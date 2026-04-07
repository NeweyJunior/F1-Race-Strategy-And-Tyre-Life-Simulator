#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

//------- CONSTANTS -------
#define HIGH_STRESS_COEFFICIENT 0.80
#define STRESS_FACTOR_COEFFICIENT 0.11
#define DEGREE_DIFFERENT_COEFFICIENT 0.0002
#define WEIGHT_PENALTY_COEFFICIENT 0.00015
#define SOFT_TIME_COEFFICIENT 0.995
#define MEDIUM_TIME_COEFFICIENT 1.00
#define HARD_TIME_COEFFICIENT 1.005
#define AVG_FUEL_COEFFICIENT 0.03
#define SOFT_TYRE_PENALTY 0.75
#define INVALID_LAP 999999.0
#define TOTAL_NUMBER_OF_TRACKS 24
#define PROBABILITY_CALCULATION_NUMBER 10000
#define MAX_STOP_NUMBER 5
#define SOFT_WINDOW_COEFFICIENT 0.1
#define MEDIUM_WINDOW_COEFFICIENT 0.2
#define HARD_WINDOW_COEFFICIENT 0.3
//-------------------------

typedef struct {
    char name[100];
    float length;
    float referenceTime;
    float pitWay;
    int stressLevel;
    float trackFuelCoefficient;
    int totalLaps;
} Track;

Track allTracks[TOTAL_NUMBER_OF_TRACKS];

//--------global variables--------
float c1_coefficient = 1.60;
float c2_coefficient = 1.45;
float c3_coefficient = 0.95;
float c4_coefficient = 0.70;
float c5_coefficient = 0.50;
float c6_coefficient = 0.30;
float originalCarWeight = 798.0;
//--------------------------------

//------------functions-----------------
int calculateTyreLife(float trackDegree, int tyreType, float trackLength, int trackStress, float startFuel, Track t);
void calculateBestStrategy(int trackID, float startFuel, float trackTemp);
void menu();
void smallMenu();
void calculateStopNumber(Track t, float startFuel, float trackTemp);
//--------------------------------------

