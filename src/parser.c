#ifndef _parser_
#define _parser_

#include "parser.h"

#include <string.h>
#include <stdlib.h>

#include "linkedList.h"

list keywords;

void addKeyword(translation *addition) {
    appendList(&keywords, addition);
}

unsigned int getFieldCount(char *data) {
    unsigned int output = 1;

    for (int i = 0; i < strlen(data); i++) {
        if (data[i] == ' ')
            output += 1;
    }

    return output;
}

int fillFields(parsedLine *line, char *data) {
    line->fields = malloc (line->fieldCount * sizeof(char *));
    
    int startPos = 0;
    for (int i = 0; i < line->fieldCount; i++) {
        for (int n = startPos; n < strlen(data); n++) {            
            if (data[n] == ' ' || data[n] == '\n') {
                line->fields[i] = malloc ((n - startPos) * sizeof(char));
                if (line->fields[i] == NULL)
                    return 1;

                for (int m = n - startPos; m >= 0; m--) {
                    line->fields[i][m] = data[m + startPos];
                }

                startPos = n + 1;
                break;
            }
        }
    }

    return 0;
}

int translateFields(parsedLine *line) {
    
    
    return 0;
}

parsedLine *parseLine(FILE *fp) {
    parsedLine *line = malloc (sizeof(parsedLine));

    char *raw = malloc (BUFSIZ * sizeof(char));
    if (raw == NULL)
        return NULL;
    fgets(raw, BUFSIZ, fp);

    line->fieldCount = getFieldCount(raw);
    if (fillFields(line, raw)) return NULL;

    return line;
}

void initParser() {
    keywords = makeList();

}

#endif