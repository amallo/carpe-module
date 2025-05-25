#include "ConfigManager.h"

ConfigManager::ConfigManager() : config(JSON_BUFFER_SIZE) {}

bool ConfigManager::begin() {
    if (!SPIFFS.begin(true)) {
        Serial.println("Erreur lors de l'initialisation de SPIFFS");
        return false;
    }
    return loadConfig();
}

bool ConfigManager::loadConfig() {
    File configFile = SPIFFS.open("/config.json", "r");
    if (!configFile) {
        Serial.println("Impossible d'ouvrir config.json");
        return false;
    }
    
    DeserializationError error = deserializeJson(config, configFile);
    configFile.close();
    
    if (error) {
        Serial.println("Erreur lors du parsing du JSON: " + String(error.c_str()));
        return false;
    }
    
    Serial.println("Configuration chargée avec succès");
    return true;
}

bool ConfigManager::saveConfig() {
    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
        Serial.println("Impossible de sauvegarder config.json");
        return false;
    }
    
    serializeJson(config, configFile);
    configFile.close();
    
    Serial.println("Configuration sauvegardée");
    return true;
}

String ConfigManager::getDeviceId() {
    return config["device"]["id"].as<String>();
}

String ConfigManager::getDeviceName() {
    return config["device"]["name"].as<String>();
}

long ConfigManager::getLoRaFrequency() {
    return config["lora"]["frequency"].as<long>();
}

int ConfigManager::getLoRaPower() {
    return config["lora"]["power"].as<int>();
}

bool ConfigManager::isEncryptionEnabled() {
    return config["security"]["encryption_enabled"].as<bool>();
}

int ConfigManager::getMessageTimeout() {
    return config["protocol"]["message_timeout"].as<int>();
}

void ConfigManager::setDeviceId(const String& id) {
    config["device"]["id"] = id;
}

void ConfigManager::setLoRaFrequency(long frequency) {
    config["lora"]["frequency"] = frequency;
}

void ConfigManager::setEncryptionEnabled(bool enabled) {
    config["security"]["encryption_enabled"] = enabled;
}

void ConfigManager::printConfig() {
    Serial.println("=== Configuration ===");
    Serial.println("Device ID: " + getDeviceId());
    Serial.println("Device Name: " + getDeviceName());
    Serial.println("LoRa Frequency: " + String(getLoRaFrequency()));
    Serial.println("LoRa Power: " + String(getLoRaPower()));
    Serial.println("Encryption: " + String(isEncryptionEnabled() ? "Enabled" : "Disabled"));
    Serial.println("Message Timeout: " + String(getMessageTimeout()) + "ms");
    Serial.println("=====================");
} 