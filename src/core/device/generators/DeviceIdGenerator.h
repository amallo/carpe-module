#pragma once
#include <string>

/**
 * @brief Interface pour la génération d'ID de device
 * Abstraction permettant différentes stratégies de génération (aléatoire, MAC, UUID, etc.)
 * Suit les principes de Clean Architecture avec Dependency Inversion
 */
class DeviceIdGenerator {
public:
    virtual ~DeviceIdGenerator() = default;
    
    /**
     * @brief Génère un ID unique pour le device
     * @return std::string ID généré selon la stratégie implémentée
     */
    virtual std::string generate() = 0;

protected:
    /**
     * @brief Constructeur protégé pour empêcher l'instanciation directe
     */
    DeviceIdGenerator() = default;
    
    /**
     * @brief Constructeur de copie interdit
     */
    DeviceIdGenerator(const DeviceIdGenerator&) = delete;
    
    /**
     * @brief Opérateur d'assignation interdit
     */
    DeviceIdGenerator& operator=(const DeviceIdGenerator&) = delete;
}; 