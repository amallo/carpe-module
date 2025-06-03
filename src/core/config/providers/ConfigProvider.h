#pragma once
#include <string>

/**
 * @brief Interface pour la gestion de configuration
 * Abstraction permettant différentes implémentations (NVS, fichiers, mémoire, etc.)
 * Suit les principes de Clean Architecture avec Dependency Inversion
 */
class ConfigProvider {
public:
    virtual ~ConfigProvider() = default;
    
    /**
     * @brief Récupère l'ID du device
     * @return std::string contenant l'ID du device
     */
    virtual std::string getDeviceId() = 0;
    
    /**
     * @brief Définit l'ID du device
     * @param id Nouvel ID du device
     */
    virtual void setDeviceId(const std::string& id) = 0;
     
protected:
    /**
     * @brief Constructeur protégé pour empêcher l'instanciation directe
     */
    ConfigProvider() = default;
    
    /**
     * @brief Constructeur de copie interdit
     */
    ConfigProvider(const ConfigProvider&) = delete;
    
    /**
     * @brief Opérateur d'assignation interdit
     */
    ConfigProvider& operator=(const ConfigProvider&) = delete;
}; 