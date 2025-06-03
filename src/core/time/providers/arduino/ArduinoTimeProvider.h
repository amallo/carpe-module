#pragma once
#include <core/time/providers/TimeProvider.h>
#include <Arduino.h>

/**
 * @brief Implémentation Arduino de TimeService utilisant micros() et delay()
 * Pour le hardware ESP32 et environnements Arduino
 */
class ArduinoTimeProvider : public TimeProvider {
public:
    unsigned long getMicros() override {
        return micros();
    }
    
    void delay(unsigned long ms) override {
        ::delay(ms);
    }
}; 