int main() {
	srand(time(NULL));

	FILE* tracksData;
	tracksData = fopen("C:\\Users\\LENOVO\\Desktop\\F1-Race-Strategy-And-Tyre-Life-Simulator\\tracks_data.txt","r");
	
	if(tracksData == NULL){
		printf("File opening is failed.\n");
		return 1;
	}else{
		int i = 0;
		while(fscanf(tracksData,"%s %f %f %f %d %f %d",allTracks[i].name,&allTracks[i].length,&allTracks[i].referenceTime,
		&allTracks[i].pitWay,&allTracks[i].stressLevel,&allTracks[i].trackFuelCoefficient,&allTracks[i].totalLaps) == 7)
			i++;
		fclose(tracksData);
	}
	
    menu();
    int chooseTrack, tyre, actionType;
    float startFuel,trackTemp;
    
    while (1) { 
        printf("1-Calculate tyre life || 2- Calculate best strategy || 3- Exit\n");
        printf("===========================================================================================\n");
        printf("What action do you want to take:");
        if (scanf("%d", &actionType) != 1) {
            printf("Invalid input. Please enter a valid number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }
        
        if (actionType == 3) {
            printf("Exiting simulator... See you on track!\n");
            return 0;
        }
        
        if (actionType == 1) {
            printf("-------------------------------------------------------------------------------------------\n");
            printf("Please select a track:");
            if (scanf("%d", &chooseTrack) != 1) {
                printf("Invalid input. Please enter a valid track number.\n");
                while (getchar() != '\n');
                continue;
            }
            printf("-------------------------------------------------------------------------------------------\n");
            
            if (chooseTrack > 24 || chooseTrack < 1) {
                printf("Please enter a valid track.\n");
                printf("-------------------------------------------------------------------------------------------\n");
                continue;
            }
            
            printf("Please enter a track temperature: ");
            if (scanf("%f",&trackTemp) != 1) {
                printf("Invalid input. Please enter a valid temperature.\n");
                while (getchar() != '\n');
                continue;
            }
            printf("-------------------------------------------------------------------------------------------\n");
            
            Track selectedTrack = allTracks[chooseTrack - 1];
            printf("SELECTED TRACK: %s\n", selectedTrack.name);
            printf("Temp: %.2f C | Length: %.3f km | Stress Level: %d | Number of laps: %d\n", 
                   trackTemp, selectedTrack.length, selectedTrack.stressLevel, selectedTrack.totalLaps);
            printf("-------------------------------------------------------------------------------------------\n");
            
            printf("Enter starting fuel load (kg):");
            if (scanf("%f", &startFuel) != 1 || startFuel <= 0) {
                printf("Invalid input. Please enter a positive fuel load.\n");
                while (getchar() != '\n');
                continue;
            }
            printf("-------------------------------------------------------------------------------------------\n");
            
            printf("1) c1 | 2) c2 | 3) c3 | 4) c4 | 5) c5 | 6) c6 |\n");
            printf("Select tyre compound (1-6):");
            if (scanf("%d", &tyre) != 1 || tyre < 1 || tyre > 6) {
                printf("Invalid input. Please select a tyre compound between 1 and 6.\n");
                while (getchar() != '\n');
                continue;
            }
            printf("===========================================================================================\n");
            
            int life = calculateTyreLife(trackTemp, tyre, selectedTrack.length, selectedTrack.stressLevel, startFuel, selectedTrack);
            printf("%d lap tyre life\n", life);
            printf("===========================================================================================\n");
            
        } else if (actionType == 2) {
           printf("-------------------------------------------------------------------------------------------\n");
            printf("Please select a track:");
            if (scanf("%d", &chooseTrack) != 1) {
                printf("Invalid input. Please enter a valid track number.\n");
                while (getchar() != '\n');
                continue;
            }
            printf("-------------------------------------------------------------------------------------------\n");
            
            if (chooseTrack > 24 || chooseTrack < 1) {
                printf("Please enter a valid track.\n");
                printf("-------------------------------------------------------------------------------------------\n");
                continue;
            }
            
            printf("Please enter a track temperature: ");
            if (scanf("%f",&trackTemp) != 1) {
                printf("Invalid input. Please enter a valid temperature.\n");
                while (getchar() != '\n');
                continue;
            }
            printf("-------------------------------------------------------------------------------------------\n");
            
            Track selectedTrack = allTracks[chooseTrack - 1];
            printf("SELECTED TRACK: %s\n", selectedTrack.name);
            printf("Temp: %.2f C | Length: %.3f km | Stress Level: %d | Number of laps: %d\n", 
                   trackTemp, selectedTrack.length, selectedTrack.stressLevel, selectedTrack.totalLaps);
            printf("-------------------------------------------------------------------------------------------\n");
            
            printf("Enter starting fuel load (kg):");
            if (scanf("%f", &startFuel) != 1 || startFuel <= 0) {
                printf("Invalid input. Please enter a positive fuel load.\n");
                while (getchar() != '\n');
                continue;
            }
            printf("-------------------------------------------------------------------------------------------\n");
            
            calculateStopNumber(selectedTrack, startFuel, trackTemp);
        } else {
            printf("===========================================================================================\n");
            printf("Please select a valid process.\n");
            printf("===========================================================================================\n");
            continue;
        }
        smallMenu();
    }
    return 0;
}

int calculateTyreLife(float trackDegree, int tyreType, float trackLength, int trackStress, float startFuel, Track t) {
    float selectedCoefficient;

    switch (tyreType) {
        case 1: selectedCoefficient = c1_coefficient; break;
        case 2: selectedCoefficient = c2_coefficient; break;
        case 3: selectedCoefficient = c3_coefficient; break;
        case 4: selectedCoefficient = c4_coefficient; break;
        case 5: selectedCoefficient = c5_coefficient; break;
        case 6: selectedCoefficient = c6_coefficient; break;
        default: selectedCoefficient = c3_coefficient; break;
    }

    float idealKm = 250.0;
    
    if(t.stressLevel == 5){
        selectedCoefficient *= HIGH_STRESS_COEFFICIENT;
    }
    
    if(t.length > 5.0 && (tyreType == 5 || tyreType == 6)){
        selectedCoefficient *= SOFT_TYRE_PENALTY;
    }
    
    float totalDistance = idealKm * selectedCoefficient;

    float referenceDegree = 20.0;
    float degreeDifference = trackDegree - referenceDegree;
    float degreeEffect = 1.0 - (degreeDifference * DEGREE_DIFFERENT_COEFFICIENT);

    float stressFactor = 1 - ((trackStress - 1) * STRESS_FACTOR_COEFFICIENT);

    float grainingPenalty = 1.0;

    if (trackDegree <= 25.0 && trackStress <= 3) {
        grainingPenalty = 0.82;
    }

    if (degreeEffect <= 0.0) {
        printf("!!! CRITICAL ERROR !!! Tire burst due to excessive heat!\n");
        return 0;
    }
    
    float startWeight = startFuel + originalCarWeight; 
    float lastWeight = startWeight;

    for (int i = 0; i < t.totalLaps; i++) {
        lastWeight -= t.trackFuelCoefficient;
    }
    
    float averageWeight = (startWeight + lastWeight - (2 * originalCarWeight)) / 2;
    float weightPenalty = 1 - (averageWeight * WEIGHT_PENALTY_COEFFICIENT);

    float realDistance = totalDistance * degreeEffect * stressFactor * grainingPenalty * weightPenalty;

    int howManyLaps = (int)realDistance / trackLength;

    return howManyLaps;
}

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

void menu() {
    printf("===========================================================================================\n");
    printf("-------                       STRATEGY CALCULATE SIMULATOR                          -------\n");
    printf("===========================================================================================\n");
    printf("WELCOME TO THE STRATEGY CALCULATION SIMULATOR V1.5! THE PURPOSE OF THIS SIMULATOR IS\nTO FIND THE STRATEGY THAT WILL FINISH THE RACE IN THE FASTEST WAY.\n");
    printf("===========================================================================================\n");
    printf("1-AUSTRALIA GP || 2-CHINESE GP || 3-JAPANESE GP || 4-BAHRAIN GP || 5-SAUDI ARABIAN GP ||\n");
    printf("6-MIAMI GP || 7-CANADA GP || 8-MONACOGP || 9-SPANISH GP || 10-AUSTRIAN GP ||\n");
    printf("11-BRITISH GP || 12-BELGIAN GP || 13-HUNGARIAN GP || 14-DUTCH GP || 15-ITALIAN GP ||\n");
    printf("16-MADRID GP || 17-AZERBAIJAN GP || 18-SINGAPORE GP || 19-US GP || 20-MEXICO CITY GP ||\n");
    printf("21-SAO PAULO GP || 22-LAS VEGAS GP || 23-QATAR GP || 24-ABU DHABI GP || \n");
    printf("===========================================================================================\n");
}

void smallMenu() {
    printf("1-AUSTRALIA GP || 2-CHINESE GP || 3-JAPANESE GP || 4-BAHRAIN GP || 5-SAUDI ARABIAN GP ||\n");
    printf("6-MIAMI GP || 7-CANADA GP || 8-MONACOGP || 9-SPANISH GP || 10-AUSTRIAN GP ||\n");
    printf("11-BRITISH GP || 12-BELGIAN GP || 13-HUNGARIAN GP || 14-DUTCH GP || 15-ITALIAN GP ||\n");
    printf("16-MADRID GP || 17-AZERBAIJAN GP || 18-SINGAPORE GP || 19-US GP || 20-MEXICO CITY GP ||\n");
    printf("21-SAO PAULO GP || 22-LAS VEGAS GP || 23-QATAR GP || 24-ABU DHABI GP || \n");
    printf("===========================================================================================\n");
}