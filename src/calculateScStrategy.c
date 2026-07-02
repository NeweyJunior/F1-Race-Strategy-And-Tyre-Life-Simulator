#include "../headers/includes.h"
strategy scStrategy;

strategy calculateScStrategy(Track t, float startFuel, float trackTemp, int safetyCar, int scStart, int totalLapsRemaining){
    bestStrategy = calculateStopNumber(t, startFuel, trackTemp, safetyCar, scStart, totalLapsRemaining);
    strategy originalBestStrategy = bestStrategy;
    
    int totalLapNumber = 0, scFlag = 0, boxbox = 1;
    char tyreType[MAX_STOP_NUMBER + 2];
    float finalSecond = 0.0;
    float totalSeconds[MAX_STOP_NUMBER + 2][MAX_TRACK_LAPS];
    char backupForScTyre[MAX_STOP_NUMBER + 2];
    int howManyPitBeforeSc = 0;
    // flag = 0 ; sc ❌
    // flag = 1 ; sc ✔️
    for(int i = 0; i < bestStrategy.pitNumberForBest + 1; i++){
        backupForScTyre[i]= bestStrategy.bestStrategyName[i];

        for(int j = 0; j < bestStrategy.stintLap[i]; j++){
            if(bestStrategy.lapTimes[i][j] == 0) break;

            totalSeconds[i][j] = bestStrategy.lapTimes[i][j];
            finalSecond += totalSeconds[i][j];
            totalLapNumber++;
            
            if(totalLapNumber == scStart){
                scFlag = 1;
                break;
            }
        }
        if(scFlag == 0){
            finalSecond += t.pitWay;
            howManyPitBeforeSc++;
        }
        tyreType[i] = bestStrategy.bestStrategyName[i];
        if(scFlag) break;
    }
    // if we do pit
    if(boxbox){
        totalLapsRemaining -= scStart; // To accurately calculate tyre life
        startFuel -= (t.totalLaps - totalLapsRemaining) * (t.trackFuelCoefficient);
        finalSecond += (t.pitWay/2);
        scStrategy = calculateStopNumber(t, startFuel, trackTemp, safetyCar, scStart, totalLapsRemaining);
        finalSecond += scStrategy.totalSeconds;

        scStrategy.totalSeconds = finalSecond;

        // --- STITCHING ---
        char finalTyres[MAX_STOP_NUMBER + 2] = {'\0'};
        int finalLaps[MAX_STOP_NUMBER + 2] = {0};
        
        int currentStint = 0;
        int lapsCounted = 0;

        // 1. CALCULATE AND CUT THE LAP UNTIL SC IS COMPLETED.
        for(int i = 0; i <= originalBestStrategy.pitNumberForBest; i++) {
            if(lapsCounted + originalBestStrategy.stintLap[i] <= scStart) {
                // This stint was completed before the Safety Car.
                finalTyres[currentStint] = originalBestStrategy.bestStrategyName[i];
                finalLaps[currentStint] = originalBestStrategy.stintLap[i];
                lapsCounted += originalBestStrategy.stintLap[i];
                currentStint++;
                if(lapsCounted == scStart) break; // If the Safety Car came out just as you were entering the pits
            } else {
                // The Safety Car came out in the middle of this stint! We’re cutting the stint short right at the Safety Car lap.
                finalTyres[currentStint] = originalBestStrategy.bestStrategyName[i];
                finalLaps[currentStint] = scStart - lapsCounted; // Laps driven only up to the SC
                currentStint++;
                break; 
            }
        }

        // 2. Solder the new strategy added after the SC to the end.
        for(int i = 0; i <= scStrategy.pitNumberForBest; i++){
            finalTyres[currentStint] = scStrategy.bestStrategyName[i];
            finalLaps[currentStint] = scStrategy.stintLap[i];
            currentStint++;
        }

        // 3. RESTORE THE FINAL LIST INTO SC_STRATEGY
        for(int i = 0; i < currentStint; i++){
            scStrategy.bestStrategyName[i] = finalTyres[i];
            scStrategy.stintLap[i] = finalLaps[i];
        }
        scStrategy.bestStrategyName[currentStint] = '\0';
        scStrategy.pitNumberForBest = currentStint - 1; // Seal the total number of pits.
    }

    if(scStrategy.totalSeconds <= originalBestStrategy.totalSeconds){
        bestStrategy = scStrategy; // If the SC strategy is good, permanently replace it with SC.
        return scStrategy;
    }else{
        bestStrategy = originalBestStrategy; // If the SC strategy is bad, revert it to its previous state.
        return originalBestStrategy;
    }
}