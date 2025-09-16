#pragma once
#include <core/device/PinCodeGenerator.h>
#include <string>
#include <vector>

/**
 * @brief Mock pour PinCodeGenerator pour les tests
 * Permet de programmer des codes PIN spécifiques pour les tests
 */
class MockPinCodeGenerator : public PinCodeGenerator {
private:
    std::vector<std::string> scheduledPinCodes;
    int currentIndex;
    
public:
    MockPinCodeGenerator();
    virtual ~MockPinCodeGenerator() = default;
    
    /**
     * @brief Génère le prochain code PIN programmé
     * @return Code PIN programmé ou "0000" par défaut
     */
    std::string generatePinCode() override;
    
    /**
     * @brief Programme un code PIN spécifique pour le prochain appel
     * @param pinCode Code PIN à retourner
     */
    void scheduleGeneratedPinCode(const std::string& pinCode);
    
    /**
     * @brief Programme plusieurs codes PIN en séquence
     * @param pinCodes Vecteur de codes PIN
     */
    void scheduleGeneratedPinCodes(const std::vector<std::string>& pinCodes);
    
    /**
     * @brief Remet à zéro le générateur
     */
    void reset();
    
    /**
     * @brief Vérifie si des codes PIN ont été générés
     * @return true si au moins un code a été généré
     */
    bool wasGenerateCalled() const;
    
    /**
     * @brief Retourne le nombre de codes PIN générés
     * @return Nombre d'appels à generatePinCode()
     */
    int getGenerateCallCount() const;
};
