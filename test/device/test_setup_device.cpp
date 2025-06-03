#include <unity.h>
#include <iostream>
#include <core/device/SetupDeviceUseCase.h>
#include <test/config/providers/MockConfigProvider.h>
#include <test/core/device/generators/MockDeviceIdGenerator.h>
#include <core/logging/providers/ConsoleLogger.h>

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

void test_device_already_initialized() {
    logger->info("🧪 Test: Device déjà initialisé");
    
    SetupDeviceRequest request;
    configProvider->scheduleDeviceIdResult("carpe-TEST123");
    SetupDeviceResponse response = useCase->execute(request);
    
    logger->debug("Response success: " + std::string(response.success ? "true" : "false"));
    logger->debug("Response device_id: " + response.device_id);
    logger->debug("Response error: " + response.error_message);
    
    TEST_ASSERT_FALSE(response.success);
    TEST_ASSERT_EQUAL_STRING("carpe-TEST123", response.device_id.c_str());
    TEST_ASSERT_EQUAL_STRING(response.error_message.c_str(), "ALREADY_INITIALIZED");
    
    logger->info("✅ Test device déjà initialisé: PASS");
}

void test_setup_a_new_device() {
    logger->info("🧪 Test: Setup nouveau device");
    
    SetupDeviceRequest request;
    configProvider->scheduleDeviceIdResult("");
    deviceIdGenerator->scheduleGenerateResult("carpe-TEST123");
    
    SetupDeviceResponse response = useCase->execute(request);
    
    logger->debug("Response success: " + std::string(response.success ? "true" : "false"));
    logger->debug("Response device_id: " + response.device_id);
    logger->debug("Generated ID: carpe-TEST123");
    
    TEST_ASSERT_TRUE(response.success);
    TEST_ASSERT_EQUAL_STRING("carpe-TEST123", response.device_id.c_str());
    TEST_ASSERT_EQUAL_STRING(response.error_message.c_str(), "");
    
    logger->info("✅ Test setup nouveau device: PASS");
}

int main() {
    std::cout << "🧪 Device Initialization Use Case Test" << std::endl;
    std::cout << "=======================================" << std::endl;
    
    UNITY_BEGIN();
    
    RUN_TEST(test_device_already_initialized);
    RUN_TEST(test_setup_a_new_device);
    
    int result = UNITY_END();
    
    std::cout << std::endl;
    if (result == 0) {
        std::cout << "✅ Tous les tests du use case passent !" << std::endl;
    } else {
        std::cout << "❌ Certains tests ont échoué." << std::endl;
    }
    
    return result;
} 