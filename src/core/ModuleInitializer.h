#pragma once
#include <Arduino.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>

class ModuleInitializer {
private:
    static const char* MODULE_CONFIG_FILE;
    static const size_t JSON_BUFFER_SIZE = 512;
    
    String generateModuleId();
    bool createConfigFile(const String& moduleId);
    
public:
    ModuleInitializer();
    
    bool initialize();
    bool isAlreadyInitialized();
    String getModuleId();
    
    void printModuleInfo();
}; 