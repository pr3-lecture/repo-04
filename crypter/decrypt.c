//
// Created by martin on 31.12.17.
//

#include <stdio.h>
#include <stdlib.h>
#include "decrypt.h"
#include "executable.h"

int main(int argc, char** argv) {
    char* fileName;
    char* message;
    KEY key;
    key.type = DECRYPT;

    if(argc == 1) {
        //need more arguments
        errorExit("KEY is missing\nUsage: ./decrypt KEY [fileName]\n");
    } else if(argc > 3) {
        //too many arguments
        errorExit("Too many arguments\nUsage: ./decrypt KEY [fileName]\n");
    }

    key.chars = argv[1];
    if(argc == 3) {
        fileName = argv[2];

        //read message from file
        FILE* file = fopen(fileName, "r");

        //TODO in while loop to get greater files
        message = readLineFromFile(file);
        if(message == NULL) {
            errorExit("Error: Could not read file");
        }

        removeNewLine(message);
        printf("Message from file: %s\n", message);

        decryptMessage(key, message);

        fclose(file);
    } else {
        //read message from command line
        message = malloc(BUFFER_SIZE * sizeof(char));
        printf("Enter your message: ");

        //TODO in loop to get more input
        if (fgets(message, BUFFER_SIZE, stdin) != 0) {
            decryptMessage(key, message);
        }
    }

    return 0;
}

void decryptMessage(KEY key, char* message) {
    int returnCode;
    char* output = malloc(BUFFER_SIZE * sizeof(char));

    removeNewLine(message);
    returnCode = decrypt(key, message, output);

    if(returnCode == 0) {
        printf("Decrypted Message: %s\n", output);
        cleanUp(message, output);
    } else if (returnCode == E_KEY_TOO_SHORT) {
        cleanUp(message, output);
        errorExit("Key is too short");
    } else if (returnCode == E_KEY_ILLEGAL_CHAR) {
        cleanUp(message, output);
        errorExit("Illegal char in KEY");
    } else if (returnCode == E_CYPHER_ILLEGAL_CHAR) {
        cleanUp(message, output);
        errorExit("Illegal char in encrypted Message");
    } else {
        cleanUp(message, output);
        errorExit("Unknown error");
    }
}