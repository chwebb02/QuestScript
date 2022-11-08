#ifndef __errors__
#define __errors__

void errorHandler(int *);

enum Errors {
    FUNC_FAILED = 1,
    VARIABLE_ERROR,
};

#endif