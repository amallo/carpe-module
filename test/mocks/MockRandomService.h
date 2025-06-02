#pragma once

#include "../../src/core/services/RandomService.h"
#include "MockFramework.h"
#include <vector>

/**
 * @brief Mock de RandomService pour les tests
 * Permet de contrôler les valeurs aléatoires de manière déterministe
 */

struct RandomCall {
    std::string method_name;
    int min_value;
    int max_value;
    
    bool operator==(const RandomCall& other) const {
        return method_name == other.method_name && 
               min_value == other.min_value && 
               max_value == other.max_value;
    }
};

class MockRandomService : public RandomService, public MockBase {
private:
    CallTracker<RandomCall> call_tracker;
    std::vector<int> predefined_values;
    size_t current_index;
    
public:
    MockRandomService() : current_index(0) {}
    
    int getRandomInt(int min, int max) override {
        call_tracker.record_call({"getRandomInt", min, max});
        
        if (!predefined_values.empty()) {
            int value = predefined_values[current_index % predefined_values.size()];
            current_index++;
            return value;
        }
        
        // Valeur par défaut si aucune valeur prédéfinie
        return min;
    }
    
    void setSeed(unsigned long seed) override {
        call_tracker.record_call({"setSeed", static_cast<int>(seed), 0});
    }
    
    // Méthodes pour configurer le mock
    void setNextRandomValues(const std::vector<int>& values) {
        predefined_values = values;
        current_index = 0;
    }
    
    void addRandomValue(int value) {
        predefined_values.push_back(value);
    }
    
    // Méthodes de vérification
    bool was_get_random_int_called_with(int min, int max) const {
        return call_tracker.was_called_with({"getRandomInt", min, max});
    }
    
    bool was_set_seed_called() const {
        // Chercher n'importe quel appel setSeed (peu importe le seed)
        for (const auto& call : call_tracker.get_calls()) {
            if (call.method_name == "setSeed") {
                return true;
            }
        }
        return false;
    }
    
    int get_call_count() const {
        return call_tracker.get_call_count();
    }
    
    void reset() override {
        call_tracker.reset();
        predefined_values.clear();
        current_index = 0;
    }
}; 