#ifndef _variables_
#define _variables_

#include "variables.h"

#include <stdbool.h>

#include "linkedList.h"
#include "errors.h"

list variables;

// Initializes a new variable and appends it to the variables list
// Returns 0 if successful, or an error code
int newVar(char *key, type t) {
	if (key == NULL)
		return NO_VAR_NAME;
	if (t.typeSize < 1 || t.typeName == NULL)
		return NO_VAR_TYPE;

	var newVar;
	newVar.key = key;
	newVar.varType = t;
	appendList(&variables, &newVar);

	return NO_ERROR;
}

var *dereferenceVar(char *key) {
	if (key == NULL)
		return NULL;	
	// Search for the variable by key
	var *output; bool isInitialized = false;
	for (int i = 0; i < variables.size; i++) {
		output = fromList(variables, i);

		if (!strcmp(key, output->key)) {
			isInitialized = true;
			break;
		}
	}

	if (!isInitialized)
		return NULL;
	
	return output;
}

int assignVar(char *key, void *value) {
	if (key == NULL)
		return NO_VAR_NAME;
	if (value == NULL)
		return NO_ASSIGNMENT_VALUE;

	var *variable = dereferenceVar(key);
	if (variable == NULL)
		return VAR_NOT_INITIALIZED;
	
	if (sizeof(*value) != variable->varType.typeSize)
		return TYPE_CONVERSION;
	
	variable->value = value;
	return NO_ERROR;
}

int deleteVar(char *key) {
	if (key == NULL)
		return NO_VAR_NAME;
	
	var *variable = dereferenceVar(key);
	if (variable == NULL)
		return VAR_NOT_INITIALIZED;
	
	return NO_ERROR;
}

#endif