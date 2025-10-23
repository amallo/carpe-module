
#pragma once
#include <string>
#include "core/device/providers/Screen.h"
#include "core/peer/AuthChallengeGenerator.h"
#include "core/peer/MessageGateway.h"
#include "core/peer/AuthChallengeStore.h"

class InitiateAuthChallengeUseCase {
   
    public:
        InitiateAuthChallengeUseCase(Screen& screen, AuthChallengeGenerator& challengeGenerator, MessageGateway& messageGateway, AuthChallengeStore& challengeStore);
        ~InitiateAuthChallengeUseCase();
        void execute(const std::string& deviceAddress);
    
    private:
        Screen* screen;
        AuthChallengeGenerator* challengeGenerator;
        MessageGateway* messageGateway;
        AuthChallengeStore* challengeStore;
};