#pragma once
#include <NimBLEServer.h>
#include "core/peer/usecases/InitiateAuthChallengeUseCase.h"

class NimBLEConnectionCallback : public NimBLEServerCallbacks {
public:
    NimBLEConnectionCallback(InitiateAuthChallengeUseCase& useCase);
    
    void onConnect(NimBLEServer* pServer) override;
    
private:
    InitiateAuthChallengeUseCase* useCase;
};
