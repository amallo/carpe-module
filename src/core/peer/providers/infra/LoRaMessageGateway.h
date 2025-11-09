#pragma once
#include "core/peer/providers/MessageGateway.h"
#include "core/peer/protocol/Message.h"
#include <LoRa.h>

/**
 * @brief Gateway pour l'envoi de messages via LoRa
 */
class LoRaMessageGateway : public MessageGateway {
public:
    LoRaMessageGateway();
    
    /**
     * @brief Initialise LoRa (doit être appelé avant d'utiliser send)
     * @param frequency Fréquence LoRa en Hz (ex: 868E6 pour 868 MHz)
     * @param nss Pin NSS (ex: 18)
     * @param rst Pin RST (ex: 14)
     * @param dio0 Pin DIO0 (ex: 26)
     * @return true si l'initialisation a réussi, false sinon
     */
    bool begin(long frequency, int nss = 18, int rst = 14, int dio0 = 26);
    
    void send(const MessageInterface& message) override;
    
private:
    bool initialized;
};

