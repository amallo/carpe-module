
#pragma once
#include <string>
#include "core/device/providers/Screen.h"
#include "core/peer/ChallengeGenerator.h"
#include "core/peer/MessageGateway.h"

class PeerBeginConnectionUseCase {
   
    public:
        PeerBeginConnectionUseCase(Screen& screen, ChallengeGenerator& challengeGenerator, MessageGateway& messageGateway);
        ~PeerBeginConnectionUseCase();
        void execute(const std::string& deviceAddress);
    
    private:
        Screen* screen;
        ChallengeGenerator* challengeGenerator;
        MessageGateway* messageGateway;
};