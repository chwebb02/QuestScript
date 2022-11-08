#ifndef __parser__
#define __parser__

#include <stdio.h>

typedef struct {
    unsigned int fieldCount;
    char **fields;
    unsigned int commandCount;
} parsedLine;

enum actions {
    ASSIGN_INT = 1,
    ASSIGN_CHAR,
};

parsedLine *parseLine(FILE *fp);

#define NULL_LINE (parsedLine){0, NULL, 0}

#endif