#pragma once
#include <stdexcept>
#include <string>

// Constantes pour les messages d'erreur Bluetooth
namespace BluetoothErrorMessages {
    constexpr const char* MAX_ATTEMPTS_EXCEEDED = "Maximum authentication attempts exceeded";
    constexpr const char* INVALID_PIN = "Invalid PIN code provided";
    constexpr const char* NOT_AUTHENTICATED = "Device not authenticated";
    constexpr const char* CONNECTION_FAILED = "Bluetooth connection failed";
    constexpr const char* CONNECTION_TIMEOUT = "Bluetooth connection timeout";
    constexpr const char* DEVICE_NOT_FOUND = "Bluetooth device not found";
    constexpr const char* UNKNOWN_ERROR = "Unknown Bluetooth error";
}

/**
 * @brief Erreurs spécifiques aux connexions Bluetooth
 * Enumération des types d'erreurs possibles lors des connexions BLE
 */
enum class BluetoothErrorType {
    MaxAttempts,        // Trop de tentatives d'authentification
    InvalidPin,         // PIN invalide
    NotAuthenticated,   // Non authentifié
    ConnectionFailed,   // Échec de connexion
    Timeout,           // Timeout de connexion
    DeviceNotFound     // Périphérique non trouvé
};

/**
 * @brief Exception spécifique aux erreurs de connexion Bluetooth
 * Hérite de std::runtime_error pour une gestion d'erreur standard
 */
class BluetoothConnectionError : public std::runtime_error {
private:
    BluetoothErrorType errorType;
    
public:
    /**
     * @brief Constructeur avec type d'erreur et message
     * @param type Type d'erreur Bluetooth
     * @param message Message d'erreur détaillé
     */
    BluetoothConnectionError(BluetoothErrorType type, const std::string& message)
        : std::runtime_error(message), errorType(type) {}
    
    /**
     * @brief Constructeur avec type d'erreur seulement
     * @param type Type d'erreur Bluetooth
     */
    BluetoothConnectionError(BluetoothErrorType type)
        : std::runtime_error(getDefaultMessage(type)), errorType(type) {}
    
    /**
     * @brief Récupère le type d'erreur
     * @return Type d'erreur Bluetooth
     */
    BluetoothErrorType getErrorType() const {
        return errorType;
    }
    
    /**
     * @brief Récupère le message par défaut selon le type d'erreur
     * @param type Type d'erreur
     * @return Message par défaut
     */
    static std::string getDefaultMessage(BluetoothErrorType type) {
        switch (type) {
            case BluetoothErrorType::MaxAttempts:
                return BluetoothErrorMessages::MAX_ATTEMPTS_EXCEEDED;
            case BluetoothErrorType::InvalidPin:
                return BluetoothErrorMessages::INVALID_PIN;
            case BluetoothErrorType::NotAuthenticated:
                return BluetoothErrorMessages::NOT_AUTHENTICATED;
            case BluetoothErrorType::ConnectionFailed:
                return BluetoothErrorMessages::CONNECTION_FAILED;
            case BluetoothErrorType::Timeout:
                return BluetoothErrorMessages::CONNECTION_TIMEOUT;
            case BluetoothErrorType::DeviceNotFound:
                return BluetoothErrorMessages::DEVICE_NOT_FOUND;
            default:
                return BluetoothErrorMessages::UNKNOWN_ERROR;
        }
    }
};
