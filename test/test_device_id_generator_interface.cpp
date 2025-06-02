#include "test_framework.h"
#include "mocks/MockDeviceIdGenerator.h"
#include "../src/core/device/generators/RandomDeviceIdGenerator.h"
#include "../src/core/device/generators/MacAddressDeviceIdGenerator.h"

/**
 * @brief Tests pour l'interface DeviceIdGenerator et ses implémentations
 * Vérifie le polymorphisme et l'interchangeabilité des stratégies
 */

class DeviceIdGeneratorTest {
private:
    static MockDeviceIdGenerator* mockGenerator;
    static RandomDeviceIdGenerator* randomGenerator;
    static MacAddressDeviceIdGenerator* macGenerator;

public:
    static void setUp() {
        mockGenerator = new MockDeviceIdGenerator();
        randomGenerator = new RandomDeviceIdGenerator();
        macGenerator = new MacAddressDeviceIdGenerator();
    }

    static void tearDown() {
        delete mockGenerator;
        delete randomGenerator;
        delete macGenerator;
        mockGenerator = nullptr;
        randomGenerator = nullptr;
        macGenerator = nullptr;
    }

    static void test_mock_interface_compliance() {
        TEST_LOG("Testing MockDeviceIdGenerator interface compliance");
        
        // ARRANGE - Vérifier que Mock implémente DeviceIdGenerator
        DeviceIdGenerator* generator = mockGenerator;
        mockGenerator->set_generate_return("carpe-MOCK456");
        
        // ACT
        String generatedId = generator->generate();
        
        // ASSERT
        TEST_ASSERT_EQUAL_STRING("carpe-MOCK456", generatedId.c_str());
        TEST_ASSERT_TRUE(mockGenerator->was_generate_called());
        TEST_ASSERT_EQUAL_INT(1, mockGenerator->get_call_count());
        
        TEST_LOG("Mock interface test passed - ID: " + generatedId);
    }

    static void test_random_generator_interface_compliance() {
        TEST_LOG("Testing RandomDeviceIdGenerator interface compliance");
        
        // ARRANGE - Utiliser via l'interface
        DeviceIdGenerator* generator = randomGenerator;
        
        // ACT
        String generatedId = generator->generate();
        
        // ASSERT
        TEST_ASSERT_TRUE(generatedId.startsWith("carpe-"));
        TEST_ASSERT_EQUAL_INT(12, generatedId.length());
        
        TEST_LOG("Random interface test passed - ID: " + generatedId);
    }

    static void test_mac_generator_interface_compliance() {
        TEST_LOG("Testing MacAddressDeviceIdGenerator interface compliance");
        
        // ARRANGE - Utiliser via l'interface
        DeviceIdGenerator* generator = macGenerator;
        
        // ACT
        String generatedId = generator->generate();
        
        // ASSERT
        TEST_ASSERT_TRUE(generatedId.startsWith("carpe-"));
        TEST_ASSERT_EQUAL_INT(12, generatedId.length());
        
        TEST_LOG("MAC interface test passed - ID: " + generatedId);
    }

    static void test_polymorphism_with_different_strategies() {
        TEST_LOG("Testing polymorphism with different generator strategies");
        
        // ARRANGE - Array de différentes implémentations
        DeviceIdGenerator* generators[] = {
            mockGenerator,
            randomGenerator,
            macGenerator
        };
        
        mockGenerator->set_generate_return("carpe-POLY123");
        
        // ACT & ASSERT - Utiliser chaque générateur via l'interface
        for (int i = 0; i < 3; i++) {
            String id = generators[i]->generate();
            TEST_ASSERT_TRUE(id.startsWith("carpe-"));
            TEST_ASSERT_EQUAL_INT(12, id.length());
            TEST_LOG("Strategy " + String(i) + " generated: " + id);
        }
    }

