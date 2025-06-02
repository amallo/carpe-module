#pragma once

#include <unity.h>
#include <string>

#ifdef NATIVE_BUILD
#include <iostream>
#else
#include <Arduino.h>
#endif

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
    TEST_ASSERT_MESSAGE(strcmp(expected, actual) != 0, "Strings should not be equal")

// Macros pour std::string - avec support des string literals et std::string
#define TEST_ASSERT_EQUAL_STDSTRING(expected, actual) \
    TEST_ASSERT_EQUAL_STRING(expected, actual.c_str())

#define TEST_ASSERT_EQUAL_STDSTRING_TO_STDSTRING(expected, actual) \
    TEST_ASSERT_EQUAL_STRING(expected.c_str(), actual.c_str())

#define TEST_ASSERT_NOT_EQUAL_STDSTRING(expected, actual) \
    TEST_ASSERT_MESSAGE(expected != actual, "std::strings should not be equal")

#define ASSERT_STDSTRING_NOT_EMPTY(str) TEST_ASSERT_TRUE(str.length() > 0)

// Helpers pour les logs avec std::string
inline void test_log(const std::string& msg) {
#ifdef NATIVE_BUILD
    std::cout << "[TEST] " << msg << std::endl;
#else
    Serial.println(("[TEST] " + msg).c_str());
#endif
}

inline void test_log(const char* msg) {
#ifdef NATIVE_BUILD
    std::cout << "[TEST] " << msg << std::endl;
#else
    Serial.print("[TEST] ");
    Serial.println(msg);
#endif
}

// Macro pour simplifier
#define TEST_LOG(msg) test_log(msg)
#define DEBUG_PRINT(msg) test_log(std::string("[DEBUG] ") + msg) 