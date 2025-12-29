#ifndef CRYPTO_ENGINE_H
#define CRYPTO_ENGINE_H

#define CHACHA_BLOCK_SIZE   256 //(20 * 256)= 10 KB

#define CHACHA_NONCE_SIZE   12
#define CHACHA_KEY_SIZE     32
#define CHACHA_TAG_SIZE     16

#include <ChaChaPoly.h>
#include <stdint.h>

void generate_nonce(uint8_t nonce[12]);

void Cha_encryption(
    const uint8_t * plaintext,
    uint8_t * ciphertext,
    uint8_t * tag,
    const uint8_t * nonce
);

bool Cha_decryption(
    const uint8_t * ciphertext,
    uint8_t * decrypted,
    const uint8_t * tag,
    const uint8_t *nonce
);

#endif
