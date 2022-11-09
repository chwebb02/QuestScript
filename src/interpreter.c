#ifndef __interpreter__
#define __interpreter__

#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "errors.h"

int *interpretLine(int *line, parsedLine *info) {
	int *errorInfo = malloc (2 * sizeof(int));
	errorInfo[0] = *line;
	*line += 1;
	// Iterate over each field of the parsedLine
	for (int i = 0; i < info->fieldCount; i++) {
		// Go to next field if no translation is found
		if (info->function[i] == NULL)
			continue;
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
	initParser();

	int line = 1;
	int *error = malloc (2 * sizeof(int));
	while(!feof(fp)) {
		parsedLine *myLine = parseLine(fp);

		errorHandler(interpretLine(&line, myLine));

		free(myLine);
	}
}

#endif