#include <unity.h>
#include <iostream>
#include "providers/MockConfigProvider.h"

MockConfigProvider* mockConfig = nullptr;

void setUp() {
    mockConfig = new MockConfigProvider();
}

void tearDown() {
    delete mockConfig;
    mockConfig = nullptr;
}

// === Tests des comportements de base (rétrocompatibilité) ===

void test_basic_device_id_operations() {
    std::string testId = "advanced-mock-123";
    
    mockConfig->setDeviceId(testId);
    std::string retrievedId = mockConfig->getDeviceId();
    
    TEST_ASSERT_EQUAL_STRING(testId.c_str(), retrievedId.c_str());
    TEST_ASSERT_TRUE(mockConfig->wasSetDeviceIdCalled());
    TEST_ASSERT_TRUE(mockConfig->wasGetDeviceIdCalled());
}

void test_default_success_behavior() {
    // Par défaut, load et save devraient retourner true
    TEST_ASSERT_TRUE(mockConfig->loadConfig());
    TEST_ASSERT_TRUE(mockConfig->saveConfig());
}

// === Tests des configurations de résultats ===

void test_schedule_load_failure() {
    mockConfig->scheduleLoadFailure("NVS storage error");
    
    bool result = mockConfig->loadConfig();
    
    TEST_ASSERT_FALSE(result);
    BoolResult lastResult = mockConfig->getLastLoadResult();
    TEST_ASSERT_FALSE(lastResult.success);
    TEST_ASSERT_EQUAL_STRING("NVS storage error", lastResult.errorMessage.c_str());
}

void test_schedule_save_failure() {
    mockConfig->scheduleSaveFailure("Disk full");
    
    bool result = mockConfig->saveConfig();
    
    TEST_ASSERT_FALSE(result);
    BoolResult lastResult = mockConfig->getLastSaveResult();
    TEST_ASSERT_FALSE(lastResult.success);
    TEST_ASSERT_EQUAL_STRING("Disk full", lastResult.errorMessage.c_str());
}

void test_schedule_mixed_results() {
    // Programme une séquence : succès, échec, succès
    std::vector<BoolResult> loadResults = {
        BoolResult::createSuccess(true),
        BoolResult::createFailure("Temporary error"),
        BoolResult::createSuccess(true)
    };
    mockConfig->scheduleLoadResults(loadResults);
    
    // Premier appel : succès
    TEST_ASSERT_TRUE(mockConfig->loadConfig());
    TEST_ASSERT_TRUE(mockConfig->getLastLoadResult().success);
    
    // Deuxième appel : échec
    TEST_ASSERT_FALSE(mockConfig->loadConfig());
    TEST_ASSERT_FALSE(mockConfig->getLastLoadResult().success);
    TEST_ASSERT_EQUAL_STRING("Temporary error", mockConfig->getLastLoadResult().errorMessage.c_str());
    
    // Troisième appel : succès
    TEST_ASSERT_TRUE(mockConfig->loadConfig());
    TEST_ASSERT_TRUE(mockConfig->getLastLoadResult().success);
}

void test_default_result_configuration() {
    // Configure un résultat par défaut d'échec
    mockConfig->setLoadDefaultResult(false, "Default error");
    
    // Tous les appels devraient échouer maintenant
    TEST_ASSERT_FALSE(mockConfig->loadConfig());
    TEST_ASSERT_FALSE(mockConfig->loadConfig());
    TEST_ASSERT_FALSE(mockConfig->loadConfig());
    
    // Vérifie le message d'erreur
    TEST_ASSERT_EQUAL_STRING("Default error", mockConfig->getLastLoadResult().errorMessage.c_str());
}

void test_scheduled_then_default() {
    // Programme un succès puis configure un échec par défaut
    mockConfig->scheduleLoadSuccess();
    mockConfig->setLoadDefaultResult(false, "Default failure");
    
    // Premier appel utilise le résultat programmé
    TEST_ASSERT_TRUE(mockConfig->loadConfig());
    
    // Appels suivants utilisent le défaut
    TEST_ASSERT_FALSE(mockConfig->loadConfig());
    TEST_ASSERT_FALSE(mockConfig->loadConfig());
}

// === Tests de suivi d'appels avancé ===

