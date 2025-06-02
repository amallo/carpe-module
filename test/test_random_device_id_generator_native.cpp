#include "test_framework.h"
#include "mocks/MockRandomService.h"
#include "mocks/MockTimeService.h"
#include "../src/core/device/generators/RandomDeviceIdGenerator.h"

/**
 * @brief Tests natifs pour RandomDeviceIdGenerator avec injection de dépendances
 * Démontre comment tester la logique pure sans dépendances hardware
 */

class RandomDeviceIdGeneratorNativeTest {
private:
    static MockRandomService* mockRandom;
    static MockTimeService* mockTime;
    static RandomDeviceIdGenerator* generator;

public:
    static void setUp() {
        mockRandom = new MockRandomService();
        mockTime = new MockTimeService();
        generator = new RandomDeviceIdGenerator(mockRandom, mockTime);
    }

    static void tearDown() {
        delete generator;
        delete mockTime;
        delete mockRandom;
        generator = nullptr;
        mockTime = nullptr;
        mockRandom = nullptr;
    }

    static void test_generate_returns_correct_format() {
        TEST_LOG("Testing carpe-XXXXXX format with mocked random values");
        
        // ARRANGE - Programmer des valeurs déterministes
        // Indices pour "carpe-123456": [1,2,3,4,5,6] dans "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        std::vector<int> values = {1, 2, 3, 4, 5, 6}; // Correspondra à "123456"
        mockRandom->setNextRandomValues(values);
        
        // ACT
        std::string deviceId = generator->generate();
        
        // ASSERT - Tests de base
        TEST_LOG("Generated ID: " + deviceId);
        TEST_ASSERT_EQUAL_STDSTRING("carpe-123456", deviceId);
        TEST_ASSERT_EQUAL_INT(12, deviceId.length());
        
        // Test du préfixe
        std::string prefix = deviceId.substr(0, 6);
        TEST_ASSERT_EQUAL_STDSTRING("carpe-", prefix);
        
        TEST_LOG("Random service call count: " + std::to_string(mockRandom->get_call_count()));
    }

    static void test_generate_creates_different_ids_with_different_seeds() {
        TEST_LOG("Testing uniqueness with different time seeds");
        
        // ARRANGE - Premier générateur avec seed 1000000
        mockTime->setCurrentMicros(1000000);
        mockRandom->setNextRandomValues({10, 11, 12, 13, 14, 15}); // "ABCDEF"
        
        // ACT - Premier ID
        std::string id1 = generator->generate();
        
        // ARRANGE - Nouveau générateur avec seed différent
        mockTime->setCurrentMicros(2000000);
        MockRandomService mockRandom2;
        MockTimeService mockTime2;
        mockTime2.setCurrentMicros(2000000);
        mockRandom2.setNextRandomValues({20, 21, 22, 23, 24, 25}); // "KLMNOP"
        
        RandomDeviceIdGenerator generator2(&mockRandom2, &mockTime2);
        
        // ACT - Deuxième ID
        std::string id2 = generator2.generate();
        
        // ASSERT
        TEST_ASSERT_EQUAL_STDSTRING("carpe-ABCDEF", id1);
        TEST_ASSERT_EQUAL_STDSTRING("carpe-KLMNOP", id2);
        TEST_ASSERT_NOT_EQUAL_STDSTRING(id1, id2);
        
        TEST_LOG("ID1: " + id1);
        TEST_LOG("ID2: " + id2);
    }

    static void test_deterministic_behavior_with_same_seed() {
        TEST_LOG("Testing deterministic behavior with same values");
        
        // ARRANGE - Mêmes valeurs aléatoires
        std::vector<int> values = {0, 35, 18, 7, 14, 31}; // "0ZI7EV"
        mockRandom->setNextRandomValues(values);
        
        // ACT - Premier appel
        std::string id1 = generator->generate();
        
        // ARRANGE - Reset et mêmes valeurs
        mockRandom->reset();
        mockRandom->setNextRandomValues(values);
        MockTimeService mockTime2;
        RandomDeviceIdGenerator generator2(mockRandom, &mockTime2);
        
        // ACT - Deuxième appel
        std::string id2 = generator2.generate();
        
        // ASSERT
        TEST_ASSERT_EQUAL_STDSTRING_TO_STDSTRING(id1, id2);
        TEST_ASSERT_EQUAL_STDSTRING("carpe-0ZI7EV", id1);
        
        TEST_LOG("Deterministic ID: " + id1);
    }

