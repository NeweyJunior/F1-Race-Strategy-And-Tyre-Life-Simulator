#ifndef BEST_STRATEGY
#define BEST_STRATEGY

#include "../constants/define.h"

typedef struct{
    char bestStrategyName[MAX_STOP_NUMBER + 1];
    float totalSeconds;
    int pitNumberForBest;
    int stintLap[MAX_STOP_NUMBER + 1];
    float fuelAmount;
    float lapTimes[MAX_STOP_NUMBER + 1][MAX_TRACK_LAPS];
    int bestIndex;
}strategy;

extern strategy bestStrategy;
extern strategy scStrategy;

#endif