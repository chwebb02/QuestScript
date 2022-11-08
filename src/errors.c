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
    if (errorCode[1] == FUNC_FAILED)
        printf("function failed");
    else if (errorCode[1] == VARIABLE_ERROR)
        printf("variable error");
        
    printf(" on line %d!\n", errorCode[0]);
}

#endif