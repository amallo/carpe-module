#include "NvsConfigManager.h"

#ifdef NATIVE_BUILD
#include "../../test/native_stubs.h"
// Pour l'environnement natif, on utilise directement std::string
using Preferences = PreferencesStub;
using String = std::string;
#else
#include <Arduino.h>
#endif

NvsConfigManager::NvsConfigManager() : deviceId("") {}

bool NvsConfigManager::loadConfig() {
    if (!prefs.begin("app_config", true)) return false;
    
#ifdef NATIVE_BUILD
    // Version native - pas de conversion nécessaire
    deviceId = prefs.getString("deviceId", "");
#else
    // Version Arduino - conversion Arduino String -> std::string
    String arduinoDeviceId = prefs.getString("deviceId", "");
    deviceId = std::string(arduinoDeviceId.c_str());
#endif
    
    prefs.end();
    return true;
}

bool NvsConfigManager::saveConfig() {
    if (!prefs.begin("app_config", false)) return false;
    
#ifdef NATIVE_BUILD
    // Version native - pas de conversion nécessaire
    prefs.putString("deviceId", deviceId);
#else
    // Version Arduino - conversion std::string -> Arduino String
    String arduinoDeviceId = String(deviceId.c_str());
    prefs.putString("deviceId", arduinoDeviceId);
#endif
    
    prefs.end();
    return true;
}

std::string NvsConfigManager::getDeviceId() {
    return deviceId;
}

void NvsConfigManager::setDeviceId(const std::string& id) {
    deviceId = id;
}

void NvsConfigManager::printConfig() {
    Serial.println("[Config]");
    Serial.print("Device ID: ");
    Serial.println(deviceId.c_str());
}
