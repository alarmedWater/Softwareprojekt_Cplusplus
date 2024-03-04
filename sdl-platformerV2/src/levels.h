#ifndef LEVELS_H
#define LEVELS_H

#include "types.h"

enum
{
    LEVEL_COUNTX = 2,
    LEVEL_COUNTY = 2
};

extern Level levels[LEVEL_COUNTY][LEVEL_COUNTX];

void initializeLevels();
char* loadLevelFromFile(const char* filename);

#endif