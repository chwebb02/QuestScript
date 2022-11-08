#ifndef __variables__
#define __variables__

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *key;
    char *type;
    void *value;
} var;

var newVar(char *varName, char *type);
void assignVar(char *key, void *value);


#endif