#pragma once

#include <Arduino.h>
#include <Preferences.h>
#include "./ConfigManager.h"

/**
 * @brief Implémentation NVS de ConfigManager pour ESP32
 * Stocke la configuration dans la mémoire flash NVS (Non-Volatile Storage)
 * Suit les principes de Clean Architecture avec Dependency Inversion
 */
class NvsConfigManager : public ConfigManager {
public:
    NvsConfigManager();

    // Implémentation de l'interface ConfigManager
    bool loadConfig() override;    // Charge les valeurs depuis NVS
    bool saveConfig() override;    // Sauvegarde les valeurs dans NVS

    String getDeviceId() override;
    void setDeviceId(const String& id) override;

    void printConfig() override;

private:
    Preferences prefs;
    String deviceId;
};