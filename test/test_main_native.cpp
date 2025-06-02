#include "test_framework.h"
#include <iostream>

// Déclarations des fonctions de test
void test_random_device_id_generator_native_all();

// Fonctions globales Unity
void setUp() {
    // Setup global pour chaque test
}

void tearDown() {
    // Cleanup global pour chaque test
}

int main() {
    std::cout << "🧪 CARPE MODULE - Native Test Suite" << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << "Framework: Unity + Custom Mock Framework" << std::endl;
    std::cout << "Architecture: Clean Architecture with Dependency Injection" << std::endl;
    std::cout << "Platform: Native (Desktop)" << std::endl;
    std::cout << std::endl;
    
    UNITY_BEGIN();
    
    // Exécuter tous les groupes de tests
    std::cout << "📋 Running Unit Tests..." << std::endl;
    test_random_device_id_generator_native_all();
    
    std::cout << std::endl;
    std::cout << "📊 Test Summary:" << std::endl;
    int result = UNITY_END();
    
    std::cout << std::endl;
    std::cout << "✅ All tests completed!" << std::endl;
    std::cout << "====================================" << std::endl;
    
    return result;
} 