#include <unity.h>
#include <iostream>
#include <core/transport/providers/BluetoothProvider.h>
#include <core/logging/providers/infra/ConsoleLogger.h>
#include <core/transport/providers/BluetoothConnectionCallback.h>
#include <core/Screen.h>
#include <test/common/TestDisplay.h>
#include <test/common/ConsoleScreen.h>
#include "MockBluetoothProvider.h"
#include "MockPinCodeGenerator.h"

// Test de l'envoi de challenge à la connexion
void test_should_send_challenge_on_connection() {
    // Créer le provider et le callback
    MockBluetoothProvider provider;
    ConsoleLogger logger(false);
    ConsoleScreen screen;
    MockPinCodeGenerator pinGenerator;
    
    // Configurer le mock pour retourner un PIN prévisible
    pinGenerator.scheduleGeneratedPinCode("5678");
    
    // Créer le callback avec injection du provider et du pinGenerator
    BluetoothConnectionCallback callback(&logger, &screen, &provider, &pinGenerator);
    callback.setDeviceId("carpe-TEST123");
    
    // Vérifier qu'aucun message n'a été envoyé avant la connexion
    TEST_ASSERT_FALSE(provider.wasMessageSent("pair:challenge:"));
    
    // Simuler la connexion d'un client (ce qui déclenche le callback)
    callback.onDeviceConnected("AA:BB:CC:DD:EE:FF");
    
    // Vérifier qu'un message challenge a été envoyé par le callback
    TEST_ASSERT_TRUE(provider.wasMessageSent("pair:challenge:5678"));
    TEST_ASSERT_EQUAL_INT(1, provider.getSentMessages().size());
    TEST_ASSERT_TRUE(pinGenerator.wasGeneratePinCodeCalled());
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
    
    RUN_TEST(test_should_send_challenge_on_connection);
    
    return UNITY_END();
}
