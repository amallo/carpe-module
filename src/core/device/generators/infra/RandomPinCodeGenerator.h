#pragma once
#include "../../PinCodeGenerator.h"
#include <core/random/providers/RandomProvider.h>
#include <string>

/**
 * @brief Générateur de code PIN aléatoire
 * Génère des codes PIN de 4 chiffres en utilisant un RandomProvider
 */
class RandomPinCodeGenerator : public PinCodeGenerator {
private:
    RandomProvider* randomProvider;
    
public:
    /**
     * @brief Constructeur
     * @param randomProvider Provider pour la génération de nombres aléatoires
     */
    explicit RandomPinCodeGenerator(RandomProvider* randomProvider);
    
    /**
     * @brief Destructeur virtuel
     */
    virtual ~RandomPinCodeGenerator() = default;
    
    /**
     * @brief Génère un code PIN de 4 chiffres
     * @return Code PIN généré (format "XXXX")
     */
    std::string generatePinCode() override;
};
