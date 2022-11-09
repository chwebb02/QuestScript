#ifndef _errors_
#define _errors_

#include "errors.h"

#include <stdio.h>

void errorHandler(int *errorCode) {
    if (errorCode == NULL)
        return;

    if (errorCode[1] == 0)
        return;

    printf("ERROR >> ");
    switch (errorCode[1]) {
        case FUNC_FAILED:
            printf("function failed");
            break;
        case FIELD_COUNT:
            printf("wrong field count");
            break;
    }
        
    printf(" on line %d!\n", errorCode[0]);
}

#endif