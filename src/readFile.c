#include "../headers/includes.h"

void readFile(){
    FILE* tracksData;
    tracksData = fopen("C:\\Users\\LENOVO\\Desktop\\F1-Race-Strategy-And-Tyre-Life-Simulator\\tracks_data.txt","r");
    
    if(tracksData == NULL){
        printf("File opening is failed.\n");
        exit(EXIT_FAILURE);
    }else{
        int i = 0;
        while(fscanf(tracksData,"%s %f %f %f %d %f %d",allTracks[i].name,&allTracks[i].length,&allTracks[i].referenceTime,
        &allTracks[i].pitWay,&allTracks[i].stressLevel,&allTracks[i].trackFuelCoefficient,&allTracks[i].totalLaps) == 7)
            i++;
        fclose(tracksData);
    }
}