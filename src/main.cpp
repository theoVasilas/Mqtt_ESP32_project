#include <Arduino.h>

#include "crypto_engine.h"
#include "helper_fun.h"
#include "crypto_config.h"

static uint8_t plaintext_block[CHACHA_BLOCK_SIZE];
static uint8_t ciphertext_block[CHACHA_BLOCK_SIZE];
static uint8_t auth_tag[CHACHA_TAG_SIZE];
static uint8_t nonce[CHACHA_NONCE_SIZE];

void setup() {
    Serial.begin(9600);

    memset(plaintext_block, 0x00, CHACHA_BLOCK_SIZE);
    strcpy((char*)plaintext_block, "HELLO ESP32 CHACHA");

    Cha_encryption(plaintext_block, ciphertext_block, auth_tag, nonce);

    print_hex("Ciphertext: ", ciphertext_block, 64);
    print_hex("Tag: ", auth_tag, CHACHA_TAG_SIZE);

    monitorMemory();
}

void loop() {}