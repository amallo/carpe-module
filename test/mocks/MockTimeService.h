#pragma once

#include "../../src/core/services/TimeService.h"
#include "MockFramework.h"

/**
 * @brief Mock de TimeService pour les tests
 * Permet de contrôler le temps de manière déterministe
 */

struct TimeCall {
    std::string method_name;
    unsigned long parameter;
    
    bool operator==(const TimeCall& other) const {
        return method_name == other.method_name && parameter == other.parameter;
    }
};

class MockTimeService : public TimeService, public MockBase {
private:
    CallTracker<TimeCall> call_tracker;
    unsigned long current_micros;
    
public:
    MockTimeService() : current_micros(1000000) {} // Commence à 1 seconde
    
    unsigned long getMicros() override {
        call_tracker.record_call({"getMicros", 0});
        return current_micros;
    }
    
    void delay(unsigned long ms) override {
        call_tracker.record_call({"delay", ms});
        // Simuler l'avancement du temps
        current_micros += ms * 1000; // Convertir ms en µs
    }
    
    // Méthodes pour configurer le mock
    void setCurrentMicros(unsigned long micros) {
        current_micros = micros;
    }
    
    void advanceTime(unsigned long micros) {
        current_micros += micros;
    }
    
    // Méthodes de vérification
    bool was_get_micros_called() const {
        return call_tracker.was_called_with({"getMicros", 0});
    }
    
    bool was_delay_called_with(unsigned long ms) const {
        return call_tracker.was_called_with({"delay", ms});
    }
    
    int get_call_count() const {
        return call_tracker.get_call_count();
    }
    
    void reset() override {
        call_tracker.reset();
        current_micros = 1000000;
    }
}; 