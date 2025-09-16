#include <unity.h>
#include <iostream>
#include <core/device/SetupDeviceUseCase.h>
#include <test/config/providers/MockConfigProvider.h>
#include <test/core/device/generators/MockDeviceIdGenerator.h>
#include <core/logging/providers/infra/ConsoleLogger.h>
#include <test/common/TestDisplay.h>

// Global variables for use case and mocks
SetupDeviceUseCase* useCase = nullptr;
MockConfigProvider* configProvider = nullptr;
MockDeviceIdGenerator* deviceIdGenerator = nullptr;
ConsoleLogger* logger = nullptr;

// Tests
void setUp(void) {
    // Initialiser le logger pour les tests
    logger = new ConsoleLogger(false);  // sans timestamp pour les tests
    logger->setLevel(LogLevel::DEBUG);
    
    logger->debug("🧪 Initialisation des mocks pour test");
    
    configProvider = new MockConfigProvider();
    deviceIdGenerator = new MockDeviceIdGenerator();
    useCase = new SetupDeviceUseCase(configProvider, deviceIdGenerator);
    
    logger->debug("✅ Setup terminé");
}

void tearDown(void) {
    logger->debug("🧹 Nettoyage des mocks");
    
    delete useCase;
    delete configProvider;
    delete deviceIdGenerator;
    delete logger;
    
    useCase = nullptr;
    configProvider = nullptr;
    deviceIdGenerator = nullptr;
    logger = nullptr;
}

void test_device_already_connected() {
    TestDisplay::print(TestDisplay::TEST, "Test: Device déjà connecté");
    
    SetupDeviceRequest request;
    configProvider->scheduleDeviceIdResult("carpe-TEST123");
    SetupDeviceResponse response = useCase->execute(request);
    
    logger->debug("Response success: " + std::string(response.success ? "true" : "false"));
    logger->debug("Response device_id: " + response.device_id);
    logger->debug("Response error: " + response.error_message);
    
    TEST_ASSERT_FALSE(response.success);
    TEST_ASSERT_EQUAL_STRING("carpe-TEST123", response.device_id.c_str());
    TEST_ASSERT_EQUAL_STRING(response.error_message.c_str(), "ALREADY_INITIALIZED");
    
    TestDisplay::print(TestDisplay::SUCCESS, "Test device déjà initialisé: PASS");
}


int main() {
    TestDisplay::printSectionTitle("🧪 Device Connect Device Use Case Test");
    
    UNITY_BEGIN();
    
    RUN_TEST(test_device_already_connected);
    
    int result = UNITY_END();
    
    // Affichage du résumé personnalisé
    int total = 2;
    int passed = (result == 0) ? total : total - result;
    int failed = result;
    
    TestDisplay::printTestSummary(total, passed, failed);
    
    return result;
} 