#ifndef _parser_
#define _parser_

#include "parser.h"

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "linkedList.h"
#include "errors.h"

// List of keywords and their translations
list keywords;

// add a new keyword translation
void addKeyword(translation *addition) {
    appendList(&keywords, addition);
}

int countFields(char *buffer) {
    int fields = 0;

    int open = 0;
    for (int i = 0; i < strlen(buffer); i++) {
        if (buffer[i] == '(') {
            open += 1;

            if (i > 0)
                if (buffer[i - 1] != ' ') fields += 1;
        }

        if (!open) {
            if (buffer[i] == ' ')
                fields += 1;
        }

        if (buffer[i] == ')' && open) {
            open -= 1;
            fields += 1;
        }
        else if (!open && buffer[i] == ')')
            return -1;
    }

    return fields + 1;
}

int setFields(parsedLine *line, FILE *fp) {
    char *buffer = malloc (BUFSIZ * sizeof(char));
    if (buffer == NULL)
        return BAD_MALLOC;
    
    // Get Field Count
    fgets(buffer, BUFSIZ, fp);
    line->fieldCount = countFields(buffer);

    if (line->fieldCount == -1)
        return DANGLING_PARENTHESIS;
    
    line->keywords = malloc (line->fieldCount * sizeof(translation));
    if (line->keywords == NULL)
        return BAD_MALLOC;

    // Set raw component of field translation
    // Iterate over each field in the parsedLine
    int startPos = 0;
    for (int word = 0; word < line->fieldCount; word++) {
        line->keywords[word].raw = malloc (BUFSIZ * sizeof(char));
        if (line->keywords[word].raw == NULL)
            return BAD_MALLOC;
        
        // Progressively iterate over each character of the buffer
        int open = 0; // open parentheses counter
        for (int character = startPos; character < strlen(buffer); character++) {
            if (open < 0)
                return DANGLING_PARENTHESIS;
            
            // Opening parentheses
            if (buffer[character] == '(')
                open -= 1;
            
            // Translation for open parentheses
            if (open) {
                line->keywords[word].raw[character - startPos] = buffer[character];
                continue;
            }
            else {
                if (buffer[character] == ' ' || buffer[character] == '\n') {
                    startPos = character + 1;
                    break;
                }

                line->keywords[word].raw[character - startPos] = buffer[character];
            }

            // Closing parentheses
            if (buffer[character] == ')') {
                open -= 1;

                // Exit sequence for parenthetical fields
                if (!open) {
                    startPos = character + 1;
                    break;
                }
            }
        }
    }

    free(buffer);
    return 0;
}

void translateFields(parsedLine *line) {
    // First iterate over the number of fields in the parsedLine
    for (int field = 0; field < line->fieldCount; field++) {
        line->keywords[field].translation = malloc (sizeof(void *));
        if (line->keywords[field].translation == NULL)
            return;
        
        bool isMatch = false; // Value to check if a translation was assigned
        
        // Iterate over each keyword, checking to see if there is a translation for the field we are currently checking
        for (int keyword = 1; keyword <= ((int) keywords.size); keyword++) {
            // Get the comparison from the keywords list
            translation *comparison = fromList(keywords, keyword);

            if (!strcmp(line->keywords[field].raw, comparison->raw)) {
                isMatch = false;
                line->keywords[field].translation = comparison->translation;
                break;
            }
        }

        if (!isMatch)
            line->keywords[field].translation = NULL;
    }
}

/*
Takes a line from a file as input and returns a parsed line
pointer to the calling function, or NULL if there is an error 
*/
parsedLine *parseLine(FILE *fp) {
    // Make room for the parsedLine
    parsedLine *line = malloc (sizeof(parsedLine));
    if (line == NULL || !fp)
        return NULL;

    // Set the fieldCount and the raw fields of the translation
    if (setFields(line, fp))
        return NULL;

    // Translate the raw fields of the translation
    translateFields(line);

    printf("test 3\n");

    return line;
}

void freeParsedLine(parsedLine **line) {
    for (int i = 0; i < (*line)->fieldCount; i++)
        free((*line)->keywords[i].raw);
    free(*line);
    *line = NULL;
}

int initParser(int (*pImport)(parsedLine *), int (*pAssign)(parsedLine *)) {
    keywords = makeList();

    translation import, assign;
    
    // Import translation
    import.raw = malloc (8 * sizeof(char));
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