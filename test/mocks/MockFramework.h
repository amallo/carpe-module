#pragma once

#include <vector>
#include <functional>
#include <string>
#include <map>

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

// Structure générique pour les appels de méthode
template<typename ParamType = std::string>
struct MethodCall {
    std::string method_name;
    ParamType parameter;
    
    MethodCall() = default;
    MethodCall(const std::string& method, const ParamType& param) 
        : method_name(method), parameter(param) {}
    
    bool operator==(const MethodCall& other) const {
        return method_name == other.method_name && parameter == other.parameter;
    }
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
    // Constructeur par défaut avec valeur par défaut basée sur le type
    ReturnValueManager() : default_value(T{}) {}
    
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

/**
 * @brief Template générique pour créer des mocks facilement
 */
template<typename CallType = MethodCall<std::string>>
class GenericMock : public MockBase {
protected:
    CallTracker<CallType> call_tracker;
    std::map<std::string, ReturnValueManager<bool>> bool_returns;

public:
    GenericMock() = default;

    // Méthodes génériques pour enregistrer les appels
    void record_call(const CallType& call) {
        call_tracker.record_call(call);
    }

    // Méthodes génériques pour configurer les retours
    void set_return_value(const std::string& method, bool value) {
        auto it = bool_returns.find(method);
        if (it != bool_returns.end()) {
            it->second.set_return_value(value);
        } else {
            bool_returns.emplace(method, ReturnValueManager<bool>(value));
        }
    }

    void add_return_value(const std::string& method, bool value) {
        auto it = bool_returns.find(method);
        if (it != bool_returns.end()) {
            it->second.add_return_value(value);
        } else {
            // Créer avec constructeur par défaut puis ajouter la valeur
            bool_returns.emplace(method, ReturnValueManager<bool>(true));
            bool_returns.at(method).add_return_value(value);
        }
    }

    bool get_return_value(const std::string& method) {
        auto it = bool_returns.find(method);
        return (it != bool_returns.end()) ? it->second.get_next_return_value() : true;
    }

    // Méthodes de vérification
    bool was_called(const std::string& method, const std::string& param = "") const {
        return call_tracker.was_called_with({method, param});
    }

    int get_call_count() const {
        return call_tracker.get_call_count();
    }

    CallType get_last_call() const {
        return call_tracker.get_last_call();
    }

    void reset() override {
        call_tracker.reset();
        for (auto& pair : bool_returns) {
            pair.second.reset();
        }
    }
}; 