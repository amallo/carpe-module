#pragma once
#include <Arduino.h>

/**
 * @brief Interface pour la gestion de configuration
 * Abstraction permettant différentes implémentations (NVS, fichiers, mémoire, etc.)
 */
class ConfigManager {
public:
    virtual ~ConfigManager() = default;
    
    /**
     * @brief Charge les valeurs de configuration depuis le stockage
     * @return true si le chargement a réussi, false sinon
     */
    virtual bool loadConfig() = 0;
    
    /**
     * @brief Sauvegarde les valeurs de configuration dans le stockage
     * @return true si la sauvegarde a réussi, false sinon
     */
    virtual bool saveConfig() = 0;
    
    /**
     * @brief Récupère l'ID du device
     * @return String contenant l'ID du device
     */
    virtual String getDeviceId() = 0;
    
    /**
     * @brief Définit l'ID du device
     * @param id Nouvel ID du device
     */
    virtual void setDeviceId(const String& id) = 0;
    
    /**
     * @brief Affiche la configuration actuelle (pour debug)
     */
    virtual void printConfig() = 0;
    
protected:
    /**
     * @brief Constructeur protégé pour empêcher l'instanciation directe
     */
    ConfigManager() = default;
    
    /**
     * @brief Constructeur de copie interdit
     */
    ConfigManager(const ConfigManager&) = delete;
    
    /**
     * @brief Opérateur d'assignation interdit
     */
    ConfigManager& operator=(const ConfigManager&) = delete;
}; 