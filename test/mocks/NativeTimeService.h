#pragma once
#include "../TimeService.h"
#include <chrono>
#include <thread>

/**
 * @brief Implémentation native de TimeService utilisant std::chrono
 * Pour les tests sur desktop et environnements non-Arduino
 */
class NativeTimeService : public TimeService {
public:
    unsigned long getMicros() override {
        auto now = std::chrono::high_resolution_clock::now();
        auto duration = now.time_since_epoch();
        return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
    }
    
    void delay(unsigned long ms) override {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }
}; 