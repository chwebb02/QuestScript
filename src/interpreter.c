#ifndef __interpreter__
#define __interpreter__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "errors.h"

// REMOVE THIS
#include "DEBUG.c"

// Import a library
int import(parsedLine *line) {
	if (line->fieldCount > 2)
		return FIELD_COUNT;

	

	return 0;
}

int assign(parsedLine *line) {


	return 0;
}

int *interpretLine(int *line, parsedLine *info) {
	int *errorInfo = malloc (2 * sizeof(int));
	errorInfo[0] = *line;
	*line += 1;
	// Iterate over each field of the parsedLine
	for (int i = 0; i < info->fieldCount; i++) {
		// Go to next field if no translation is found
		if (info->keywords[i].translation == NULL)
			continue;
		
		// Run the parsedLine through the function
		errorInfo[1] = info->keywords[i].translation(info);
	}

	return errorInfo;
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Please provide an input file!\n");
		return 1;
	}

	printf("\n");

	// Open the file
	FILE *fp = fopen(argv[1], "r");
	if (!fp) {
		printf("UNABLE TO READ FILE, %s!\n\n", argv[1]);
		return 2;
	}

	// Initialize the components of the system
	initParser(import, assign);

	int line = 1;
	int *error = malloc (2 * sizeof(int));
	while(!feof(fp)) {
		parsedLine *myLine = parseLine(fp);
		printParsedLine(myLine);

		errorHandler(interpretLine(&line, myLine));

		freeParsedLine(&myLine);
	}
}

#endif