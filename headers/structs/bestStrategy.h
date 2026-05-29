#ifndef BEST_STRATEGY
#define BEST_STRATEGY

#include "../constants/define.h"

typedef struct{
    char bestStrategyName[MAX_STOP_NUMBER + 1];
    int totalSeconds;
    int pitNumberForBest;
    int stintLap[MAX_STOP_NUMBER + 1];
    float fuelAmount;
}strategy;

extern strategy bestStrategy;

#endif BEST_STRATEGY