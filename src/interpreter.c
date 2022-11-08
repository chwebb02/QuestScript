#ifndef __interpreter__
#define __interpreter__

#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

// REMOVE THIS
#include "linkedList.h"

int *interpretLine(int *line, parsedLine info) {
    int *errorInfo = malloc (2 * sizeof(int));
    errorInfo[1] = *line;
    *line += 1;



    errorInfo[1] = 0;
    return errorInfo;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Please provide an input file!\n");
        return 1;
    }

    printf("\n");

    list myList = makeList();
    int x = 5, y = 10, z = 25;
    appendList(&myList, &x);
    appendList(&myList, &y);
    appendList(&myList, &z);
    for (int i = 1; i <= 3; i++)
        printf("%d ", *((int *) fromList(myList, i)));
    printf("\n");
    popList(&myList, 0);
    for (int i = 1; i <= 2; i++)
        printf("%d ", *((int *) fromList(myList, i)));
    printf("\n");

    // Open the file
    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        printf("UNABLE TO READ FILE, %s!\n\n", argv[1]);
        return 2;
    }

    int line = 1;
    int *error = malloc (2 * sizeof(int));
    while(!feof(fp)) {
        parsedLine *myLine = parseLine(fp);

        free(myLine);
    }
}

#endif