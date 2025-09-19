#pragma once
#include <core/random/providers/RandomProvider.h>
#include <esp_system.h>  // esp_random

/**
 * SecureRandomProvider
 * Implémentation basée sur le RNG matériel de l'ESP32 via esp_random().
 * Fournit un entier uniforme dans [min, max) avec rejection sampling
 * pour éviter le modulo bias.
 */
class SecureRandomProvider : public RandomProvider {
public:
    int getRandomInt(int min, int max) override {
        if (max <= min) {
            return min;
        }
        const uint32_t range = static_cast<uint32_t>(max - min);
        // Limite supérieure multiple de range pour éviter le biais
        const uint32_t limit = (UINT32_MAX / range) * range;
        uint32_t r;
        do {
            r = esp_random();
        } while (r >= limit);
        return static_cast<int>(min + (r % range));
    }

    void setSeed(unsigned long /*seed*/) override {
        // Pas nécessaire avec le RNG matériel; ignoré intentionnellement
    }
};


