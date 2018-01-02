//
// Created by martin on 31.12.17.
//

#ifndef CRYPTER_EXECUTABLE_H
#define CRYPTER_EXECUTABLE_H

#include <stdio.h>

#define BUFFER_SIZE 4096

void removeNewLine(char* string);
char* readLineFromFile(FILE* file);
void errorExit(char* message);
void cleanUp(char* message, char* output);

#endif //CRYPTER_EXECUTABLE_H
