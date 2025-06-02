#include "../src/core/device/generators/RandomDeviceIdGenerator.h"
#include "test_framework.h"

// Tests pour RandomDeviceIdGenerator
class RandomDeviceIdGeneratorTest {
private:
    static RandomDeviceIdGenerator* generator;

public:
    static void setUp() {
        generator = new RandomDeviceIdGenerator();
    }

    static void tearDown() {
        delete generator;
        generator = nullptr;
    }

    static void test_generate_returns_non_empty_string() {
        TEST_LOG("Testing that generate() returns non-empty string");
        
        String deviceId = generator->generate();
        
        ASSERT_STRING_NOT_EMPTY(deviceId);
    }

    static void test_generate_returns_correct_format() {
        TEST_LOG("Testing carpe-XXXXXX format");
        
        String deviceId = generator->generate();
        
        // Should start with "carpe-"
        TEST_ASSERT_TRUE(deviceId.startsWith("carpe-"));
        
        // Should have correct length (carpe- = 6 chars + 6 random chars = 12 total)
        TEST_ASSERT_EQUAL_INT(12, deviceId.length());
        
        // Extract the random part
        String randomPart = deviceId.substring(6);
        TEST_ASSERT_EQUAL_INT(6, randomPart.length());
        
        TEST_LOG("Generated ID: " + deviceId);
    }

    static void test_generate_creates_different_ids_on_multiple_calls() {
        TEST_LOG("Testing uniqueness of generated IDs");
        
        String id1 = generator->generate();
        delay(10); // Petit délai pour changer le seed
        String id2 = generator->generate();
        delay(10);
        String id3 = generator->generate();
        
        // Les IDs devraient être différents (utilisons strcmp pour Unity)
        TEST_ASSERT_FALSE(strcmp(id1.c_str(), id2.c_str()) == 0);
        TEST_ASSERT_FALSE(strcmp(id2.c_str(), id3.c_str()) == 0);
        TEST_ASSERT_FALSE(strcmp(id1.c_str(), id3.c_str()) == 0);
        
        TEST_LOG("ID1: " + id1);
        TEST_LOG("ID2: " + id2);
        TEST_LOG("ID3: " + id3);
    }

    static void test_random_part_contains_only_valid_characters() {
        TEST_LOG("Testing character validity in random part");
        
        String deviceId = generator->generate();
        String randomPart = deviceId.substring(6);
        
        // Vérifier que chaque caractère est alphanumérique
        for (int i = 0; i < randomPart.length(); i++) {
            char c = randomPart.charAt(i);
            bool isValid = (c >= '0' && c <= '9') || 
                          (c >= 'A' && c <= 'Z') || 
                          (c >= 'a' && c <= 'z');
            TEST_ASSERT_TRUE(isValid);
        }
    }

    static void test_multiple_instances_generate_different_ids() {
        TEST_LOG("Testing that different instances generate different IDs");
        
        RandomDeviceIdGenerator generator2;
        
        String id1 = generator->generate();
        String id2 = generator2.generate();
        
        // Même si pas garanti à 100%, très peu probable d'avoir le même
        TEST_ASSERT_FALSE(strcmp(id1.c_str(), id2.c_str()) == 0);
    }
};

// Définition du membre statique
RandomDeviceIdGenerator* RandomDeviceIdGeneratorTest::generator = nullptr;

// Fonctions Unity - chaque test doit être une fonction séparée
void test_random_device_id_generate_returns_non_empty_string() {
    RandomDeviceIdGeneratorTest::setUp();
    RandomDeviceIdGeneratorTest::test_generate_returns_non_empty_string();
    RandomDeviceIdGeneratorTest::tearDown();
}

void test_random_device_id_generate_returns_correct_format() {
    RandomDeviceIdGeneratorTest::setUp();
    RandomDeviceIdGeneratorTest::test_generate_returns_correct_format();
    RandomDeviceIdGeneratorTest::tearDown();
}

void test_random_device_id_generate_creates_different_ids() {
    RandomDeviceIdGeneratorTest::setUp();
    RandomDeviceIdGeneratorTest::test_generate_creates_different_ids_on_multiple_calls();
    RandomDeviceIdGeneratorTest::tearDown();
}

void test_random_device_id_valid_characters() {
    RandomDeviceIdGeneratorTest::setUp();
    RandomDeviceIdGeneratorTest::test_random_part_contains_only_valid_characters();
    RandomDeviceIdGeneratorTest::tearDown();
}

void test_random_device_id_multiple_instances() {
    RandomDeviceIdGeneratorTest::setUp();
    RandomDeviceIdGeneratorTest::test_multiple_instances_generate_different_ids();
    RandomDeviceIdGeneratorTest::tearDown();
}

// Fonction pour regrouper tous les tests (appelée depuis test_main)
void test_random_device_id_generator_all() {
    TEST_LOG("=== RandomDeviceIdGenerator Tests ===");
    RUN_TEST(test_random_device_id_generate_returns_non_empty_string);
    RUN_TEST(test_random_device_id_generate_returns_correct_format);
    RUN_TEST(test_random_device_id_generate_creates_different_ids);
    RUN_TEST(test_random_device_id_valid_characters);
    RUN_TEST(test_random_device_id_multiple_instances);
} 