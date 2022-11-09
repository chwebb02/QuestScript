#ifndef __variables__
#define __variables__

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *typeName;
    unsigned short typeSize;
} type;

typedef struct {
    char *key;
    void *value;
    type varType;
} var;

int newVar(char *key, type t);
int assignVar(char *key, void *value);
var *dereferenceVar(char *key);
int deleteVar(char *key);

#endif