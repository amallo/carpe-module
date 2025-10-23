#include "NimBLEConnectionCallback.h"

NimBLEConnectionCallback::NimBLEConnectionCallback(InitiateAuthChallengeUseCase& useCase) 
    : useCase(&useCase) {
}

void NimBLEConnectionCallback::onConnect(NimBLEServer* pServer) {
    // Déclencher le cas d'utilisation d'initiation de challenge
    if (useCase) {
        useCase->execute("connected_device");
    }
}
