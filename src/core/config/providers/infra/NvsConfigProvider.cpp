#include <core/config/providers/ConfigProvider.h>
#include "NvsConfigProvider.h"

#include <Arduino.h>



std::string NvsConfigProvider::getDeviceId() {
    if (!prefs.begin("app_config", true)) return "";
    String arduinoDeviceId = prefs.getString("deviceId", "");
    return std::string(arduinoDeviceId.c_str());
    prefs.end();
}

void NvsConfigProvider::setDeviceId(const std::string& deviceId) {
    if (!prefs.begin("app_config", false)) return;
    String arduinoDeviceId = String(deviceId.c_str());
    prefs.putString("deviceId", arduinoDeviceId);
    prefs.end();
}

std::string NvsConfigProvider::getPinCode() {
    if (!prefs.begin("app_config", true)) return "";
    String arduinoPinCode = prefs.getString("pinCode", "");
    prefs.end();
    return std::string(arduinoPinCode.c_str());
}

void NvsConfigProvider::setPinCode(const std::string& pinCode) {
    if (!prefs.begin("app_config", false)) return;
    String arduinoPinCode = String(pinCode.c_str());
    prefs.putString("pinCode", arduinoPinCode);
    prefs.end();
}
