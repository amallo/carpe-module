#ifndef NVS_CONFIG_MANAGER_H
#define NVS_CONFIG_MANAGER_H

#include <Arduino.h>
#include <Preferences.h>

class NvsConfigManager {
public:
    NvsConfigManager();

    bool loadConfig();    // Charge les valeurs depuis NVS
    bool saveConfig();    // Sauvegarde les valeurs dans NVS

    String getDeviceId();
    void setDeviceId(const String& id);

    void printConfig();

private:
    Preferences prefs;
    String deviceId;
};

#endif // NVS_CONFIG_MANAGER_H