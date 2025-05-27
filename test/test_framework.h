#pragma once

#include <Arduino.h>
#include <unity.h>

// Macros personnalisées pour les tests
#define TEST_SETUP() void setUp() {}
#define TEST_TEARDOWN() void tearDown() {}

// Macros pour des assertions plus expressives
#define ASSERT_NOT_NULL(ptr) TEST_ASSERT_NOT_NULL(ptr)
#define ASSERT_NULL(ptr) TEST_ASSERT_NULL(ptr)
#define ASSERT_STRING_EQUALS(expected, actual) TEST_ASSERT_EQUAL_STRING(expected, actual)
#define ASSERT_STRING_NOT_EMPTY(str) TEST_ASSERT_TRUE(str.length() > 0)

// Macro manquante dans Unity - comparaison de strings
#define TEST_ASSERT_NOT_EQUAL_STRING(expected, actual) \
    TEST_ASSERT_FALSE(strcmp(expected, actual) == 0)

// Helpers pour le debug
#define DEBUG_PRINT(msg) Serial.println("[DEBUG] " + String(msg))
#define TEST_LOG(msg) Serial.println("[TEST] " + String(msg)) 