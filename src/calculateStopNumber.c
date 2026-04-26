#include "../headers/includes.h"

void calculateStopNumber(Track t, float startFuel, float trackTemp){
    float allProbabilitys[PROBABILITY_CALCULATION_NUMBER];

    for(int k = 0; k < PROBABILITY_CALCULATION_NUMBER; k++){
        allProbabilitys[k] = INVALID_LAP;
    }
    
    float startFuelBackUp = startFuel;
    char tyres[3] = {'S', 'M', 'H'};
    char allSimTyres[PROBABILITY_CALCULATION_NUMBER][MAX_STOP_NUMBER + 1];
    int allSimLaps[PROBABILITY_CALCULATION_NUMBER][MAX_STOP_NUMBER + 1];
    int allSimPitNumbers[PROBABILITY_CALCULATION_NUMBER];

    for(int k = 0; k < PROBABILITY_CALCULATION_NUMBER; k++){
        for(int l = 0; l < MAX_STOP_NUMBER + 1; l++){
            allSimTyres[k][l] = ' ';
        }
        allSimPitNumbers[k] = 0;
    }

    for(int j = 0; j < PROBABILITY_CALCULATION_NUMBER; j++){
        //flag 1 = invalid lap
        //flag 2 = calculate race time

        int selectedTyre = 1;
        float sumTimes = 0;
        int i, flag, laps, lapsRemaining, pitNumber = 0;
        startFuel = startFuelBackUp;
        
        for(i = 0; i < MAX_STOP_NUMBER; i++){
            flag = 0; 
            if(i == 0) lapsRemaining = t.totalLaps;

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
            
            float fuelBurn = laps * t.trackFuelCoefficient;
            float avgFuel = startFuel - (fuelBurn / 2);
            
            sumTimes += (laps * speed) + (laps) * (avgFuel * AVG_FUEL_COEFFICIENT);

            lapsRemaining -= laps; 
            if(lapsRemaining <= 0){
                flag = 2;
                break;
            }

            startFuel = startFuel - fuelBurn;
            if(startFuel <= 0){
                flag = 1; 
                break;
            }
            pitNumber++;
        }

        if(flag == 1){
            allProbabilitys[j] = INVALID_LAP;
        }else if(flag == 2){
            allProbabilitys[j] = sumTimes + (pitNumber) * (t.pitWay);
            allSimPitNumbers[j] = pitNumber;
            char firstTyre = allSimTyres[j][0];
            int isLegal = 0;

            for(int k = 0; k <= pitNumber; k++){
                if(firstTyre != allSimTyres[j][k]){
                    isLegal = 1;
                }
            }
            if(isLegal == 0) allProbabilitys[j] = INVALID_LAP;
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
    int pitNumberForBest = allSimPitNumbers[bestIndex];
    int totalSeconds = (int) smallest;
    printf("The winner strategy is : ");
    for(int i = 0; i < MAX_STOP_NUMBER + 1; i++){
        if(allSimTyres[bestIndex][i] != ' '){ 
            printf("%c ", allSimTyres[bestIndex][i]);
        }
    }
    printf("!!\n");

    int totalLapsTaken = 0;

    for(int i = 0; i < pitNumberForBest; i++){
        if(allSimTyres[bestIndex][i] != ' '){ 
            int currentLaps = allSimLaps[bestIndex][i]; // How many laps were completed in that stint?
            totalLapsTaken += currentLaps; // Update race lap
            char currentTyre = allSimTyres[bestIndex][i];
            
            // Find the coefficient according to the letter (S, M, H)
            float windowCoefficient;
            if (currentTyre == 'S') windowCoefficient = SOFT_WINDOW_COEFFICIENT;
            else if (currentTyre == 'M') windowCoefficient = MEDIUM_WINDOW_COEFFICIENT;
            else windowCoefficient = HARD_WINDOW_COEFFICIENT;
            
            // Calculate the deviation and print it to the screen.
            int pitWindowWidth = (int)(currentLaps * windowCoefficient);
            printf("(%d. Pit window: %d - %d) ", i + 1, totalLapsTaken - pitWindowWidth, totalLapsTaken + pitWindowWidth);
        }
    }
    printf("\n");
    printf("Estimated total race time : %d min. %d sec.\n",totalSeconds / 60, totalSeconds % 60);
    printf("-------------------------------------------------------------------------------------------\n");
}