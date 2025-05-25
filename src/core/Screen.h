#pragma once
#include <Arduino.h>

/**
 * @brief Interface pure pour l'affichage d'écran
 */
class Screen {
public:
    /**
     * @brief Destructeur virtuel pour assurer une destruction propre
     */
    virtual ~Screen() = default;
    
    /**
     * @brief Initialise l'écran
     */
    virtual bool begin() = 0;
    
    /**
     * @brief Efface complètement l'écran
     */
    virtual void clear() = 0;
    
    /**
     * @brief Affiche un message standard
     */
    virtual void showMessage(const String& message) = 0;
    
    /**
     * @brief Affiche un message d'erreur
     */
    virtual void showError(const String& error) = 0;
    
    /**
     * @brief Affiche un statut système
     */
    virtual void showStatus(const String& status) = 0;
    
    /**
     * @brief Met à jour l'affichage physique
     */
    virtual void update() = 0;

protected:
    /**
     * @brief Constructeur protégé pour empêcher l'instanciation directe
     */
    Screen() = default;
    
    /**
     * @brief Constructeur de copie interdit
     */
    Screen(const Screen&) = delete;
    
    /**
     * @brief Opérateur d'assignation interdit
     */
    Screen& operator=(const Screen&) = delete;
}; 