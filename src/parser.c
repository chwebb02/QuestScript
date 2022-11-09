#ifndef _parser_
#define _parser_

#include "parser.h"

#include <string.h>
#include <stdlib.h>

#include "linkedList.h"

// List of keywords and their translations
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
    line->function = malloc (line->fieldCount * sizeof(void *));
    
    // Iterate over each field in the parsedLine
    for (int i = 0; i < line->fieldCount; i++) {
        line->function[i] = NULL;

        // Iterate over each keyword, checking for a match
        for (int n = 0; n < keywords.size; n++) {
            // Assign a translation from the keywords list
            translation *comparison = fromList(keywords, n);

            // If the strings match, assign the translation to the associated translation in the parsedLine
            if (!strcmp(comparison->raw, line->fields[i])) {
                line->function[i] = comparison->translation;
            }
        }
    }
    
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

int initParser(int (*pImport)(parsedLine *), int (*pAssign)(parsedLine *)) {
    keywords = makeList();

    translation import, assign;
    
    // Import translation
    import.raw = malloc (7 * sizeof(char));
    if (import.raw == NULL)
        return 2;
    strcpy(import.raw, "import");
    import.translation = pImport;

    // Assign translation
    assign.raw = malloc (6 * sizeof(char));
    if (assign.raw == NULL)
        return 3;
    strcpy(assign.raw, "assign");
    assign.translation = pAssign;

    // Append the translations to the keywords list
    appendList(&keywords, &import);
    appendList(&keywords, &assign);

    return 0;
}

#endif