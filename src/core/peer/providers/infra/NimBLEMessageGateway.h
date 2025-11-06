#pragma once
#include "core/peer/providers/MessageGateway.h"
#include "core/peer/protocol/Message.h"

#ifdef NATIVE_BUILD
#include "test/transport/MockNimBLE.h"
#else
#include <NimBLEServer.h>
#include <NimBLECharacteristic.h>
#endif

class NimBLEMessageGateway : public MessageGateway {
public:
    NimBLEMessageGateway();
    void setCharacteristic(NimBLECharacteristic* characteristic);
    
    void send(const MessageInterface& message) override;
    
private:
    NimBLECharacteristic* characteristic;
};
