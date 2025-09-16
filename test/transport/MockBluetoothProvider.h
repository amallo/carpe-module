#pragma once
#include <core/transport/providers/BluetoothProvider.h>
#include <core/transport/BluetoothConnectionError.h>
#include <string>

/**
 * @brief Mock pour tester l'authentification PIN Bluetooth
 * Simule le comportement d'un provider Bluetooth avec authentification
 */
class MockBluetoothProvider : public BluetoothProvider {
private:
    std::string expectedPin;
    bool isAuthenticated;
    bool authenticationAttempted;
    int authenticationAttempts;
    static const int MAX_AUTH_ATTEMPTS = 3;
    
public:
    MockBluetoothProvider() : isAuthenticated(false), authenticationAttempted(false), authenticationAttempts(0) {
        // PIN par défaut pour les tests
        expectedPin = "1234";
    }
    
    // Configuration du PIN attendu pour les tests
    void setExpectedPin(const std::string& pin) {
        expectedPin = pin;
    }
    
    // Simulation de l'authentification
    bool simulateAuthenticateWithPin(const std::string& providedPin) {
        authenticationAttempted = true;
        
        // Si on a déjà forcé le dépassement via shouldRaiseAnError, ne pas incrémenter
        if (authenticationAttempts <= MAX_AUTH_ATTEMPTS) {
            authenticationAttempts++;
        }
        
        if (authenticationAttempts > MAX_AUTH_ATTEMPTS) {
            return false; // Trop de tentatives
        }
        
        isAuthenticated = (providedPin == expectedPin);
        return isAuthenticated;
    }
    
    // Getters pour les tests
    bool getIsAuthenticated() const { return isAuthenticated; }
    bool getAuthenticationAttempted() const { return authenticationAttempted; }
    int getAuthenticationAttempts() const { return authenticationAttempts; }
    std::string getExpectedPin() const { return expectedPin; }
    
    // Gestion des erreurs pour les tests
    void shouldRaiseAnError(BluetoothErrorType expectedError) {
        // Simule une exception/erreur pour le test
        // Dans une vraie implémentation, cela pourrait lever une exception
        throw BluetoothConnectionError(expectedError);
    }
    
    // Implémentation des méthodes virtuelles (simulées)
    bool init(const std::string& deviceId) override { return true; }
    bool start() override { return true; }
    bool sendString(const std::string& message) override { return isAuthenticated; }
    bool isConnected() override { return isAuthenticated; }
    bool isStarted() override { return true; }
    void setConnectionCallback(BluetoothConnectionCallback* callback) override {}
    void setReceivedMessageCallback(BluetoothReceivedMessageCallback* callback) override {}
};
