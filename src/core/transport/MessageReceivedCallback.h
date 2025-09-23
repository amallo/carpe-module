#pragma once
#include <vector>
#include <cstdint>
#include <string>

/**
 * @brief Interface commune pour tous les callbacks de réception de messages
 * Permet l'unification de la réception entre différents protocoles (Bluetooth, LoRa, etc.)
 */
class MessageReceivedCallback {
public:
    virtual ~MessageReceivedCallback() = default;
    
    /**
     * @brief Callback appelé lors de la réception d'un message
     * @param message Les données binaires du message reçu
     * @param source Le protocole source du message (ex: "bluetooth", "lora")
     */
    virtual void onMessageReceived(const std::vector<uint8_t>& message, const std::string& source) = 0;
    
protected:
    /**
     * @brief Constructeur protégé pour empêcher l'instanciation directe
     */
    MessageReceivedCallback() = default;
    
    /**
     * @brief Constructeur de copie interdit
     */
    MessageReceivedCallback(const MessageReceivedCallback&) = delete;
    
    /**
     * @brief Opérateur d'assignation interdit
     */
    MessageReceivedCallback& operator=(const MessageReceivedCallback&) = delete;
};
