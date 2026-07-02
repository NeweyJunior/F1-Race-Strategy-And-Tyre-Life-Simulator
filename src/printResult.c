#include "../headers/includes.h"

void printResult(Track t, float startFuel, float trackTemp, int safetyCar, int scStart, int totalLapsRemaining){
    
    if(safetyCar){
        calculateScStrategy(t, startFuel, trackTemp, safetyCar, scStart, totalLapsRemaining);
    }else{
        calculateStopNumber(t, startFuel, trackTemp, safetyCar, scStart, totalLapsRemaining);
    }
    
    if(bestStrategy.fuelAmount <= 0.001){ // 0.001 is very low and very riskful for fuel amount
        printf("Fuel amount is not enough.\n");
        printf("-------------------------------------------------------------------------------------------\n");
    }else{
        char stintsForTyre[MAX_STOP_NUMBER] = {0};
        printf("-------------------------------------------------------------------------------------------\n");
        printf("The winner strategy is : ");
        for(int i = 0; i < MAX_STOP_NUMBER + 1; i++){
            if(bestStrategy.bestStrategyName[i] != '\0'){
                if(bestStrategy.bestStrategyName[i + 1] == '\0'){
                    printf("%c", bestStrategy.bestStrategyName[i]);
                }else{
                    printf("%c-", bestStrategy.bestStrategyName[i]);
                }
                stintsForTyre[i] = bestStrategy.bestStrategyName[i];
            }
        }
        printf(" !!\n");

        printf("Total Laps: %d\n", t.totalLaps);
        fflush(stdout);

        int totalLapsTaken = 0;
        int howManyAverage[7] = {0};

        printf("--------- PIT WINDOW ---------\n");
        for(int i = 0; i < bestStrategy.pitNumberForBest; i++){
            if(bestStrategy.bestStrategyName[i] != ' '){
                int currentLaps = bestStrategy.stintLap[i]; // How many laps were completed in that stint?
                totalLapsTaken += currentLaps; // Update race lap
                char currentTyre = bestStrategy.bestStrategyName[i];

                // Find the coefficient according to the letter (S, M, H)
                float windowCoefficient;
                if (currentTyre == 'S') windowCoefficient = SOFT_WINDOW_COEFFICIENT;
                else if (currentTyre == 'M') windowCoefficient = MEDIUM_WINDOW_COEFFICIENT;
                else windowCoefficient = HARD_WINDOW_COEFFICIENT;
                
                // Calculate the deviation and print it to the screen.
                int pitWindowWidth = (int)(currentLaps * windowCoefficient);
                if(i == 0)
                    howManyAverage[i] = ((totalLapsTaken - pitWindowWidth) + (totalLapsTaken + pitWindowWidth) ) / 2;
                howManyAverage[i] = ((totalLapsTaken - pitWindowWidth) + (totalLapsTaken + pitWindowWidth)) / 2 - howManyAverage[i - 1];
                printf("%d. Pit window: %d - %d\n", i + 1, totalLapsTaken - pitWindowWidth, totalLapsTaken + pitWindowWidth);
            }
        }
                 
        printf("----------- STINTS -----------\n");
        for(int i = 0; i <= bestStrategy.pitNumberForBest; i++){
            if(bestStrategy.bestStrategyName[i] == '\0') break;
            
            printf("%d. stint: %c with ~%d laps\n", i + 1, bestStrategy.bestStrategyName[i], bestStrategy.stintLap[i]);
        }
        
        printf("-------------------------------------------------------------------------------------------\n");
        printf("Estimated total race time -> %d:%d:%d.%.3d\n", (int)bestStrategy.totalSeconds / 3600, ((int)bestStrategy.totalSeconds % 3600) / 60,
        (((int)bestStrategy.totalSeconds % 3600) % 60) % 60, (int)(bestStrategy.totalSeconds - (int)bestStrategy.totalSeconds) * 100);
        printf("-------------------------------------------------------------------------------------------\n");
    }

}   
