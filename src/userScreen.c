#include "../headers/includes.h"

/* 
    This function, controlled user screen (It was previously in main.c; the load on main.c has been reduced.)
*/

void userScreen(){
    menu();
    int chooseTrack, tyre, actionType, safetyCar, scStart = 0;
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
            break;
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
            
            printf("Should the possibility of a safety car being used be considered?\n");
            printf("1) Yes\t\t 0) No\n");
            printf("Choose: ");

            if (scanf("%d", &safetyCar) != 1 || (safetyCar != 0 && safetyCar != 1)) {
                printf("Invalid input. Please enter a valid choose.\n");
                while (getchar() != '\n');
                continue;
            }
            printf("-------------------------------------------------------------------------------------------\n");
            if(safetyCar){
                printf("Enter sc start lap number:");

                if (scanf("%d", &scStart) != 1 || scStart <= 0 || scStart >= selectedTrack.totalLaps) {
                    printf("Invalid input. Please enter a valid lap number.\n");
                    while (getchar() != '\n');
                    continue;
                }

                printf("-------------------------------------------------------------------------------------------\n");

                printf("Enter starting fuel load (kg):");
                if (scanf("%f", &startFuel) != 1 || startFuel <= 0) {
                    printf("Invalid input. Please enter a valid fuel load.\n");
                    while (getchar() != '\n');
                    continue;
                }
                printResult(selectedTrack, startFuel, trackTemp, safetyCar, scStart, selectedTrack.totalLaps);
                
                printf("-------------------------------------------------------------------------------------------\n");
            }else{
                printf("Enter starting fuel load (kg):");
                if (scanf("%f", &startFuel) != 1 || startFuel <= 0) {
                    printf("Invalid input. Please enter a valid fuel load.\n");
                    while (getchar() != '\n');
                    continue;
                }
                printf("-------------------------------------------------------------------------------------------\n");
                printResult(selectedTrack, startFuel, trackTemp, safetyCar, scStart, selectedTrack.totalLaps);
            }



        } else {
            printf("===========================================================================================\n");
            printf("Please select a valid process.\n");
            printf("===========================================================================================\n");
            continue;
        }
        smallMenu();
    }
}
