
#ifndef TRACKSTRUCT_H
#define TRACKSTRUCT_H

#include "../constants/define.h"

typedef struct {
    char name[100];
    float length;
    float referenceTime;
    float pitWay;
    int stressLevel;
    float trackFuelCoefficient;
    int totalLaps;
} Track;

extern Track allTracks[TOTAL_NUMBER_OF_TRACKS];

#endif