#pragma once
#include "core/peer/protocol/Message.h"

/**
 * @brief Interface pour l'envoi de messages
 */
class MessageGateway {
public:
    virtual ~MessageGateway() = default;
    
    /**
     * @brief Envoyer un message générique
     * @param message Le message à envoyer
     */
    virtual void send(const MessageInterface& message) = 0;
};
