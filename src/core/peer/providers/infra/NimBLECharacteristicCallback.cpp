#include "NimBLECharacteristicCallback.h"
#include <vector>

NimBLECharacteristicCallback::NimBLECharacteristicCallback(ReceiveMessageUseCase& useCase) 
    : useCase(&useCase) {
}

void NimBLECharacteristicCallback::onWrite(NimBLECharacteristic* pCharacteristic) {
    if (!useCase || !pCharacteristic) {
        return;
    }
    
    // Récupérer les données reçues
    std::string value = pCharacteristic->getValue();
    if (value.length() == 0) {
        return;
    }
    
    // Convertir std::string en std::vector<uint8_t>
    std::vector<uint8_t> data(value.begin(), value.end());
    
    // Appeler le use case avec la source BLUETOOTH
    useCase->execute(data, ReceiveMessageUseCase::Source::BLUETOOTH);
}

