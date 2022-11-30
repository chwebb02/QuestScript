#!/bin/bash

# Compiler statement, will be updated as project goes on because I am too lazy to learn how to use CMake
gcc src/interpreter.c src/errors.c src/linkedList.c src/parser.c src/variables.c -o qsRuntime