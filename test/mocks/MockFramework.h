#pragma once

#include <vector>
#include <functional>
#include <string>

/**
 * @brief Framework de mock simple pour tests natifs
 * Version sans dépendances Arduino - fonctionne sur desktop
 */

// Classe de base pour tous les mocks
class MockBase {
public:
    virtual void reset() = 0;
    virtual ~MockBase() = default;
};

// Template pour les call trackers
template<typename T>
class CallTracker {
private:
    std::vector<T> calls;
    int call_count = 0;

public:
    void record_call(const T& call_info) {
        calls.push_back(call_info);
        call_count++;
    }

    int get_call_count() const { return call_count; }
    
    bool was_called() const { return call_count > 0; }
    
    bool was_called_with(const T& expected) const {
        for (const auto& call : calls) {
            if (call == expected) return true;
        }
        return false;
    }

    T get_last_call() const {
        return calls.empty() ? T{} : calls.back();
    }

    const std::vector<T>& get_calls() const {
        return calls;
    }

    void reset() {
        calls.clear();
        call_count = 0;
    }
};

// Classe pour gérer les valeurs de retour programmées
template<typename T>
class ReturnValueManager {
private:
    std::vector<T> return_values;
    int current_index = 0;
    T default_value;

public:
    explicit ReturnValueManager(T default_val) : default_value(default_val) {}

    void set_return_value(const T& value) {
        return_values.clear();
        return_values.push_back(value);
        current_index = 0;
    }

    void add_return_value(const T& value) {
        return_values.push_back(value);
    }

    T get_next_return_value() {
        if (return_values.empty()) return default_value;
        
        T value = return_values[current_index];
        if (current_index < return_values.size() - 1) {
            current_index++;
        }
        return value;
    }

    void reset() {
        return_values.clear();
        current_index = 0;
    }
}; 