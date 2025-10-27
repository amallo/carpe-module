#include "ESP32CommonIDGenerator.h"
#include <string>
#include <sstream>
#include <iomanip>

#ifdef ESP32
#include "esp_random.h"
#else
#include <random>
#include <chrono>
#endif

std::string ESP32CommonIDGenerator::generate() {
    return generateUUID();
}

std::string ESP32CommonIDGenerator::generateUUID() {
    std::string result;
    result.reserve(36);
    
#ifdef ESP32
    // Utilisation de l'entropie hardware ESP32
    for (int i = 0; i < 8; i++) {
        result += "0123456789abcdef"[esp_random() % 16];
    }
    result += "-";
    
    for (int i = 0; i < 4; i++) {
        result += "0123456789abcdef"[esp_random() % 16];
    }
    result += "-4"; // Version 4
    
    for (int i = 0; i < 3; i++) {
        result += "0123456789abcdef"[esp_random() % 16];
    }
    result += "-";
    
    // 1 caractère (8-11)
    result += "89ab"[esp_random() % 4];
    for (int i = 0; i < 3; i++) {
        result += "0123456789abcdef"[esp_random() % 16];
    }
    result += "-";
    
    for (int i = 0; i < 12; i++) {
        result += "0123456789abcdef"[esp_random() % 16];
    }
#else
    // Fallback pour compilation native (tests)
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 15);
    static std::uniform_int_distribution<> dis2(8, 11);
    
    std::stringstream ss;
    ss << std::hex;
    
    for (int i = 0; i < 8; i++) ss << dis(gen);
    ss << "-";
    for (int i = 0; i < 4; i++) ss << dis(gen);
    ss << "-4";
    for (int i = 0; i < 3; i++) ss << dis(gen);
    ss << "-";
    ss << dis2(gen);
    for (int i = 0; i < 3; i++) ss << dis(gen);
    ss << "-";
    for (int i = 0; i < 12; i++) ss << dis(gen);
    
    result = ss.str();
#endif
    
    return result;
}
