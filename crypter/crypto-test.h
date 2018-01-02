//
// Created by martin on 30.12.17.
//

#ifndef __CRYPTO_TEST_H__
#define __CRYPTO_TEST_H__

#define mu_assert(message, test) do { if (!(test)) return message; } while(0)
#define mu_run_test(test) do { char *message = test(); tests_run++; \
                                if (message) return message; } while (0)

#define OUTPUT_LENGTH 27

static void initTests();

static char* testEncrypt();

static char* testDecrypt();

static char* testEnryptShortKey();

static char* testDecryptShortKey();

static char* testEncryptWrongKeyCharacters();

static char* testDecryptWrongKeyCharacters();

static char* testEncryptWrongMessageCharacters();

static char* testDecryptWrongMessageCharacters();

static char* allTests();

int run();

#endif /* __CRYPTO_TEST_H__ */
