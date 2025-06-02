#include "test_framework.h"
#include "mocks/MockBluetoothProvider.h"
#include "../src/core/device/generators/RandomDeviceIdGenerator.h"

/**
 * @brief Tests d'intégration avec mocks
 * Exemple de comment tester les interactions entre composants
 */

class BluetoothIntegrationTest {
private:
    static MockBluetoothProvider* mockBluetooth;
    static RandomDeviceIdGenerator* idGenerator;

public:
    static void setUp() {
        mockBluetooth = new MockBluetoothProvider();
        idGenerator = new RandomDeviceIdGenerator();
    }

    static void tearDown() {
        delete mockBluetooth;
        delete idGenerator;
        mockBluetooth = nullptr;
        idGenerator = nullptr;
    }

    static void test_bluetooth_initialization_with_generated_device_id() {
        TEST_LOG("Testing Bluetooth initialization with generated device ID");
        
        // ARRANGE - Programmer le mock pour retourner true
        mockBluetooth->set_init_return(true);
        
        // ACT - Générer un ID et initialiser Bluetooth
        String deviceId = idGenerator->generate();
        bool initResult = mockBluetooth->init(deviceId);
        
        // ASSERT - Vérifier le résultat et les appels
        TEST_ASSERT_TRUE(initResult);
        TEST_ASSERT_TRUE(mockBluetooth->was_init_called_with(deviceId));
        TEST_ASSERT_EQUAL_INT(1, mockBluetooth->get_call_count());
        
        TEST_LOG("Device ID used: " + deviceId);
    }

    static void test_bluetooth_initialization_failure_handling() {
        TEST_LOG("Testing Bluetooth initialization failure handling");
        
        // ARRANGE - Programmer le mock pour retourner false
        mockBluetooth->set_init_return(false);
        
        // ACT
        String deviceId = idGenerator->generate();
        bool initResult = mockBluetooth->init(deviceId);
        
        // ASSERT
        TEST_ASSERT_FALSE(initResult);
        TEST_ASSERT_TRUE(mockBluetooth->was_init_called_with(deviceId));
    }

    static void test_bluetooth_connection_sequence() {
        TEST_LOG("Testing complete Bluetooth connection sequence");
        
        // ARRANGE - Programmer une séquence de retours
        mockBluetooth->set_init_return(true);
        mockBluetooth->set_start_return(true);
        mockBluetooth->add_is_connected_return(false); // Premier appel: pas encore connecté
        mockBluetooth->add_is_connected_return(true);  // Deuxième appel: connecté
        
        // ACT - Simuler une séquence d'initialisation complète
        String deviceId = idGenerator->generate();
        bool initOk = mockBluetooth->init(deviceId);
        bool startOk = mockBluetooth->start();
        bool connected1 = mockBluetooth->isConnected(); // Premier check
        bool connected2 = mockBluetooth->isConnected(); // Deuxième check
        
        // ASSERT
        TEST_ASSERT_TRUE(initOk);
        TEST_ASSERT_TRUE(startOk);
        TEST_ASSERT_FALSE(connected1); // Premier check: pas connecté
        TEST_ASSERT_TRUE(connected2);  // Deuxième check: connecté
        
        // Vérifier que toutes les méthodes ont été appelées
        TEST_ASSERT_TRUE(mockBluetooth->was_init_called_with(deviceId));
        TEST_ASSERT_TRUE(mockBluetooth->was_start_called());
        TEST_ASSERT_TRUE(mockBluetooth->was_is_connected_called());
    }

    static void test_send_message_with_device_id() {
        TEST_LOG("Testing message sending with device ID");
        
        // ARRANGE
        mockBluetooth->set_send_string_return(true);
        
        // ACT
        String deviceId = idGenerator->generate();
        String message = "Hello from " + deviceId;
        bool sendResult = mockBluetooth->sendString(message);
        
        // ASSERT
        TEST_ASSERT_TRUE(sendResult);
        TEST_ASSERT_TRUE(mockBluetooth->was_send_string_called_with(message));
        
        // Vérifier que le message contient bien l'ID généré
        BluetoothCall lastCall = mockBluetooth->get_last_call();
        TEST_ASSERT_TRUE(lastCall.parameter.indexOf(deviceId) >= 0);
        
        TEST_LOG("Message sent: " + message);
    }

    static void test_mock_reset_functionality() {
        TEST_LOG("Testing mock reset functionality");
        
        // ARRANGE & ACT - Faire quelques appels
        String deviceId = idGenerator->generate();
        mockBluetooth->init(deviceId);
        mockBluetooth->start();
        
        // ASSERT - Vérifier que les appels sont enregistrés
        TEST_ASSERT_TRUE(mockBluetooth->get_call_count() > 0);
        
        // ACT - Reset du mock
        mockBluetooth->reset();
        
        // ASSERT - Vérifier que le mock est nettoyé
        TEST_ASSERT_EQUAL_INT(0, mockBluetooth->get_call_count());
        TEST_ASSERT_FALSE(mockBluetooth->was_init_called());
        TEST_ASSERT_FALSE(mockBluetooth->was_start_called());
    }
};

// Définition des membres statiques
MockBluetoothProvider* BluetoothIntegrationTest::mockBluetooth = nullptr;
RandomDeviceIdGenerator* BluetoothIntegrationTest::idGenerator = nullptr;

// Fonctions Unity pour chaque test
void test_bluetooth_init_with_device_id() {
    BluetoothIntegrationTest::setUp();
    BluetoothIntegrationTest::test_bluetooth_initialization_with_generated_device_id();
    BluetoothIntegrationTest::tearDown();
}

void test_bluetooth_init_failure() {
    BluetoothIntegrationTest::setUp();
    BluetoothIntegrationTest::test_bluetooth_initialization_failure_handling();
    BluetoothIntegrationTest::tearDown();
}

void test_bluetooth_connection_sequence() {
    BluetoothIntegrationTest::setUp();
    BluetoothIntegrationTest::test_bluetooth_connection_sequence();
    BluetoothIntegrationTest::tearDown();
}

void test_bluetooth_send_message() {
    BluetoothIntegrationTest::setUp();
    BluetoothIntegrationTest::test_send_message_with_device_id();
    BluetoothIntegrationTest::tearDown();
}

void test_bluetooth_mock_reset() {
    BluetoothIntegrationTest::setUp();
    BluetoothIntegrationTest::test_mock_reset_functionality();
    BluetoothIntegrationTest::tearDown();
}

// Fonction pour regrouper tous les tests (appelée depuis test_main)
void test_bluetooth_integration_all() {
    TEST_LOG("=== Bluetooth Integration Tests ===");
    RUN_TEST(test_bluetooth_init_with_device_id);
    RUN_TEST(test_bluetooth_init_failure);
    RUN_TEST(test_bluetooth_connection_sequence);
    RUN_TEST(test_bluetooth_send_message);
    RUN_TEST(test_bluetooth_mock_reset);
} 