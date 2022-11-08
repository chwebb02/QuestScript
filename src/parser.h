#ifndef __parser__
#define __parser__

#include <stdio.h>

typedef struct {
    unsigned int fieldCount;
    char **fields;
    unsigned int keywordCount;
    char **translations;
} parsedLine;

parsedLine *parseLine(FILE *fp);

#endif