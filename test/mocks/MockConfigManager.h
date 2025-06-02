#pragma once

#include "../../src/core/config/ConfigManager.h"
#include "MockFramework.h"
#include <string>

/**
 * @brief Mock de ConfigManager pour les tests
 * Permet de tester les interactions avec la configuration sans dépendance hardware
 */

// Structure pour enregistrer les appels aux méthodes
struct ConfigCall {
    std::string method_name;
    std::string parameter;
    
    bool operator==(const ConfigCall& other) const {
        return method_name == other.method_name && parameter == other.parameter;
    }
};

class MockConfigManager : public ConfigManager, public MockBase {
private:
    CallTracker<ConfigCall> call_tracker;
    ReturnValueManager<bool> load_config_returns;
    ReturnValueManager<bool> save_config_returns;
    ReturnValueManager<std::string> get_device_id_returns;
    
    // État simulé
    std::string simulated_device_id;

public:
    MockConfigManager() 
        : load_config_returns(true)
        , save_config_returns(true)
        , get_device_id_returns("carpe-MOCK123")
        , simulated_device_id("carpe-MOCK123") {
    }

    // Implémentation des méthodes virtuelles
    bool loadConfig() override {
        call_tracker.record_call({"loadConfig", ""});
        return load_config_returns.get_next_return_value();
    }

    bool saveConfig() override {
        call_tracker.record_call({"saveConfig", ""});
        return save_config_returns.get_next_return_value();
    }

    std::string getDeviceId() override {
        call_tracker.record_call({"getDeviceId", ""});
        return simulated_device_id.empty() ? 
               get_device_id_returns.get_next_return_value() : 
               simulated_device_id;
    }

    void setDeviceId(const std::string& id) override {
        call_tracker.record_call({"setDeviceId", id});
        simulated_device_id = id;
    }

    void printConfig() override {
        call_tracker.record_call({"printConfig", ""});
        // Mock - ne fait rien de réel
    }

    // Méthodes pour programmer le comportement du mock
    void set_load_config_return(bool value) { 
        load_config_returns.set_return_value(value); 
    }
    void set_save_config_return(bool value) { 
        save_config_returns.set_return_value(value); 
    }
    void set_get_device_id_return(const std::string& value) { 
        get_device_id_returns.set_return_value(value);
        simulated_device_id = value;
    }

    // Méthodes pour ajouter plusieurs valeurs de retour (séquences)
    void add_load_config_return(bool value) { 
        load_config_returns.add_return_value(value); 
    }
    void add_save_config_return(bool value) { 
        save_config_returns.add_return_value(value); 
    }

    // Méthodes de vérification (assertions)
    bool was_load_config_called() const {
        return call_tracker.was_called_with({"loadConfig", ""});
    }

    bool was_save_config_called() const {
        return call_tracker.was_called_with({"saveConfig", ""});
    }

    bool was_get_device_id_called() const {
        return call_tracker.was_called_with({"getDeviceId", ""});
    }

    bool was_set_device_id_called_with(const std::string& id) const {
        return call_tracker.was_called_with({"setDeviceId", id});
    }

    bool was_print_config_called() const {
        return call_tracker.was_called_with({"printConfig", ""});
    }

    int get_call_count() const {
        return call_tracker.get_call_count();
    }

    ConfigCall get_last_call() const {
        return call_tracker.get_last_call();
    }

    // Reset pour nettoyer entre les tests
    void reset() override {
        call_tracker.reset();
        load_config_returns.reset();
        save_config_returns.reset();
        get_device_id_returns.reset();
        simulated_device_id = "carpe-MOCK123";
    }
}; 