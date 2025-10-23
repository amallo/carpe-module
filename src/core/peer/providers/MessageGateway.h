#pragma once
#include "core/peer/model/Message.h"

/**
 * @brief Interface pour l'envoi de messages
 */
class MessageGateway {
public:
    virtual ~MessageGateway() = default;
    virtual void send(Message* message) = 0;
};
