#pragma once
#include "core/device/generators/CommonIDGenerator.h"
#include <vector>
#include <string>

/**
 * @brief Mock pour CommonIDGenerator utilisé dans les tests
 * 
 * Permet de contrôler les identifiants générés pour les tests
 * et de vérifier les appels à la génération d'identifiants.
 */
class MockCommonIDGenerator : public CommonIDGenerator {
public:
    MockCommonIDGenerator();
    ~MockCommonIDGenerator() override = default;
    
    /**
     * @brief Génère un identifiant prédéfini
     * @return L'identifiant suivant dans la liste prédéfinie
     */
    std::string generate() override;
    
    /**
     * @brief Ajoute un identifiant à la liste des identifiants à retourner
     * @param id L'identifiant à ajouter
     */
    void scheduleID(const std::string& id);
    
    /**
     * @brief Vérifie si generate() a été appelé
     * @return true si generate() a été appelé au moins une fois
     */
    bool wasGenerateCalled() const;
    
    /**
     * @brief Retourne le nombre d'appels à generate()
     * @return Le nombre d'appels
     */
    int getGenerateCallCount() const;
  

private:
    std::vector<std::string> scheduledIDs;
    int currentIndex;
    int generateCallCount;
};
