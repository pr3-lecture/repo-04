//
// Created by martin on 30.12.17.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "crypto.h"
#include "crypto-test.h"

char* output = NULL;
int tests_run = 0;
char* message;
char* encryptedMessage;
KEY key;

static void initTests() {
    output = malloc(OUTPUT_LENGTH * sizeof(char));
    message = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    encryptedMessage = "URFVPJB[]ZN^XBJCEBVF@ZRKMJ";

    key.chars = "TPERULES";
}

static void endTests() {
    free(output);
}

static char* testEncrypt() {
    int resultCode;

    key.type = ENCRYPT;
    resultCode = encrypt(key, message, output);

    mu_assert("Encrypt failed", resultCode == 0 &&
                                    strcmp(output, encryptedMessage) == 0);

    return 0;
}

static char* testDecrypt() {
    int resultCode;

    key.type = DECRYPT;
    resultCode = decrypt(key, encryptedMessage, output);

    mu_assert("Decrypt failed", resultCode == 0 &&
                                    strcmp(output, message) == 0);

    return 0;
}

static char* testEnryptShortKey() {
    int resultCode;
    key.type = ENCRYPT;
    key.chars = "";

    resultCode = encrypt(key, message, output);

    mu_assert("Encrypting: too short key", resultCode == E_KEY_TOO_SHORT);

    return 0;
}

static char* testDecryptShortKey() {
    int resultCode;
    key.type = DECRYPT;
    key.chars = "";

    resultCode = decrypt(key, message, output);

    mu_assert("Decrypting: too short key", resultCode == E_KEY_TOO_SHORT);

    return 0;
}

static char* testEncryptWrongKeyCharacters() {
    int resultCode;
    key.type = ENCRYPT;
    key.chars = "AB1";

    resultCode = encrypt(key, message, output);

    mu_assert("Encrypting: illegal char key", resultCode == E_KEY_ILLEGAL_CHAR);

    return 0;
}

static char* testDecryptWrongKeyCharacters() {
    int resultCode;
    key.type = DECRYPT;
    key.chars = "AB1";

    resultCode = decrypt(key, message, output);

    mu_assert("Decrypting: illegal char key", resultCode == E_KEY_ILLEGAL_CHAR);

    return 0;
}

static char* testEncryptWrongMessageCharacters() {
    int resultCode;
    char* wrongMessage;

    key.type = ENCRYPT;
    key.chars = "TPERULES";
    wrongMessage = "ABC1";

    resultCode = encrypt(key, wrongMessage, output);

    mu_assert("Enrypting: illegal char message", resultCode == E_MESSAGE_ILLEGAL_CHAR);

    return 0;
}

static char* testDecryptWrongMessageCharacters() {
    int resultCode;
    char* wrongMessage;

    key.type = DECRYPT;
    key.chars = "TPERULES";
    wrongMessage = "ABC1";

    resultCode = decrypt(key, wrongMessage, output);

    mu_assert("Decrypting: illegal char cypher", resultCode == E_CYPHER_ILLEGAL_CHAR);

    return 0;
}

static char* allTests() {
    initTests();

    mu_run_test(testEncrypt);
    mu_run_test(testDecrypt);
    mu_run_test(testEnryptShortKey);
    mu_run_test(testDecryptShortKey);
    mu_run_test(testEncryptWrongKeyCharacters);
    mu_run_test(testDecryptWrongKeyCharacters);
    mu_run_test(testEncryptWrongMessageCharacters);
    mu_run_test(testDecryptWrongMessageCharacters);

    return 0;
}

int run() {
    initTests();

    char *result = allTests();

    if (result != 0)
        printf("%s\n", result);
    else
        printf("ALL TESTS PASSED\n");

    printf("Tests run: %d\n", tests_run);

    endTests();
    return result != 0;
}

int main() {
    run();
    return 0;
}