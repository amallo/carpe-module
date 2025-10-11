#pragma once

#include <string>

/**
 * @brief Interface pour l'affichage sur différents types d'écrans
 * Abstraction permettant d'utiliser OLED, LCD, TFT, ou même Serial
 */
class Screen {
public:
    /**
     * @brief Destructeur virtuel pour assurer une destruction propre
     */
    virtual ~Screen() = default;
    
    /**
     * @brief Initialise l'écran
     * @return true si l'initialisation réussit
     */
    virtual bool init() = 0;
    
    /**
     * @brief Efface l'écran
     */
    virtual void clear() = 0;
    
    /**
     * @brief Affiche un message sur l'écran
     * @param message le message à afficher
     */
    virtual void showMessage(const std::string& message) = 0;
    
    /**
     * @brief Affiche un message d'erreur
     * @param error le message d'erreur à afficher
     */
    virtual void showError(const std::string& error) = 0;
    
    /**
     * @brief Affiche un statut système
     * @param status le statut à afficher
     */
    virtual void showStatus(const std::string& status) = 0;
    
    /**
     * @brief Met à jour l'affichage (pour les écrans bufferisés)
     */
    virtual void update() = 0;
    
    /**
     * @brief Affiche un défi de code PIN pour l'authentification
     * @param pinCode le code PIN à afficher
     */
    virtual void displayPinCodeChallenge(const std::string& pinCode) = 0;

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