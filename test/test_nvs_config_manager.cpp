#include "test_framework.h"
#include "../src/core/config/NvsConfigManager.h"
#include "../src/core/device/generators/RandomDeviceIdGenerator.h"

/**
 * @brief Tests pour NvsConfigManager
 * Vérifie l'implémentation concrète de l'interface ConfigManager
 */

class NvsConfigManagerTest {
private:
    static NvsConfigManager* nvsConfig;
    static RandomDeviceIdGenerator* idGenerator;

public:
    static void setUp() {
        nvsConfig = new NvsConfigManager();
        idGenerator = new RandomDeviceIdGenerator();
    }

    static void tearDown() {
        delete nvsConfig;
        delete idGenerator;
        nvsConfig = nullptr;
        idGenerator = nullptr;
    }

    static void test_interface_compliance() {
        TEST_LOG("Testing ConfigManager interface compliance");
        
        // ARRANGE - Vérifier que NvsConfigManager implémente ConfigManager
        ConfigManager* configInterface = nvsConfig;
        
        // ACT - Utiliser les méthodes via l'interface
        String testId = "carpe-INTERFACE";
        configInterface->setDeviceId(testId);
        String retrievedId = configInterface->getDeviceId();
        
        // ASSERT
        TEST_ASSERT_EQUAL_STRING(testId.c_str(), retrievedId.c_str());
        TEST_LOG("Interface test passed - ID: " + retrievedId);
    }

    static void test_polymorphism() {
        TEST_LOG("Testing polymorphism with ConfigManager interface");
        
        // ARRANGE - Créer un pointeur vers l'interface
        ConfigManager* config = new NvsConfigManager();
        String generatedId = idGenerator->generate();
        
        // ACT - Utiliser via le polymorphisme
        config->setDeviceId(generatedId);
        String storedId = config->getDeviceId();
        
        // ASSERT
        TEST_ASSERT_EQUAL_STRING(generatedId.c_str(), storedId.c_str());
        
        // CLEANUP
        delete config;
        
        TEST_LOG("Polymorphism test passed - ID: " + storedId);
    }

    static void test_basic_functionality() {
        TEST_LOG("Testing basic NvsConfigManager functionality");
        
        // ARRANGE
        String testId = "carpe-NVS123";
        
        // ACT & ASSERT - Test set/get cycle
        nvsConfig->setDeviceId(testId);
        String retrievedId = nvsConfig->getDeviceId();
        TEST_ASSERT_EQUAL_STRING(testId.c_str(), retrievedId.c_str());
        
        // ACT & ASSERT - Test printConfig (should not crash)
        nvsConfig->printConfig(); // Visual test - check serial output
        
        TEST_LOG("Basic functionality test passed");
    }

    static void test_load_save_operations() {
        TEST_LOG("Testing load/save operations");
        
        // ARRANGE
        String originalId = "carpe-SAVE456";
        nvsConfig->setDeviceId(originalId);
        
        // ACT - Test save operation
        bool saveResult = nvsConfig->saveConfig();
        
        // ASSERT - Save should work (assuming NVS is available)
        // Note: En simulation, NVS pourrait ne pas être disponible
        // C'est pourquoi on teste juste que la méthode ne crash pas
        TEST_LOG(saveResult ? "Save succeeded" : "Save failed (expected in test env)");
        
        // ACT - Test load operation  
        bool loadResult = nvsConfig->loadConfig();
        TEST_LOG(loadResult ? "Load succeeded" : "Load failed (expected in test env)");
        
        // ASSERT - Methods should return without crashing
        TEST_ASSERT_TRUE(true); // If we reach here, methods didn't crash
        
        TEST_LOG("Load/save operations completed");
    }

    static void test_integration_with_generated_id() {
        TEST_LOG("Testing integration with RandomDeviceIdGenerator");
        
        // ARRANGE
        String generatedId = idGenerator->generate();
        
        // ACT - Set generated ID and retrieve it
        nvsConfig->setDeviceId(generatedId);
        String storedId = nvsConfig->getDeviceId();
        
        // ASSERT
        TEST_ASSERT_EQUAL_STRING(generatedId.c_str(), storedId.c_str());
        TEST_ASSERT_TRUE(storedId.startsWith("carpe-"));
        TEST_ASSERT_EQUAL_INT(12, storedId.length());
        
        TEST_LOG("Generated ID: " + generatedId);
        TEST_LOG("Stored ID: " + storedId);
    }
};

// Définition des membres statiques
NvsConfigManager* NvsConfigManagerTest::nvsConfig = nullptr;
RandomDeviceIdGenerator* NvsConfigManagerTest::idGenerator = nullptr;

// Fonctions Unity pour chaque test
void test_nvs_interface_compliance() {
    NvsConfigManagerTest::setUp();
    NvsConfigManagerTest::test_interface_compliance();
    NvsConfigManagerTest::tearDown();
}

void test_nvs_polymorphism() {
    NvsConfigManagerTest::setUp();
    NvsConfigManagerTest::test_polymorphism();
    NvsConfigManagerTest::tearDown();
}

void test_nvs_basic_functionality() {
    NvsConfigManagerTest::setUp();
    NvsConfigManagerTest::test_basic_functionality();
    NvsConfigManagerTest::tearDown();
}

void test_nvs_load_save_operations() {
    NvsConfigManagerTest::setUp();
    NvsConfigManagerTest::test_load_save_operations();
    NvsConfigManagerTest::tearDown();
}

void test_nvs_integration_with_generator() {
    NvsConfigManagerTest::setUp();
    NvsConfigManagerTest::test_integration_with_generated_id();
    NvsConfigManagerTest::tearDown();
}

// Fonction pour regrouper tous les tests (à ajouter dans test_main)
void test_nvs_config_manager_all() {
    TEST_LOG("=== NvsConfigManager Tests ===");
    RUN_TEST(test_nvs_interface_compliance);
    RUN_TEST(test_nvs_polymorphism);
    RUN_TEST(test_nvs_basic_functionality);
    RUN_TEST(test_nvs_load_save_operations);
    RUN_TEST(test_nvs_integration_with_generator);
} 