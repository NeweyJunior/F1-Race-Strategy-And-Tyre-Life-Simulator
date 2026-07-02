#include "../headers/includes.h"
strategy bestStrategy;

strategy calculateStopNumber(Track t, float startFuel, float trackTemp, int safetyCar, int scStart, int totalLapsRemaining){ /*safetyCar variable
    is useless in this function, for now. */ 

    float (*sumTimes) [MAX_STOP_NUMBER + 1][MAX_TRACK_LAPS] =
        malloc(PROBABILITY_CALCULATION_NUMBER * sizeof(*sumTimes));

    if (sumTimes == NULL) {
        fprintf(stderr, "Failed to allocate simulation memory.\n");
        exit(EXIT_FAILURE);
    }

    memset(sumTimes, 0, PROBABILITY_CALCULATION_NUMBER * sizeof(*sumTimes));

    float allProbabilitys[PROBABILITY_CALCULATION_NUMBER];

    for(int k = 0; k < PROBABILITY_CALCULATION_NUMBER; k++){
        allProbabilitys[k] = INVALID_LAP;
    }
    
    float startFuelBackUp = startFuel;
    int reStartingLap = scStart + 1;
    char tyres[3] = {'S', 'M', 'H'};
    char allSimTyres[PROBABILITY_CALCULATION_NUMBER][MAX_STOP_NUMBER + 2]; /* For each simulation,
     it keeps track of which tire type was used at each pit stop. */

    int allSimLaps[PROBABILITY_CALCULATION_NUMBER][MAX_STOP_NUMBER + 1]; /* For each simulation,
     it tracks how many laps the tire can withstand in each stint. */

    int allSimPitNumbers[PROBABILITY_CALCULATION_NUMBER]; /* For each simulation,
     it keeps track of the total number of pit stops. */

    float endFuel[PROBABILITY_CALCULATION_NUMBER] = {0.0};

    for(int k = 0; k < PROBABILITY_CALCULATION_NUMBER; k++){
        for(int l = 0; l < MAX_STOP_NUMBER + 1; l++){
            allSimTyres[k][l] = '\0';
            allSimLaps[k][l] = 0;
        }
        allSimPitNumbers[k] = 0;
    }

    for(int j = 0; j < PROBABILITY_CALCULATION_NUMBER; j++){
        // flag 1 = invalid stint
        // flag 2 = calculate race time
        // flag 3 = fuel amount is low
        
        int selectedTyre = 1;
        int i, flag, laps, lapsRemaining, pitNumber = 0;
        float totalTime = 0;
        startFuel = startFuelBackUp;

        for(int resetStintIndex = 0; resetStintIndex < MAX_STOP_NUMBER; resetStintIndex++){
            for(int resetLapIndex = 0; resetLapIndex < MAX_TRACK_LAPS; resetLapIndex++){
                sumTimes[j][resetStintIndex][resetLapIndex] = 0;
            }   
        }
        
        for(i = 0; i < MAX_STOP_NUMBER; i++){
            flag = 0; 
            if(i == 0) lapsRemaining = totalLapsRemaining;

            int tyreNumbers[3] = {1, 3, 5};
            selectedTyre = tyreNumbers[rand() % 3];

            if(selectedTyre == 1) allSimTyres[j][i]  = tyres[2];
            else if(selectedTyre == 3) allSimTyres[j][i]  = tyres[1];
            else if(selectedTyre == 5) allSimTyres[j][i]  = tyres[0];

            laps = calculateTyreLife(trackTemp, selectedTyre, t.length, t.stressLevel, startFuel, t); // laps = life of selected tyre
            
            if(laps > lapsRemaining) laps = lapsRemaining;

            allSimLaps[j][i] = laps;

            // Pit window calculate
            float windowCoefficient;
            if (selectedTyre == 5) windowCoefficient = SOFT_WINDOW_COEFFICIENT;
            else if (selectedTyre == 3) windowCoefficient = MEDIUM_WINDOW_COEFFICIENT;
            else windowCoefficient = HARD_WINDOW_COEFFICIENT;
            
            int pitWindowWidth = (int)(laps * windowCoefficient);

            float speed;
            if (selectedTyre == 5) speed = t.referenceTime * SOFT_TIME_COEFFICIENT; // Soft
            else if (selectedTyre == 3) speed = t.referenceTime * MEDIUM_TIME_COEFFICIENT; // Medium
            else speed = t.referenceTime * HARD_TIME_COEFFICIENT; // Hard
            
            for(int lapNumber = 0; lapNumber < laps; lapNumber++){
                startFuel -= t.trackFuelCoefficient;
                sumTimes[j][i][lapNumber] = (speed) + (startFuel * AVG_FUEL_COEFFICIENT);
            }

            // Fuel control:
            if(startFuel <= 0){
                flag = 3;
                break;
            }

            // Stint ending:
            lapsRemaining -= laps;
            if(lapsRemaining <= 0){
                flag = 2;
                break;
            }

            pitNumber++;
        }

        for(int stintIndex = 0; stintIndex < MAX_STOP_NUMBER; stintIndex++){
            for(int lapIndex = 0; lapIndex < MAX_TRACK_LAPS; lapIndex++){
                if(sumTimes[j][stintIndex][lapIndex] == 0){
                    break;
                }
                totalTime += sumTimes[j][stintIndex][lapIndex];
            }
        }

        if(flag == 1){
            allProbabilitys[j] = INVALID_LAP;
        }else if(flag == 2){
            allProbabilitys[j] = totalTime + (pitNumber) * (t.pitWay);
            allSimPitNumbers[j] = pitNumber;
            char firstTyre = allSimTyres[j][0];
            int isLegal = 0;

            for(int k = 0; k <= pitNumber; k++){
                if(firstTyre != allSimTyres[j][k]){
                    isLegal = 1;
                }
            }

            if(isLegal == 0) allProbabilitys[j] = INVALID_LAP;
            else endFuel[j] = startFuel;

        }else if(flag == 3){
            allProbabilitys[j] = INVALID_LAP;
        }
    }

    float smallest = allProbabilitys[0];
    int bestIndex = 0;
    for(int i = 0; i < PROBABILITY_CALCULATION_NUMBER; i++){
        if(allProbabilitys[i] < smallest){
            smallest = allProbabilitys[i];
            bestIndex = i;
        }
    }
    
    for(int i = 0; i < MAX_STOP_NUMBER + 1; i++){
        bestStrategy.bestStrategyName[i] = '\0';
        bestStrategy.stintLap[i] = 0;
    }

    for(int i = 0; i < MAX_STOP_NUMBER + 1; i++){
        if(allSimTyres[bestIndex][i] != ' '){ 
            bestStrategy.bestStrategyName[i] = allSimTyres[bestIndex][i];
            bestStrategy.stintLap[i] = allSimLaps[bestIndex][i];
            bestStrategy.fuelAmount = endFuel[bestIndex];
            bestStrategy.bestIndex = bestIndex;
            for(int j = 0; j < MAX_TRACK_LAPS; j++){
                bestStrategy.lapTimes[i][j] = sumTimes[bestIndex][i][j];
            }
        }
    }
    bestStrategy.totalSeconds = (int) smallest;
    bestStrategy.pitNumberForBest = allSimPitNumbers[bestIndex];

    free(sumTimes);

    return bestStrategy;
}