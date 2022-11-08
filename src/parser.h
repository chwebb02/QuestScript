#ifndef __parser__
#define __parser__

#include <stdio.h>

typedef struct {
    unsigned int fieldCount;
    char **fields;
    unsigned int keywordCount;
    char **translations;
} parsedLine;

typedef struct {
    char *raw;
    char *translated;
} translation;

parsedLine *parseLine(FILE *fp);
void addKeyword(translation *addition);
void initParser();

#endif