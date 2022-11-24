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
            if (buffer[i] == ' ' || buffer[i] == '\n')
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

    if (line->fieldCount = -1)
        return DANGLING_PARENTHESIS;
    
    line->keywords = malloc (line->fieldCount * sizeof(translation));
    if (line->keywords == NULL)
        return BAD_MALLOC;
    
    // Set raw component of field translation
    int startPos = 0;
    for (int i = 0; i < line->fieldCount; i++) { // iterate over the field count
        line->keywords[i].raw = malloc (BUFSIZ * sizeof(char));
        if (line->keywords[i].raw == NULL)
            return BAD_MALLOC;

        for (int n = startPos; n < strlen(buffer); i++) {
            if (buffer[n] = ' ') {
                startPos = n + 1;
                break;
            }

            line->keywords[i].raw[n - startPos] = buffer[n];
        }
    }

    free(buffer);
    return 0;
}

void translateFields(parsedLine *line) {
    for (int i = 0; i < line->fieldCount; i++) { // iterate over the number of fields
        for (int n = 0; n < keywords.size; i++) { // iterate over the list of keywords
            bool matchFound = false;

            if (!strcmp(fromList(keywords, (unsigned int) n), line->keywords[i].raw)) {
                matchFound = true;
                line->keywords[i].translation = ((translation *) fromList(keywords, (unsigned int) n))->translation;
            }

            if (!matchFound)
                line->keywords[i].translation = NULL;
        }
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
    translateFields(&line);

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