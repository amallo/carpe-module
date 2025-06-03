#include <core/config/providers/ConfigProvider.h>
#include <core/config/providers/nvs/NvsConfigProvider.h>

#include <Arduino.h>

NvsConfigProvider::NvsConfigProvider() : deviceId("") {}

bool NvsConfigProvider::loadConfig() {
    if (!prefs.begin("app_config", true)) return false;
    String arduinoDeviceId = prefs.getString("deviceId", "");
    deviceId = std::string(arduinoDeviceId.c_str());
    prefs.end();
    return true;
}

bool NvsConfigProvider::saveConfig() {
    if (!prefs.begin("app_config", false)) return false;
    
    // Version Arduino - conversion std::string -> Arduino String
    String arduinoDeviceId = String(deviceId.c_str());
    prefs.putString("deviceId", arduinoDeviceId);
    
    prefs.end();
    return true;
}

std::string NvsConfigProvider::getDeviceId() {
    return deviceId;
}

void NvsConfigProvider::setDeviceId(const std::string& id) {
    deviceId = id;
}

void NvsConfigProvider::printConfig() {
    Serial.println("[Config]");
    Serial.print("Device ID: ");
    Serial.println(deviceId.c_str());
}
