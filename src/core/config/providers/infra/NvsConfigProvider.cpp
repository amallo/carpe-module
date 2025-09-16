#include <core/config/providers/ConfigProvider.h>
#include <core/config/providers/nvs/NvsConfigProvider.h>

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
