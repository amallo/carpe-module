#pragma once
#include <vector>
#include <cstdint>
#include <string>
#include <map>

// Forward declarations
class BluetoothProvider;
// class LoRaProvider;  // Future

/**
 * @brief Router simple pour diriger les messages entre différents protocoles
 * Permet le routage bidirectionnel BLE ↔ LoRa (futur)
 */
class MessageRouter {
private:
    BluetoothProvider* bluetoothProvider;
    // LoRaProvider* loraProvider;  // Future
    
public:
    MessageRouter();
    virtual ~MessageRouter() = default;
    
    /**
     * @brief Enregistrer un provider Bluetooth pour l'envoi
     * @param provider Pointeur vers le provider Bluetooth
     */
    void setBluetoothProvider(BluetoothProvider* provider);
    
    /**
     * @brief Router un message vers le protocole spécifié
     * @param message Les données binaires à envoyer
     * @param targetProtocol Le protocole cible ("bluetooth", "lora")
     * @return true si l'envoi a réussi, false sinon
     */
    bool routeMessage(const std::vector<uint8_t>& message, const std::string& targetProtocol);
    
    
    // Future: void setLoRaProvider(LoRaProvider* provider);
    
protected:
    /**
     * @brief Constructeur de copie interdit
     */
    MessageRouter(const MessageRouter&) = delete;
    
    /**
     * @brief Opérateur d'assignation interdit
     */
    MessageRouter& operator=(const MessageRouter&) = delete;
};
