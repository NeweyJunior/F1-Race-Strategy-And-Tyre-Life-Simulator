#include "../headers/includes.h"

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
