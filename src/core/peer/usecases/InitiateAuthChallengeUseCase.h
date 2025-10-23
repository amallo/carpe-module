
#pragma once
#include <string>
#include "core/device/providers/Screen.h"
#include "core/peer/ChallengeGenerator.h"
#include "core/peer/MessageGateway.h"
#include "core/peer/AuthChallengeStore.h"

class InitiateAuthChallengeUseCase {
   
    public:
        InitiateAuthChallengeUseCase(Screen& screen, ChallengeGenerator& challengeGenerator, MessageGateway& messageGateway, AuthChallengeStore& challengeStore);
        ~InitiateAuthChallengeUseCase();
        void execute(const std::string& deviceAddress);
    
    private:
        Screen* screen;
        ChallengeGenerator* challengeGenerator;
        MessageGateway* messageGateway;
        AuthChallengeStore* challengeStore;
};