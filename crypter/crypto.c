//
// Created by martin on 30.12.17.
//

#include "crypto.h"
#include <stdio.h>
#include <string.h>

int checkKey(char* key) {
    char* keyPos;

    if(!strlen(key))
        return E_KEY_TOO_SHORT;

    for(keyPos = key; *keyPos; keyPos++) {
        if(!strchr(KEY_CHARACTERS, *keyPos)) {
            return E_KEY_ILLEGAL_CHAR;
        }
    }

    return 0;
}

int encrypt(KEY key, const char* input, char* output) {
    char *inputPos;
    char* keyPos = key.chars;
    char* outputPos = output;
    int posInCrypterCharacters;

    char* inputPosInMessageCharacters;

    int checkKeyCode = checkKey(key.chars);
    if(checkKeyCode != 0)
        return checkKeyCode;

    for(inputPos = (char *) input; *inputPos; inputPos++) {
        inputPosInMessageCharacters = strchr(MESSAGE_CHARACTERS, *inputPos);
        if(!inputPosInMessageCharacters) {
            return E_MESSAGE_ILLEGAL_CHAR;
        }

        posInCrypterCharacters = ((inputPosInMessageCharacters - (MESSAGE_CHARACTERS)) + 1) ^
                                 ((strchr(KEY_CHARACTERS, *keyPos) - (KEY_CHARACTERS)) + 1);

        *outputPos = CYPHER_CHARACTERS[posInCrypterCharacters];
        outputPos++;
        keyPos++;

        //reuse key when end is reached
        if(!*keyPos) {
            keyPos = key.chars;
        }
    }

    return 0;
}

int decrypt(KEY key, const char* cypherText, char* output) {
    char* inputPos;
    char* keyPos = key.chars;
    char* outputPos = output;
    int posInMessageCharacters;

    char* inputPosInCrypterCharacters;

    int checkKeyCode = checkKey(key.chars);
    if(checkKeyCode != 0)
        return checkKeyCode;

    for(inputPos = (char *) cypherText; *inputPos; inputPos++) {
        inputPosInCrypterCharacters = strchr(CYPHER_CHARACTERS, *inputPos);
        if(!inputPosInCrypterCharacters) {
            return E_CYPHER_ILLEGAL_CHAR;
        }

        posInMessageCharacters = ((inputPosInCrypterCharacters - (CYPHER_CHARACTERS))) ^
                                 ((strchr(KEY_CHARACTERS, *keyPos) - (KEY_CHARACTERS)) + 1);

        *outputPos = MESSAGE_CHARACTERS[posInMessageCharacters - 1];
        outputPos++;
        keyPos++;

        //reuse key when end is reached
        if(!*keyPos) {
            keyPos = key.chars;
        }
    }

    return 0;
}