#pragma once
#include "core/peer/providers/MessageGateway.h"
#include "core/peer/model/Message.h"
#include <NimBLEServer.h>
#include <NimBLECharacteristic.h>

class NimBLEMessageGateway : public MessageGateway {
public:
    NimBLEMessageGateway();
    void setCharacteristic(NimBLECharacteristic* characteristic);
    void send(Message* message) override;
    
private:
    NimBLECharacteristic* characteristic;
};
