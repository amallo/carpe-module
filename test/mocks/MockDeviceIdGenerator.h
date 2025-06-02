#pragma once

#include "../../src/core/device/DeviceIdGenerator.h"
#include "MockFramework.h"
#include <string>

/**
 * @brief Mock de DeviceIdGenerator pour les tests
 * Permet de tester les interactions avec la génération d'ID sans dépendance hardware
 */

// Structure pour enregistrer les appels aux méthodes
struct GeneratorCall {
    std::string method_name;
    
    bool operator==(const GeneratorCall& other) const {
        return method_name == other.method_name;
    }
};

class MockDeviceIdGenerator : public DeviceIdGenerator, public MockBase {
private:
    CallTracker<GeneratorCall> call_tracker;
    ReturnValueManager<std::string> generate_returns;

public:
    MockDeviceIdGenerator() 
        : generate_returns("carpe-MOCK123") {
    }

    // Implémentation de l'interface
    std::string generate() override {
        call_tracker.record_call({"generate"});
        return generate_returns.get_next_return_value();
    }

    // Méthodes pour programmer le comportement du mock
    void set_generate_return(const std::string& value) { 
        generate_returns.set_return_value(value); 
    }

    // Méthodes pour ajouter plusieurs valeurs de retour (séquences)
    void add_generate_return(const std::string& value) { 
        generate_returns.add_return_value(value); 
    }

    // Méthodes de vérification (assertions)
    bool was_generate_called() const {
        return call_tracker.was_called_with({"generate"});
    }

    int get_call_count() const {
        return call_tracker.get_call_count();
    }

    GeneratorCall get_last_call() const {
        return call_tracker.get_last_call();
    }

    // Reset pour nettoyer entre les tests
    void reset() override {
        call_tracker.reset();
        generate_returns.reset();
    }
}; 