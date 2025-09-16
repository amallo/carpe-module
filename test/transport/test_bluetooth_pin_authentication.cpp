#include <unity.h>
#include <iostream>
#include <core/transport/providers/BluetoothProvider.h>
#include <core/logging/providers/infra/ConsoleLogger.h>
#include "MockBluetoothProvider.h"

// Test de l'authentification PIN réussie
void test_bluetooth_pin_authentication_success() {
    MockBluetoothProvider provider;
    
    // Test avec le bon PIN
    bool result = provider.simulateAuthenticateWithPin("1234");
    
    TEST_ASSERT_TRUE(result);
    TEST_ASSERT_TRUE(provider.getIsAuthenticated());
    TEST_ASSERT_TRUE(provider.getAuthenticationAttempted());
    TEST_ASSERT_EQUAL(1, provider.getAuthenticationAttempts());
}

// Test de l'authentification PIN échouée
void test_bluetooth_pin_authentication_failure() {
    MockBluetoothProvider provider;
    
    // Test avec un mauvais PIN
    bool result = provider.simulateAuthenticateWithPin("0000");
    
    TEST_ASSERT_FALSE(result);
    TEST_ASSERT_FALSE(provider.getIsAuthenticated());
    TEST_ASSERT_TRUE(provider.getAuthenticationAttempted());
    TEST_ASSERT_EQUAL(1, provider.getAuthenticationAttempts());
}

// Test du nombre maximum de tentatives
void test_bluetooth_pin_max_attempts() {
    MockBluetoothProvider provider;
    
    // Test direct du cas d'erreur MaxAttempts
    try {
        provider.shouldRaiseAnError(BluetoothErrorType::MaxAttempts);
        TEST_FAIL_MESSAGE("Expected exception was not thrown");
    } catch (const BluetoothConnectionError& e) {
        // Vérifier que l'erreur est bien celle attendue
        TEST_ASSERT_EQUAL(static_cast<int>(BluetoothErrorType::MaxAttempts), static_cast<int>(e.getErrorType()));
        std::string errorMsg = e.what();
        TEST_ASSERT_TRUE(errorMsg.find(BluetoothErrorMessages::MAX_ATTEMPTS_EXCEEDED) != std::string::npos);
    }
}


// Fonction de setup pour les tests
void setUp() {
    // Initialisation si nécessaire
}

// Fonction de cleanup pour les tests
void tearDown() {
    // Nettoyage si nécessaire
}

// Fonction principale pour exécuter tous les tests
int main() {
    UNITY_BEGIN();
    
    RUN_TEST(test_bluetooth_pin_authentication_success);
    RUN_TEST(test_bluetooth_pin_authentication_failure);
    RUN_TEST(test_bluetooth_pin_max_attempts);
    
    return UNITY_END();
}
