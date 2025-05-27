#include <Arduino.h>
#include <unity.h>
#include "../src/core/RandomDeviceGenerator.h"

void test_random_generator_creates_non_empty_id() {
    RandomDeviceGenerator generator;
    String deviceId = generator.generate();
    
    TEST_ASSERT_TRUE(deviceId.length() > 0);
    TEST_ASSERT_TRUE(deviceId != "");
}

void test_random_generator_creates_different_ids() {
    RandomDeviceGenerator generator;
    String id1 = generator.generate();
    delay(10); // Petit délai pour changer le seed
    String id2 = generator.generate();
    
    TEST_ASSERT_NOT_EQUAL_STRING(id1.c_str(), id2.c_str());
}

void test_random_generator_creates_valid_format() {
    RandomDeviceGenerator generator;
    String deviceId = generator.generate();
    
    // Vérifier que l'ID a une longueur raisonnable (assumant un format spécifique)
    TEST_ASSERT_TRUE(deviceId.length() >= 8);
    TEST_ASSERT_TRUE(deviceId.length() <= 32);
}

void setup() {
    delay(2000);
    UNITY_BEGIN();
    
    RUN_TEST(test_random_generator_creates_non_empty_id);
    RUN_TEST(test_random_generator_creates_different_ids);
    RUN_TEST(test_random_generator_creates_valid_format);
    
    UNITY_END();
}

void loop() {
    // Tests exécutés une seule fois dans setup()
} 