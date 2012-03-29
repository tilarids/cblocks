#include "gens.h"
#include <stdio.h>

START_GENERATOR(int, enumerate, (int start, int end))
    int i = start;
    for(; i<end; ++i)
    {
        printf("Yielding %d\n", i);
        YIELD(i);
    }
END_GENERATOR

START_GENERATOR(char, for_each, (char* start, char* end))
    while (start != end)
    {
        YIELD(*start);
        ++start;
    }
END_GENERATOR
