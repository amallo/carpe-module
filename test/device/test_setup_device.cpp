#include <unity.h>
#include <iostream>
#include <core/device/SetupDeviceUseCase.h>
#include <test/config/providers/MockConfigProvider.h>
#include <test/core/device/generators/MockDeviceIdGenerator.h>

// Global variables for use case and mocks
SetupDeviceUseCase* useCase = nullptr;
MockConfigProvider* configProvider = nullptr;
MockDeviceIdGenerator* deviceIdGenerator = nullptr;

// Tests
void setUp(void) {
    configProvider = new MockConfigProvider();
    deviceIdGenerator = new MockDeviceIdGenerator();
    useCase = new SetupDeviceUseCase(configProvider, deviceIdGenerator);
}

void tearDown(void) {
    delete useCase;
    delete configProvider;
    delete deviceIdGenerator;
    useCase = nullptr;
    configProvider = nullptr;
    deviceIdGenerator = nullptr;
}

void test_device_already_initialized() {
    SetupDeviceRequest request;
    configProvider->scheduleDeviceIdResult("carpe-TEST123");
    SetupDeviceResponse response = useCase->execute(request);
    
    TEST_ASSERT_FALSE(response.success);
    TEST_ASSERT_EQUAL_STRING("carpe-TEST123", response.device_id.c_str());
    TEST_ASSERT_EQUAL_STRING(response.error_message.c_str(), "ALREADY_INITIALIZED");
}

void test_setup_a_new_device() {
    SetupDeviceRequest request;
    configProvider->scheduleDeviceIdResult("");
    deviceIdGenerator->scheduleGenerateResult("carpe-TEST123");
    
    SetupDeviceResponse response = useCase->execute(request);
    
    TEST_ASSERT_TRUE(response.success);
    TEST_ASSERT_EQUAL_STRING("carpe-TEST123", response.device_id.c_str());
    TEST_ASSERT_EQUAL_STRING(response.error_message.c_str(), "");

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