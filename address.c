#include "nimiq_native.h"

void toBase32(char* out, const unsigned char* in, const size_t inlen) {
    const char alphabet[] = "0123456789ABCDEFGHJKLMNPQRSTUVXY";
    unsigned int shift = 3;
    unsigned int carry = 0;
    unsigned char byte;
    char symbol;

    int j = 0;
    for (int i = 0; i < inlen; ++i) {
        byte = in[i];
        symbol = carry | (byte >> shift);
        out[j] = alphabet[symbol & 0x1f];
        ++j;

        if (shift > 5) {
            shift -= 5;
            symbol = byte >> shift;
            out[j] = alphabet[symbol & 0x1f];
            ++j;
        }

        shift = 5 - shift;
        carry = byte << shift;
        shift = 8 - shift;
    }

    if (shift != 3) {
        out[j] = alphabet[carry & 0x1f];
        ++j;
    }
}

void toUserFriendlyAddress(char* address, const unsigned char* publicKey) {
    unsigned char out[32];
    nimiq_light_hash(out, publicKey, 32);
    toBase32(address, out, 20);
}