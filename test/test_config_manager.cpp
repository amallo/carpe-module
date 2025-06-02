#include "test_framework.h"
#include "mocks/MockConfigManager.h"
#include "../src/core/device/generators/RandomDeviceIdGenerator.h"

/**
 * @brief Tests pour l'interface ConfigManager
 * Démontre l'utilisation de l'interface et du mock
 */

class ConfigManagerTest {
private:
    static MockConfigManager* mockConfig;
    static RandomDeviceIdGenerator* idGenerator;

public:
    static void setUp() {
        mockConfig = new MockConfigManager();
        idGenerator = new RandomDeviceIdGenerator();
    }

    static void tearDown() {
        delete mockConfig;
        delete idGenerator;
        mockConfig = nullptr;
        idGenerator = nullptr;
    }

    static void test_load_config_success() {
        TEST_LOG("Testing successful config loading");
        
        // ARRANGE
        mockConfig->set_load_config_return(true);
        
        // ACT
        bool result = mockConfig->loadConfig();
        
        // ASSERT
        TEST_ASSERT_TRUE(result);
        TEST_ASSERT_TRUE(mockConfig->was_load_config_called());
        TEST_ASSERT_EQUAL_INT(1, mockConfig->get_call_count());
    }

    static void test_load_config_failure() {
        TEST_LOG("Testing config loading failure");
        
        // ARRANGE
        mockConfig->set_load_config_return(false);
        
        // ACT
        bool result = mockConfig->loadConfig();
        
        // ASSERT
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT_TRUE(mockConfig->was_load_config_called());
    }

    static void test_set_and_get_device_id() {
        TEST_LOG("Testing device ID set/get cycle");
        
        // ARRANGE
        String testId = "carpe-TEST123";
        
        // ACT
        mockConfig->setDeviceId(testId);
        String retrievedId = mockConfig->getDeviceId();
        
        // ASSERT
        TEST_ASSERT_TRUE(mockConfig->was_set_device_id_called_with(testId));
        TEST_ASSERT_TRUE(mockConfig->was_get_device_id_called());
        TEST_ASSERT_EQUAL_STRING(testId.c_str(), retrievedId.c_str());
        
        TEST_LOG("Set ID: " + testId);
        TEST_LOG("Retrieved ID: " + retrievedId);
    }

    static void test_save_config_with_generated_id() {
        TEST_LOG("Testing config save with generated device ID");
        
        // ARRANGE
        mockConfig->set_save_config_return(true);
        String generatedId = idGenerator->generate();
        
        // ACT
        mockConfig->setDeviceId(generatedId);
        bool saveResult = mockConfig->saveConfig();
        
        // ASSERT
        TEST_ASSERT_TRUE(saveResult);
        TEST_ASSERT_TRUE(mockConfig->was_set_device_id_called_with(generatedId));
        TEST_ASSERT_TRUE(mockConfig->was_save_config_called());
        
        TEST_LOG("Generated and saved ID: " + generatedId);
    }

    static void test_config_sequence() {
        TEST_LOG("Testing complete config sequence");
        
        // ARRANGE
        mockConfig->set_load_config_return(true);
        mockConfig->set_save_config_return(true);
        String newId = "carpe-SEQ456";
        
        // ACT - Simulate a typical usage sequence
        bool loadOk = mockConfig->loadConfig();      // 1. Load existing config
        String oldId = mockConfig->getDeviceId();    // 2. Get current ID
        mockConfig->setDeviceId(newId);              // 3. Set new ID
        bool saveOk = mockConfig->saveConfig();      // 4. Save config
        mockConfig->printConfig();                   // 5. Debug print
        
        // ASSERT
        TEST_ASSERT_TRUE(loadOk);
        TEST_ASSERT_TRUE(saveOk);
        TEST_ASSERT_TRUE(mockConfig->was_load_config_called());
        TEST_ASSERT_TRUE(mockConfig->was_get_device_id_called());
        TEST_ASSERT_TRUE(mockConfig->was_set_device_id_called_with(newId));
        TEST_ASSERT_TRUE(mockConfig->was_save_config_called());
        TEST_ASSERT_TRUE(mockConfig->was_print_config_called());
        
        // Verify call order and count
        TEST_ASSERT_EQUAL_INT(5, mockConfig->get_call_count());
        
        TEST_LOG("Old ID: " + oldId);
        TEST_LOG("New ID: " + newId);
    }

    static void test_mock_reset() {
        TEST_LOG("Testing mock reset functionality");
        
        // ARRANGE & ACT - Make some calls
        mockConfig->loadConfig();
        mockConfig->saveConfig();
        TEST_ASSERT_TRUE(mockConfig->get_call_count() > 0);
        
        // ACT - Reset
        mockConfig->reset();
        
        // ASSERT
        TEST_ASSERT_EQUAL_INT(0, mockConfig->get_call_count());
        TEST_ASSERT_FALSE(mockConfig->was_load_config_called());
        TEST_ASSERT_FALSE(mockConfig->was_save_config_called());
        
        // Verify default state is restored
        String defaultId = mockConfig->getDeviceId();
        TEST_ASSERT_EQUAL_STRING("carpe-MOCK123", defaultId.c_str());
    }
};

// Définition des membres statiques
MockConfigManager* ConfigManagerTest::mockConfig = nullptr;
RandomDeviceIdGenerator* ConfigManagerTest::idGenerator = nullptr;

// Fonctions Unity pour chaque test
void test_config_load_success() {
    ConfigManagerTest::setUp();
    ConfigManagerTest::test_load_config_success();
    ConfigManagerTest::tearDown();
}

void test_config_load_failure() {
    ConfigManagerTest::setUp();
    ConfigManagerTest::test_load_config_failure();
    ConfigManagerTest::tearDown();
}

void test_config_set_get_device_id() {
    ConfigManagerTest::setUp();
    ConfigManagerTest::test_set_and_get_device_id();
    ConfigManagerTest::tearDown();
}

void test_config_save_with_generated_id() {
    ConfigManagerTest::setUp();
    ConfigManagerTest::test_save_config_with_generated_id();
    ConfigManagerTest::tearDown();
}

void test_config_sequence() {
    ConfigManagerTest::setUp();
    ConfigManagerTest::test_config_sequence();
    ConfigManagerTest::tearDown();
}

void test_config_mock_reset() {
    ConfigManagerTest::setUp();
    ConfigManagerTest::test_mock_reset();
    ConfigManagerTest::tearDown();
}

// Fonction pour regrouper tous les tests (à ajouter dans test_main)
void test_config_manager_all() {
    TEST_LOG("=== ConfigManager Tests ===");
    RUN_TEST(test_config_load_success);
    RUN_TEST(test_config_load_failure);
    RUN_TEST(test_config_set_get_device_id);
    RUN_TEST(test_config_save_with_generated_id);
    RUN_TEST(test_config_sequence);
    RUN_TEST(test_config_mock_reset);
} 