    static void test_mock_programmable_behavior() {
        TEST_LOG("Testing mock programmable behavior sequences");
        
        // ARRANGE - Programmer une séquence de valeurs
        mockGenerator->reset();
        mockGenerator->add_generate_return("carpe-SEQ001");
        mockGenerator->add_generate_return("carpe-SEQ002");
        mockGenerator->add_generate_return("carpe-SEQ003");
        
        // ACT & ASSERT - Vérifier la séquence
        String id1 = mockGenerator->generate();
        String id2 = mockGenerator->generate();
        String id3 = mockGenerator->generate();
        
        TEST_ASSERT_EQUAL_STRING("carpe-SEQ001", id1.c_str());
        TEST_ASSERT_EQUAL_STRING("carpe-SEQ002", id2.c_str());
        TEST_ASSERT_EQUAL_STRING("carpe-SEQ003", id3.c_str());
        TEST_ASSERT_EQUAL_INT(3, mockGenerator->get_call_count());
        
        TEST_LOG("Sequence test passed: " + id1 + ", " + id2 + ", " + id3);
    }

    static void test_strategy_pattern_usage() {
        TEST_LOG("Testing Strategy Pattern implementation");
        
        // ARRANGE - Fonction qui utilise n'importe quelle stratégie
        auto useGenerator = [](DeviceIdGenerator* gen) -> String {
            return gen->generate();
        };
        
        // ACT - Utiliser différentes stratégies
        mockGenerator->set_generate_return("carpe-STRAT1");
        String mockResult = useGenerator(mockGenerator);
        String randomResult = useGenerator(randomGenerator);
        String macResult = useGenerator(macGenerator);
        
        // ASSERT
        TEST_ASSERT_EQUAL_STRING("carpe-STRAT1", mockResult.c_str());
        TEST_ASSERT_TRUE(randomResult.startsWith("carpe-"));
        TEST_ASSERT_TRUE(macResult.startsWith("carpe-"));
        
        TEST_LOG("Strategy pattern test passed");
        TEST_LOG("Mock: " + mockResult);
        TEST_LOG("Random: " + randomResult);
        TEST_LOG("MAC: " + macResult);
    }
};

// Définition des membres statiques
MockDeviceIdGenerator* DeviceIdGeneratorTest::mockGenerator = nullptr;
RandomDeviceIdGenerator* DeviceIdGeneratorTest::randomGenerator = nullptr;
MacAddressDeviceIdGenerator* DeviceIdGeneratorTest::macGenerator = nullptr;

// Fonctions Unity pour chaque test
void test_device_id_mock_interface() {
    DeviceIdGeneratorTest::setUp();
    DeviceIdGeneratorTest::test_mock_interface_compliance();
    DeviceIdGeneratorTest::tearDown();
}

void test_device_id_random_interface() {
    DeviceIdGeneratorTest::setUp();
    DeviceIdGeneratorTest::test_random_generator_interface_compliance();
    DeviceIdGeneratorTest::tearDown();
}

void test_device_id_mac_interface() {
    DeviceIdGeneratorTest::setUp();
    DeviceIdGeneratorTest::test_mac_generator_interface_compliance();
    DeviceIdGeneratorTest::tearDown();
}

void test_device_id_polymorphism() {
    DeviceIdGeneratorTest::setUp();
    DeviceIdGeneratorTest::test_polymorphism_with_different_strategies();
    DeviceIdGeneratorTest::tearDown();
}

void test_device_id_mock_sequences() {
    DeviceIdGeneratorTest::setUp();
    DeviceIdGeneratorTest::test_mock_programmable_behavior();
    DeviceIdGeneratorTest::tearDown();
}

void test_device_id_strategy_pattern() {
    DeviceIdGeneratorTest::setUp();
    DeviceIdGeneratorTest::test_strategy_pattern_usage();
    DeviceIdGeneratorTest::tearDown();
}

// Fonction pour regrouper tous les tests
void test_device_id_generator_interface_all() {
    TEST_LOG("=== DeviceIdGenerator Interface Tests ===");
    RUN_TEST(test_device_id_mock_interface);
    RUN_TEST(test_device_id_random_interface);
    RUN_TEST(test_device_id_mac_interface);
    RUN_TEST(test_device_id_polymorphism);
    RUN_TEST(test_device_id_mock_sequences);
    RUN_TEST(test_device_id_strategy_pattern);
} 