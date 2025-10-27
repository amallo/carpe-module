#pragma once
#include <string>

/**
 * @brief Interface pour la génération d'identifiants communs
 * 
 * Utilisé pour générer des identifiants uniques pour :
 * - Les challenges d'authentification
 * - Les sessions utilisateur
 * - Tout autre identifiant nécessitant une unicité
 */
class CommonIDGenerator {
public:
    virtual ~CommonIDGenerator() = default;
    
    /**
     * @brief Génère un identifiant unique
     * @return Un identifiant unique sous forme de string
     */
    virtual std::string generate() = 0;
};
