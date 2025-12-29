#include "helper_fun.h"
#include <Arduino.h>
#include <esp_system.h>

// Helper to print hex buffers
void print_hex(const char *label, uint8_t *buf, size_t len) {
    Serial.print(label);
    for (size_t i = 0; i < len; i++) {
        Serial.printf("%02x", buf[i]);
    }
    Serial.println();
}

void print_ASCII(const char *label, uint8_t *buf, size_t len) {
    Serial.print(label);
    for (size_t i = 0; i < len; i++) {
        Serial.printf("%c", buf[i]);
    }
    Serial.println();
}

void monitorMemory() {
    Serial.printf("Free Heap: %d bytes\n", ESP.getFreeHeap());
    Serial.printf("Min Free Heap: %d bytes\n", ESP.getMinFreeHeap()); // Lowest point reached
    Serial.printf("Max Alloc Block: %d bytes\n", ESP.getMaxAllocHeap()); // Largest single chunk available
}

