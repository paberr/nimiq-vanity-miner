#include "address.h"
#include "ed25519/ed25519.h"
#include "ed25519/sc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void printHex(const unsigned char* v, size_t len) {
    for (size_t i = 0; i < len; i++)
    {
        printf("%02X", v[i]);
    }
    printf("\n");
}

void printString(const char* v, size_t len) {
    for (size_t i = 0; i < len; i++)
    {
        printf("%c", v[i]);
    }
    printf("\n");
}

void canonicalForm(char* str, size_t len) {
    for (size_t i = 0; i < len; i++)
    {
        switch (str[i]) {
            case '0':
                str[i] = 'O';
                break;
            case '1':
                str[i] = 'I';
                break;
            case '2':
                str[i] = 'Z';
                break;
            case '3':
                str[i] = 'E';
                break;
            case '4':
                str[i] = 'A';
                break;
            case '5':
                str[i] = 'S';
                break;
            case '6':
                str[i] = 'G';
                break;
            case '7':
                str[i] = 'T';
                break;
        }
    }
}

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        printf("Usage: vanity_generate prefix [max_rounds] [--exact-match]\n");
        return 0;
    }
    // Parse command line arguments.
    const size_t prefix_len = strlen(argv[1]);
    char prefix[prefix_len];
    strncpy(prefix, argv[1], prefix_len);
    int max_rounds = -1;
    bool exact_match = false;
    for (int current=2; current<argc; ++current) {
        if (argv[current][0] == '-' && strcmp(argv[current], "--exact-match") == 0) {
            exact_match = true;
        } else {
            max_rounds = atoi(argv[2]);
        }
    }

    // Put prefix in canonical form, if close matches are allowed.
    if (!exact_match) {
        canonicalForm(prefix, prefix_len);
    }

    // Scalar helper.
    const unsigned char SC_1[32] = {1}; /* scalar with value 1 */

    unsigned char privateKey[32];
    unsigned char publicKey[32];
    char address[32];
    // Create initial seed.
    ed25519_create_seed(privateKey);
    for (int i=0; max_rounds<0 || i<max_rounds; ++i) {
        ed25519_public_key_derive(publicKey, privateKey);
        toUserFriendlyAddress(address, publicKey);

        if (!exact_match) {
            canonicalForm(address, 32);
        }

        if (strncmp(prefix, address, prefix_len) == 0) {
            // Restore original address in case of match.
            toUserFriendlyAddress(address, publicKey);

            printf("Address found:\n");
            printString(address, 32);
            printHex(privateKey, 32);
            return 0;
        }

        // Next private key.
        ed25519_add_scalars(privateKey, privateKey, SC_1);
        if (i % 10000 == 0) printf("%d\n", i);
    }

    // Bad luck.
    printf("No address found.\n");
    return 0;
}