#pragma once
#include "core/device/providers/Screen.h"
#include "core/peer/providers/MessageGateway.h"
#include "core/peer/AuthChallengeStore.h"
#include "core/peer/model/AuthChallenge.h"
#include <string>

/**
 * @brief Use case pour gérer la négociation de PIN d'authentification
 * 
 * Règles de gestion :
 * - La négociation échoue si le code PIN ne correspond pas au bout de 3 tentatives
 * - La négociation réussit si le code PIN correspond
 * - La négociation est interrompue au bout de 1 minute
 * - La négociation s'arrête en cas d'interruption ou réussite
 */
class StartAuthChallengeNegociationUseCase {
public:
    StartAuthChallengeNegociationUseCase(Screen& screen, MessageGateway& messageGateway, AuthChallengeStore& challengeStore);
    ~StartAuthChallengeNegociationUseCase();
    
    /**
     * @brief Démarre une négociation pour un challenge donné
     * @param challengeId L'ID du challenge à négocier
     */
    void execute(const std::string& challengeId);
    
    
private:
    Screen* screen;
    MessageGateway* messageGateway;
    AuthChallengeStore* challengeStore;
    AuthChallenge* currentChallenge;
};
