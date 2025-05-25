#pragma once
#include <Arduino.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>

class ConfigManager {
private:
    static const size_t JSON_BUFFER_SIZE = 1024;
    DynamicJsonDocument config;
    
public:
    ConfigManager();
    
    bool begin();
    bool loadConfig();
    bool saveConfig();
    
    // Getters pour les différentes sections
    String getDeviceId();
    
    // Setters
    void setDeviceId(const String& id);
    
    void printConfig();
}; 