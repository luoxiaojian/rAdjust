#ifndef _RALGO_H_
#define _RALGO_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LINE_NUM 2000
#define STR_LENGTH 80
#define r1min 22
#define rcmax 29

void generateRandStr(char *str);

void loadSelfSet(char *filename, char **selfSet);

float avgHDist(char **selfSet);

float avgHDistRand(char **selfSet, int iter);

int rAlgo(char *str, char **selfSet, int r1, int c);

#endif
