#pragma once

#include <string>
#include <Preferences.h>
#include <core/config/providers/ConfigProvider.h>

/**
 * @brief Implémentation NVS de ConfigProvider pour ESP32
 * Stocke la configuration dans la mémoire flash NVS (Non-Volatile Storage)
 * Suit les principes de Clean Architecture avec Dependency Inversion
 */
class NvsConfigProvider : public ConfigProvider {
public:

    std::string getDeviceId() override;
    void setDeviceId(const std::string& id) override;


private:
    Preferences prefs;
};