#pragma once
#include <string>

/**
 * @brief Interface pour la génération de codes PIN
 * Abstraction permettant de générer des codes PIN pour l'authentification
 */
class PinCodeGenerator {
public:
    virtual ~PinCodeGenerator() = default;
    
    /**
     * @brief Génère un nouveau code PIN
     * @return Code PIN généré (format string)
     */
    virtual std::string generatePinCode() = 0;
    
protected:
    /**
     * @brief Constructeur protégé pour empêcher l'instanciation directe
     */
    PinCodeGenerator() = default;
    
    /**
     * @brief Constructeur de copie interdit
     */
    PinCodeGenerator(const PinCodeGenerator&) = delete;
    
    /**
     * @brief Opérateur d'assignation interdit
     */
    PinCodeGenerator& operator=(const PinCodeGenerator&) = delete;
};
