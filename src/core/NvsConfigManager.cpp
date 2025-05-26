#include "NvsConfigManager.h"

NvsConfigManager::NvsConfigManager() : deviceId("") {}


bool NvsConfigManager::loadConfig() {
    if (!prefs.begin("app_config", true)) return false;
    deviceId = prefs.getString("deviceId", "");
    prefs.end();
    return true;
}

bool NvsConfigManager::saveConfig() {
    if (!prefs.begin("app_config", false)) return false;
    prefs.putString("deviceId", deviceId);
    prefs.end();
    return true;
}

String NvsConfigManager::getDeviceId() {
    return deviceId;
}

void NvsConfigManager::setDeviceId(const String& id) {
    deviceId = id;
}

void NvsConfigManager::printConfig() {
    Serial.println("[Config]");
    Serial.print("Device ID: ");
    Serial.println(deviceId);
}
