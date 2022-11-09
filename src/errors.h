#ifndef __errors__
#define __errors__

void errorHandler(int *);

enum Errors {
    NO_ERROR,
    FUNC_FAILED,
    FIELD_COUNT,
    NO_VAR_NAME,
    NO_VAR_TYPE,
    NAME_IN_USE,
    VAR_NOT_INITIALIZED,
    KEY_NULL,
    VALUE_NULL,
    TYPE_CONVERSION,
    NO_ASSIGNMENT_VALUE,
};

#endif