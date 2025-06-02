#pragma once

#include "../../src/core/transport/providers/BluetoothProvider.h"
#include "MockFramework.h"
#include <string>

/**
 * @brief Mock de BluetoothProvider pour les tests - Version factorisée
 * Utilise le template générique pour éviter la duplication
 */

// Type spécialisé pour les appels Bluetooth
using BluetoothCall = MethodCall<std::string>;

class MockBluetoothProvider : public BluetoothProvider {
private:
    CallTracker<BluetoothCall> call_tracker;
    ReturnValueManager<bool> init_returns;
    ReturnValueManager<bool> start_returns;
    ReturnValueManager<bool> is_connected_returns;
    ReturnValueManager<bool> send_string_returns;
    ReturnValueManager<bool> is_started_returns;

public:
    MockBluetoothProvider() 
        : init_returns(true)
        , start_returns(true)
        , is_connected_returns(false)
        , send_string_returns(true)
        , is_started_returns(true) {
    }

    // Implémentation des méthodes virtuelles
    bool init(const std::string& deviceId) override {
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

    bool sendString(const std::string& message) override {
        call_tracker.record_call({"sendString", message});
        return send_string_returns.get_next_return_value();
    }

    bool isStarted() override {
        call_tracker.record_call({"isStarted", ""});
        return is_started_returns.get_next_return_value();
    }

    // Méthodes pour configurer le comportement du mock
    void set_init_return(bool value) { init_returns.set_return_value(value); }
    void set_start_return(bool value) { start_returns.set_return_value(value); }
    void set_is_connected_return(bool value) { is_connected_returns.set_return_value(value); }
    void set_send_string_return(bool value) { send_string_returns.set_return_value(value); }
    void set_is_started_return(bool value) { is_started_returns.set_return_value(value); }
    
    void add_init_return(bool value) { init_returns.add_return_value(value); }
    void add_start_return(bool value) { start_returns.add_return_value(value); }
    void add_is_connected_return(bool value) { is_connected_returns.add_return_value(value); }
    void add_send_string_return(bool value) { send_string_returns.add_return_value(value); }
    void add_is_started_return(bool value) { is_started_returns.add_return_value(value); }

    // Méthodes de vérification
    bool was_init_called() const {
        return call_tracker.was_called_with({"init", ""});
    }

    bool was_init_called_with(const std::string& deviceId) const {
        return call_tracker.was_called_with({"init", deviceId});
    }

    bool was_start_called() const {
        return call_tracker.was_called_with({"start", ""});
    }

    bool was_is_connected_called() const {
        return call_tracker.was_called_with({"isConnected", ""});
    }

    bool was_send_string_called_with(const std::string& message) const {
        return call_tracker.was_called_with({"sendString", message});
    }

    int get_call_count() const {
        return call_tracker.get_call_count();
    }

    BluetoothCall get_last_call() const {
        return call_tracker.get_last_call();
    }

    // Reset pour nettoyer entre les tests
    void reset() {
        call_tracker.reset();
        init_returns.reset();
        start_returns.reset();
        is_connected_returns.reset();
        send_string_returns.reset();
        is_started_returns.reset();
    }

    // API fluide pour une utilisation plus moderne
    MockBluetoothProvider& will_init_return(bool value) {
        set_init_return(value);
        return *this;
    }

    MockBluetoothProvider& will_start_return(bool value) {
        set_start_return(value);
        return *this;
    }

    MockBluetoothProvider& will_be_connected(bool value) {
        set_is_connected_return(value);
        return *this;
    }

    MockBluetoothProvider& will_send_string_return(bool value) {
        set_send_string_return(value);
        return *this;
    }
}; 