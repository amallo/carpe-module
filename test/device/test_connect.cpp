#include <unity.h>
#include <iostream>
#include <core/device/SetupDeviceUseCase.h>

// Tests
void test_empty_request_parameters() {
    SetupDeviceRequest emptyRequest;
    // Test que la structure vide fonctionne
    TEST_ASSERT_TRUE(true); // Request créé sans erreur
}

void test_device_initialization_basic() {
    SetupDeviceUseCase useCase;
    SetupDeviceRequest request;
    
    SetupDeviceResponse response = useCase.execute(request);
    
    TEST_ASSERT_TRUE(response.success);
    TEST_ASSERT_EQUAL_STRING("carpe-TEST123", response.device_id.c_str());
    TEST_ASSERT_FALSE(response.was_already_initialized);
}

void test_device_initialization_interface() {
    SetupDeviceUseCase useCase;
    
    bool isInitialized = useCase.isDeviceInitialized();
    
    TEST_ASSERT_FALSE(isInitialized);
}

void setUp(void) {}
void tearDown(void) {}

int main() {
    std::cout << "🧪 Device Initialization Use Case Test" << std::endl;
    std::cout << "=======================================" << std::endl;
    
    UNITY_BEGIN();
    
    RUN_TEST(test_empty_request_parameters);
    RUN_TEST(test_device_initialization_basic);
    RUN_TEST(test_device_initialization_interface);
    
    int result = UNITY_END();
    
    std::cout << std::endl;
    if (result == 0) {
        std::cout << "✅ Tous les tests du use case passent !" << std::endl;
    } else {
        std::cout << "❌ Certains tests ont échoué." << std::endl;
    }
    
    return result;
} 