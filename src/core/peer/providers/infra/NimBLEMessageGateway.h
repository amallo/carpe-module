#pragma once
#include "core/peer/providers/MessageGateway.h"
#include "core/peer/model/Message.h"

class NimBLEMessageGateway : public MessageGateway {
public:
    void send(Message* message) override;
};
