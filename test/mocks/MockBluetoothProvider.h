#pragma once

#include "../../src/core/BluetoothProvider.h"
#include "MockFramework.h"

/**
 * @brief Mock de BluetoothProvider pour les tests
 * Suit les principes des test doubles avec enregistrement des appels et programmation des retours
 */

// Structure pour enregistrer les appels aux méthodes
struct BluetoothCall {
    String method_name;
    String parameter;
    
    bool operator==(const BluetoothCall& other) const {
        return method_name == other.method_name && parameter == other.parameter;
    }
};

class MockBluetoothProvider : public BluetoothProvider, public MockBase {
private:
    CallTracker<BluetoothCall> call_tracker;
    ReturnValueManager<bool> init_returns;
    ReturnValueManager<bool> start_returns;
    ReturnValueManager<bool> is_connected_returns;
    ReturnValueManager<bool> send_string_returns;

public:
    MockBluetoothProvider() 
        : init_returns(true)
        , start_returns(true) 
        , is_connected_returns(false)
        , send_string_returns(true) {
    }

    // Implémentation des méthodes virtuelles
    bool init(const String& deviceId) override {
        call_tracker.record_call({"init", deviceId});
        return init_returns.get_next_return_value();
    }

    bool start() override {
        call_tracker.record_call({"start", ""});
        return start_returns.get_next_return_value();
    }

    bool isConnected() override {
        call_tracker.record_call({"isConnected", ""});
        return is_connected_returns.get_next_return_value();
    }

    bool sendString(const String& message) override {
        call_tracker.record_call({"sendString", message});
        return send_string_returns.get_next_return_value();
    }

    // Méthodes pour programmer le comportement du mock
    void set_init_return(bool value) { init_returns.set_return_value(value); }
    void set_start_return(bool value) { start_returns.set_return_value(value); }
    void set_is_connected_return(bool value) { is_connected_returns.set_return_value(value); }
    void set_send_string_return(bool value) { send_string_returns.set_return_value(value); }

    // Méthodes pour ajouter plusieurs valeurs de retour (pour tester des séquences)
    void add_init_return(bool value) { init_returns.add_return_value(value); }
    void add_start_return(bool value) { start_returns.add_return_value(value); }
    void add_is_connected_return(bool value) { is_connected_returns.add_return_value(value); }
    void add_send_string_return(bool value) { send_string_returns.add_return_value(value); }

    // Méthodes de vérification (assertions)
    bool was_init_called() const { 
        return call_tracker.was_called_with({"init", ""}); 
    }
    
    bool was_init_called_with(const String& deviceId) const {
        return call_tracker.was_called_with({"init", deviceId});
    }

    bool was_start_called() const {
        return call_tracker.was_called_with({"start", ""});
    }

    bool was_is_connected_called() const {
        return call_tracker.was_called_with({"isConnected", ""});
    }

    bool was_send_string_called_with(const String& message) const {
        return call_tracker.was_called_with({"sendString", message});
    }

    int get_call_count() const {
        return call_tracker.get_call_count();
    }

    BluetoothCall get_last_call() const {
        return call_tracker.get_last_call();
    }

    // Reset pour nettoyer entre les tests
    void reset() override {
        call_tracker.reset();
        init_returns.reset();
        start_returns.reset();
        is_connected_returns.reset();
        send_string_returns.reset();
    }
}; 