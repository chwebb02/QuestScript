#ifndef _debug_
#define _debug_

#include "parser.h"

void printParsedLine(parsedLine *line) {
    printf("DEBUG >> Info in the parsedLine:\n");
    printf("\tField Count: %d\n", line->fieldCount);
    printf("\tRaw Field Data:\n");
    for (int i = 0; i < line->fieldCount; i++) {
        printf("\t\tField #%d - %s\n", i + 1, line->keywords[i].raw);
    }
    printf("\tTODO find way to print translation data\n");
}

#endif