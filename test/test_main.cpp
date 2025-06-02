#include "test_framework.h"

// Déclarations des fonctions de test
void test_random_device_id_generator_all();
void test_bluetooth_integration_all();
void test_config_manager_all();
void test_nvs_config_manager_all();
void test_device_id_generator_interface_all();

void setup() {
    Serial.begin(115200);
    delay(2000); // Attendre que le Serial soit prêt
    
    Serial.println("🧪 CARPE MODULE - Test Suite");
    Serial.println("==============================");
    Serial.println("Framework: Unity + Custom Mock Framework");
    Serial.println("Architecture: Clean Architecture with Dependency Injection");
    Serial.println("Platform: ESP32");
    Serial.println();
    
    UNITY_BEGIN();
    
    // Exécuter tous les groupes de tests
    Serial.println("📋 Running Unit Tests...");
    test_random_device_id_generator_all();
    
    Serial.println();
    Serial.println("🔗 Running Integration Tests...");
    test_bluetooth_integration_all();
    
    Serial.println();
    Serial.println("⚙️ Running Configuration Tests...");
    test_config_manager_all();
    
    Serial.println();
    Serial.println("💾 Running NVS Configuration Tests...");
    test_nvs_config_manager_all();
    
    Serial.println();
    Serial.println("🏭 Running DeviceIdGenerator Interface Tests...");
    test_device_id_generator_interface_all();
    
    Serial.println();
    Serial.println("📊 Test Summary:");
    UNITY_END();
    
    Serial.println();
    Serial.println("✅ All tests completed!");
    Serial.println("==============================");
}

void loop() {
    // Tests exécutés une seule fois dans setup()
    delay(1000);
} 