#ifndef __parser__
#define __parser__

#include <stdio.h>

struct linestruct;

typedef struct {
    char *raw;
    int (*translation)(struct linestruct *); // function pointer corresponding to a keyword
} translation;

typedef struct linestruct {
    unsigned int fieldCount;
    translation *keywords;
} parsedLine;

parsedLine *parseLine(FILE *fp);
void addKeyword(translation *addition);
void freeParsedLine(parsedLine **line);
int initParser(int (*)(parsedLine *), int (*)(parsedLine *));

#endif