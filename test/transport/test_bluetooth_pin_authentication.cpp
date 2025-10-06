#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <iostream>
#include <core/transport/providers/BluetoothProvider.h>
#include <core/logging/providers/infra/ConsoleLogger.h>
#include <core/transport/providers/BluetoothConnectionCallback.h>
#include <core/transport/MessageRouter.h>
#include <core/transport/model/Message.h>
#include <core/Screen.h>
#include <test/common/TestDisplay.h>
#include <test/common/ConsoleScreen.h>
#include "MockBluetoothProvider.h"
#include "MockPinCodeGenerator.h"
#include "MockMessageEncoder.h"

// Test de l'envoi de challenge à la connexion
TEST_CASE("Should send challenge on connection") {
    // Créer le provider et les mocks
    MockBluetoothProvider provider;
    MockMessageEncoder encoder;
    ConsoleLogger logger(false);
    ConsoleScreen screen;
    MockPinCodeGenerator pinGenerator;
    MessageRouter router(&encoder);
    
    // Configurer le mock pour retourner un PIN prévisible
    pinGenerator.scheduleGeneratedPinCode("5678");
    
    // Configurer l'encoder pour retourner le message attendu
    encoder.scheduleEncode("pair:challenge:5678");
    
    // Configurer le router avec le provider
    router.setBluetoothProvider(&provider);
    
    // Créer le callback avec injection du router
    BluetoothConnectionCallback callback(&logger, &screen, &provider, &pinGenerator, &router);
    callback.setDeviceId("carpe-TEST123");
    
    // Vérifier qu'aucun message n'a été envoyé avant la connexion
    CHECK_FALSE(provider.wasMessageSent("pair:challenge:5678"));
    
    // Simuler la connexion d'un client (ce qui déclenche le callback)
    callback.onDeviceConnected("AA:BB:CC:DD:EE:FF");
    
    // Vérifier qu'un message challenge a été envoyé par le callback
    CHECK(provider.wasMessageSent("pair:challenge:5678"));
    CHECK(provider.getSentMessages().size() == 1);
    CHECK(pinGenerator.wasGeneratePinCodeCalled());
}



 