    static void test_dependency_injection_calls() {
        TEST_LOG("Testing dependency injection calls");
        
        // ARRANGE
        mockRandom->setNextRandomValues({0, 1, 2, 3, 4, 5});
        
        // ACT
        std::string deviceId = generator->generate();
        
        // ASSERT - Vérifier que les dépendances ont été utilisées correctement
        TEST_LOG("Was getMicros called? " + std::string(mockTime->was_get_micros_called() ? "YES" : "NO"));
        TEST_LOG("Was setSeed called? " + std::string(mockRandom->was_set_seed_called() ? "YES" : "NO"));
        TEST_LOG("Random call count: " + std::to_string(mockRandom->get_call_count()));
        
        // Tests simplifiés
        TEST_ASSERT_TRUE(mockTime->was_get_micros_called());
        TEST_ASSERT_TRUE(mockRandom->was_set_seed_called());
        TEST_ASSERT_TRUE(mockRandom->get_call_count() >= 6);
        
        TEST_LOG("Dependencies correctly injected and called");
        TEST_LOG("Generated ID: " + deviceId);
    }

    static void test_character_validity() {
        TEST_LOG("Testing character validity in generated ID");
        
        // ARRANGE - Tester les valeurs limites
        std::vector<int> values = {0, 9, 10, 35, 18, 25}; // "09AZS..."
        mockRandom->setNextRandomValues(values);
        
        // ACT
        std::string deviceId = generator->generate();
        
        // ASSERT
        std::string randomPart = deviceId.substr(6);
        TEST_ASSERT_EQUAL_INT(6, randomPart.length());
        
        // Vérifier que chaque caractère est valide (0-9, A-Z)
        for (char c : randomPart) {
            bool isValid = (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z');
            TEST_ASSERT_TRUE(isValid);
        }
        
        TEST_LOG("All characters valid: " + randomPart);
    }
};

// Définition des membres statiques
MockRandomService* RandomDeviceIdGeneratorNativeTest::mockRandom = nullptr;
MockTimeService* RandomDeviceIdGeneratorNativeTest::mockTime = nullptr;
RandomDeviceIdGenerator* RandomDeviceIdGeneratorNativeTest::generator = nullptr;

// Fonctions Unity pour chaque test
void test_native_generate_format() {
    RandomDeviceIdGeneratorNativeTest::setUp();
    RandomDeviceIdGeneratorNativeTest::test_generate_returns_correct_format();
    RandomDeviceIdGeneratorNativeTest::tearDown();
}

void test_native_different_seeds() {
    RandomDeviceIdGeneratorNativeTest::setUp();
    RandomDeviceIdGeneratorNativeTest::test_generate_creates_different_ids_with_different_seeds();
    RandomDeviceIdGeneratorNativeTest::tearDown();
}

void test_native_deterministic() {
    RandomDeviceIdGeneratorNativeTest::setUp();
    RandomDeviceIdGeneratorNativeTest::test_deterministic_behavior_with_same_seed();
    RandomDeviceIdGeneratorNativeTest::tearDown();
}

void test_native_dependency_injection() {
    RandomDeviceIdGeneratorNativeTest::setUp();
    RandomDeviceIdGeneratorNativeTest::test_dependency_injection_calls();
    RandomDeviceIdGeneratorNativeTest::tearDown();
}

void test_native_character_validity() {
    RandomDeviceIdGeneratorNativeTest::setUp();
    RandomDeviceIdGeneratorNativeTest::test_character_validity();
    RandomDeviceIdGeneratorNativeTest::tearDown();
}

// Fonction pour regrouper tous les tests
void test_random_device_id_generator_native_all() {
    TEST_LOG("=== RandomDeviceIdGenerator Native Tests ===");
    RUN_TEST(test_native_generate_format);
    RUN_TEST(test_native_different_seeds);
    RUN_TEST(test_native_deterministic);
    RUN_TEST(test_native_dependency_injection);
    RUN_TEST(test_native_character_validity);
} 