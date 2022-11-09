#ifndef __parser__
#define __parser__

#include <stdio.h>

typedef struct linestruct {
    unsigned int fieldCount;
    char **fields;
    unsigned int keywordCount;
    int (**function)(struct linestruct *, void **); // array of function pointers to relevant library functions
} parsedLine;

typedef struct {
    char *raw;
    int (*translation)(struct linestruct *, void **); // function pointer corresponding to a keyword
} translation;

parsedLine *parseLine(FILE *fp);
void addKeyword(translation *addition);
void initParser();

#endif