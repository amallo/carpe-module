#pragma once
#include <NimBLEServer.h>
#include <NimBLECharacteristic.h>
#include "core/peer/usecases/ReceiveMessageUseCase.h"
#include <vector>

/**
 * @brief Callback pour gérer la réception de messages via BLE
 */
class NimBLECharacteristicCallback : public NimBLECharacteristicCallbacks {
public:
    NimBLECharacteristicCallback(ReceiveMessageUseCase& useCase);
    
    void onWrite(NimBLECharacteristic* pCharacteristic) override;
    
private:
    ReceiveMessageUseCase* useCase;
};

