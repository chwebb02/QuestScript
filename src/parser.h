#ifndef __parser__
#define __parser__

#include <stdio.h>

typedef struct linestruct {
    unsigned int fieldCount;
    char **fields;
    unsigned int keywordCount;
    int (**function)(struct linestruct *); // array of function pointers to relevant library functions
} parsedLine;

typedef struct {
    char *raw;
    int (*translation)(struct linestruct *); // function pointer corresponding to a keyword
} translation;

parsedLine *parseLine(FILE *fp);
void addKeyword(translation *addition);
int initParser(int (*)(parsedLine *), int (*)(parsedLine *));

#endif