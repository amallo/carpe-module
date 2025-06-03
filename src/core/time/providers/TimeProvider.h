#pragma once
#include <cstdint>

/**
 * @brief Interface pour les services de temps
 * Abstraction permettant d'injecter différentes implémentations (Arduino micros(), time(), etc.)
 */
class TimeProvider {
public:
    virtual ~TimeProvider() = default;
    
    /**
     * @brief Retourne le temps en microsecondes depuis le démarrage
     * @return unsigned long temps en microsecondes
     */
    virtual unsigned long getMicros() = 0;
    
    /**
     * @brief Fait une pause
     * @param ms durée en millisecondes
     */
    virtual void delay(unsigned long ms) = 0;

protected:
    TimeProvider() = default;
    TimeProvider(const TimeProvider&) = delete;
    TimeProvider& operator=(const TimeProvider&) = delete;
}; 