void test_comprehensive_call_tracking() {
    // Effectue divers appels
    mockConfig->setDeviceId("test-123");
    mockConfig->getDeviceId();
    mockConfig->getDeviceId(); // 2ème appel
    mockConfig->loadConfig();
    mockConfig->saveConfig();
    mockConfig->saveConfig(); // 2ème appel
    
    // Vérifie les compteurs
    TEST_ASSERT_EQUAL_INT(1, mockConfig->getSetDeviceIdCallCount());
    TEST_ASSERT_EQUAL_INT(2, mockConfig->getGetDeviceIdCallCount());
    TEST_ASSERT_EQUAL_INT(1, mockConfig->getLoadCallCount());
    TEST_ASSERT_EQUAL_INT(2, mockConfig->getSaveCallCount());
    
    // Vérifie les flags
    TEST_ASSERT_TRUE(mockConfig->wasSetDeviceIdCalled());
    TEST_ASSERT_TRUE(mockConfig->wasGetDeviceIdCalled());
    TEST_ASSERT_TRUE(mockConfig->wasLoadCalled());
    TEST_ASSERT_TRUE(mockConfig->wasSaveCalled());
    
    // Vérifie la dernière valeur setDeviceId
    TEST_ASSERT_EQUAL_STRING("test-123", mockConfig->getLastSetDeviceId().c_str());
}

void test_reset_functionality() {
    // Configure état initial
    mockConfig->setDeviceId("before-reset");
    mockConfig->scheduleLoadFailure("error");
    mockConfig->loadConfig();
    mockConfig->saveConfig();
    
    // Vérifie état avant reset
    TEST_ASSERT_TRUE(mockConfig->wasLoadCalled());
    TEST_ASSERT_TRUE(mockConfig->wasSaveCalled());
    TEST_ASSERT_FALSE(mockConfig->getLastLoadResult().success);
    
    // Reset complet
    mockConfig->reset();
    
    // Vérifie état après reset
    TEST_ASSERT_FALSE(mockConfig->wasLoadCalled());
    TEST_ASSERT_FALSE(mockConfig->wasSaveCalled());
    TEST_ASSERT_TRUE(mockConfig->getDeviceId().empty());
    TEST_ASSERT_TRUE(mockConfig->getLastSetDeviceId().empty());
    
    // Nouveau load devrait réussir (valeur par défaut restaurée)
    TEST_ASSERT_TRUE(mockConfig->loadConfig());
}

void test_partial_reset() {
    // Configure état
    mockConfig->setDeviceId("persistent-value");
    mockConfig->scheduleLoadFailure("temp-error");
    mockConfig->loadConfig();
    
    // Reset seulement les call trackers
    mockConfig->resetCallTrackers();
    
    // DeviceId et résultats programmés persistent
    TEST_ASSERT_EQUAL_STRING("persistent-value", mockConfig->getDeviceId().c_str());
    
    // Mais les call trackers sont reset
    TEST_ASSERT_FALSE(mockConfig->wasLoadCalled());
    TEST_ASSERT_FALSE(mockConfig->wasSetDeviceIdCalled());
}

// === Tests d'intégration et scénarios réalistes ===

void test_realistic_configuration_scenario() {
    // Simule un scénario réaliste : première lecture échoue, retry réussit
    mockConfig->scheduleLoadFailure("Config file corrupted");
    mockConfig->scheduleLoadSuccess();
    
    // Premier essai d'initialisation
    bool firstTry = mockConfig->loadConfig();
    TEST_ASSERT_FALSE(firstTry);
    
    // Retry
    bool secondTry = mockConfig->loadConfig();
    TEST_ASSERT_TRUE(secondTry);
    
    // Configuration du device
    mockConfig->setDeviceId("device-after-recovery");
    
    // Sauvegarde
    TEST_ASSERT_TRUE(mockConfig->saveConfig());
    
    // Vérifications finales
    TEST_ASSERT_EQUAL_INT(2, mockConfig->getLoadCallCount());
    TEST_ASSERT_EQUAL_INT(1, mockConfig->getSaveCallCount());
    TEST_ASSERT_EQUAL_STRING("device-after-recovery", mockConfig->getDeviceId().c_str());
}

int main() {
    std::cout << "🧪 Advanced Mock Config Provider Test" << std::endl;
    std::cout << "======================================" << std::endl;
    
    UNITY_BEGIN();
    
    // Tests de base
    RUN_TEST(test_basic_device_id_operations);
    RUN_TEST(test_default_success_behavior);
    
    // Tests de configuration de résultats
    RUN_TEST(test_schedule_load_failure);
    RUN_TEST(test_schedule_save_failure);
    RUN_TEST(test_schedule_mixed_results);
    RUN_TEST(test_default_result_configuration);
    RUN_TEST(test_scheduled_then_default);
    
    // Tests de suivi avancé
    RUN_TEST(test_comprehensive_call_tracking);
    RUN_TEST(test_reset_functionality);
    RUN_TEST(test_partial_reset);
    
    // Tests d'intégration
    RUN_TEST(test_realistic_configuration_scenario);
    
    return UNITY_END();
} 