#pragma once
#include "core/peer/protocol/decoders/MessageDecoder.h"
#include "core/peer/providers/MessageGateway.h"
#include <vector>
#include <cstdint>

/**
 * @brief Use case pour gérer la réception de messages
 * 
 * Règles de gestion :
 * - Décode les données binaires reçues
 * - Valide le message décodé
 * - Forward le message valide vers l'autre transport :
 *   * Si reçu depuis Bluetooth → redirige vers LoRa
 *   * Si reçu depuis LoRa → redirige vers Bluetooth
 * - Rejette les messages invalides
 */
class ReceiveMessageUseCase {
public:
    enum class Source {
        BLUETOOTH,
        LORA
    };
    
    ReceiveMessageUseCase(MessageDecoder& decoder, MessageGateway& bluetoothGateway, MessageGateway& loraGateway);
    ~ReceiveMessageUseCase();
    
    /**
     * @brief Traite un message reçu
     * @param data Données binaires complètes (HEADER + PAYLOAD)
     * @param source Source du message (BLUETOOTH ou LORA)
     * @return true si le message a été traité avec succès, false sinon
     */
    bool execute(const std::vector<uint8_t>& data, Source source);
    
private:
    MessageDecoder* decoder;
    MessageGateway* bluetoothGateway;
    MessageGateway* loraGateway;
};

