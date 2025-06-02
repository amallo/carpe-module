#pragma once

#include <string>

/**
 * @brief Constantes Bluetooth centralisées
 * Évite la duplication des UUIDs et configurations
 */
namespace BluetoothConstants {
    // UUIDs standardisés
    constexpr const char* SERVICE_UUID = "12345678-1234-1234-1234-123456789abc";
    constexpr const char* CHARACTERISTIC_UUID = "87654321-4321-4321-4321-cba987654321";
    
    // Configuration BLE
    constexpr int MIN_PREFERRED_CONNECTION_INTERVAL = 0x06;
    constexpr int MAX_PREFERRED_CONNECTION_INTERVAL = 0x12;
    
    // Messages de debug
    namespace Messages {
        constexpr const char* SERVICE_STARTED = "ESP32BLE: Service started and advertising";
        constexpr const char* NOT_INITIALIZED = "ESP32BLE: Cannot %s - not properly initialized. Did you call ESP32BLEProvider::init() ?";
        constexpr const char* RECEIVED_PREFIX = "Received via BLE: ";
    }
    
    // Factory method pour créer des messages d'erreur
    inline std::string format_not_initialized_message(const std::string& action) {
        char buffer[256];
        snprintf(buffer, sizeof(buffer), Messages::NOT_INITIALIZED, action.c_str());
        return std::string(buffer);
    }
} 