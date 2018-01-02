//
// Created by martin on 31.12.17.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "executable.h"

void removeNewLine(char* string) {
    //remove new line \n
    char* posNewLine = strchr(string, '\n');
    if(posNewLine != NULL) {
        *posNewLine = '\0';
    }
}

void cleanUp(char* message, char* output) {
    if(message != NULL)
        free(message);

    if(output != NULL)
        free(output);
}

void errorExit(char* message) {
    fprintf(stderr, message);
    fprintf(stderr, "\n");

    exit(EXIT_FAILURE);
}

char* readLineFromFile(FILE* file) {
    char* buffer = malloc(BUFFER_SIZE * sizeof(char));

    if (file == NULL) {
        return NULL;
    }

    if(fgets(buffer, BUFFER_SIZE, file)) {
        //read into buffer, fgets automatic ads \0 to end of buffer
        return buffer;
    } else {
        //error
        return NULL;
    }
}