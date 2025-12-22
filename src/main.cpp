#include <Arduino.h>
#include <ChaChaPoly.h>

// Helper to print hex buffers
void print_hex(const char *label, uint8_t *buf, size_t len) {
    Serial.print(label);
    for (size_t i = 0; i < len; i++) {
        Serial.printf("%02x", buf[i]);
    }
    Serial.println();
}

// 32-byte key
static const uint8_t key[32] = {
    0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
    0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,
    0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,
    0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38
};

// 12-byte nonce
static uint8_t nonce[12] = {0,0,0,1,2,3,4,5,6,7,8,9};

void setup() {
    Serial.begin(9600);
    delay(2000);

    const char* plaintext = "Hello ESP32!";
    size_t len = strlen(plaintext);
    
    uint8_t ciphertext[len];
    uint8_t decrypted[len + 1];
    uint8_t tag[16];

    ChaChaPoly chacha;

    // --- ENCRYPTION ---
    chacha.clear();
    chacha.setKey(key, 32);
    chacha.setIV(nonce, 12);
    
    // Add AAD (Optional)
    const char* aad = "header";
    chacha.addAuthData(aad, strlen(aad));

    chacha.encrypt(ciphertext, (const uint8_t*)plaintext, len);
    chacha.computeTag(tag, 16);

    Serial.println("--- Encrypted ---");
    print_hex("Cipher: ", ciphertext, len);
    print_hex("Tag:    ", tag, 16);

    // --- DECRYPTION ---
    chacha.clear();
    chacha.setKey(key, 32);
    chacha.setIV(nonce, 12);
    chacha.addAuthData(aad, strlen(aad));

    chacha.decrypt(decrypted, ciphertext, len);
    
    // checkTag returns true if the message is authentic
    if (chacha.checkTag(tag, 16)) {
        decrypted[len] = '\0';
        Serial.print("Decrypted: ");
        Serial.println((char*)decrypted);
    } else {
        Serial.println("AUTHENTICATION FAILED!");
    }
}

void loop() {}