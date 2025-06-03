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

// Tests de base de l'interface ConfigProvider
void test_mock_device_id_get_set() {
    std::string testId = "mock-device-123";
    
    mockConfig->setDeviceId(testId);
    std::string retrievedId = mockConfig->getDeviceId();
    
    TEST_ASSERT_EQUAL_STRING(testId.c_str(), retrievedId.c_str());
}

void test_mock_initial_device_id_empty() {
    std::string deviceId = mockConfig->getDeviceId();
    TEST_ASSERT_TRUE(deviceId.empty());
}

void test_mock_load_config_success() {
    bool result = mockConfig->loadConfig();
    TEST_ASSERT_TRUE(result);
}

void test_mock_save_config_success() {
    bool result = mockConfig->saveConfig();
    TEST_ASSERT_TRUE(result);
}

// Tests spécifiques au mock (spy behavior)
void test_mock_tracks_load_calls() {
    TEST_ASSERT_FALSE(mockConfig->wasLoadCalled());
    TEST_ASSERT_EQUAL_INT(0, mockConfig->getLoadCallCount());
    
    mockConfig->loadConfig();
    
    TEST_ASSERT_TRUE(mockConfig->wasLoadCalled());
    TEST_ASSERT_EQUAL_INT(1, mockConfig->getLoadCallCount());
    
    mockConfig->loadConfig();
    TEST_ASSERT_EQUAL_INT(2, mockConfig->getLoadCallCount());
}

void test_mock_tracks_save_calls() {
    TEST_ASSERT_FALSE(mockConfig->wasSaveCalled());
    TEST_ASSERT_EQUAL_INT(0, mockConfig->getSaveCallCount());
    
    mockConfig->saveConfig();
    
    TEST_ASSERT_TRUE(mockConfig->wasSaveCalled());
    TEST_ASSERT_EQUAL_INT(1, mockConfig->getSaveCallCount());
    
    mockConfig->saveConfig();
    TEST_ASSERT_EQUAL_INT(2, mockConfig->getSaveCallCount());
}

void test_mock_reset_functionality() {
    // Setup état
    mockConfig->setDeviceId("test-123");
    mockConfig->loadConfig();
    mockConfig->saveConfig();
    
    // Vérifier état avant reset
    TEST_ASSERT_FALSE(mockConfig->getDeviceId().empty());
    TEST_ASSERT_TRUE(mockConfig->wasLoadCalled());
    TEST_ASSERT_TRUE(mockConfig->wasSaveCalled());
    
    // Reset
    mockConfig->reset();
    
    // Vérifier état après reset
    TEST_ASSERT_TRUE(mockConfig->getDeviceId().empty());
    TEST_ASSERT_FALSE(mockConfig->wasLoadCalled());
    TEST_ASSERT_FALSE(mockConfig->wasSaveCalled());
    TEST_ASSERT_EQUAL_INT(0, mockConfig->getLoadCallCount());
    TEST_ASSERT_EQUAL_INT(0, mockConfig->getSaveCallCount());
}

void test_mock_polymorphism() {
    // Test que le mock peut être utilisé comme ConfigProvider*
    ConfigProvider* provider = mockConfig;
    
    provider->setDeviceId("polymorphism-test");
    std::string id = provider->getDeviceId();
    
    TEST_ASSERT_EQUAL_STRING("polymorphism-test", id.c_str());
    TEST_ASSERT_TRUE(provider->loadConfig());
    TEST_ASSERT_TRUE(provider->saveConfig());
}

int main() {
    std::cout << "🧪 Mock Config Provider Test" << std::endl;
    std::cout << "==============================" << std::endl;
    
    UNITY_BEGIN();
    
    RUN_TEST(test_mock_device_id_get_set);
    RUN_TEST(test_mock_initial_device_id_empty);
    RUN_TEST(test_mock_load_config_success);
    RUN_TEST(test_mock_save_config_success);
    RUN_TEST(test_mock_tracks_load_calls);
    RUN_TEST(test_mock_tracks_save_calls);
    RUN_TEST(test_mock_reset_functionality);
    RUN_TEST(test_mock_polymorphism);
    
    return UNITY_END();
} 