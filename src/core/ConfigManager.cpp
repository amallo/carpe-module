#include "ConfigManager.h"

ConfigManager::ConfigManager() : config(JSON_BUFFER_SIZE) {}

bool ConfigManager::begin() {
    Serial.println("🔧 Initialisation de SPIFFS...");
    
    if (!SPIFFS.begin(true)) {
        Serial.println("❌ Erreur: SPIFFS.begin() a échoué");
        Serial.println("   - Vérifiez que le filesystem a été uploadé avec: pio run --target uploadfs");
        return false;
    }
    
    Serial.println("✅ SPIFFS initialisé avec succès");
    
    
    return true;
}

bool ConfigManager::loadConfig() {
    Serial.println("📖 Tentative de chargement de /config.json...");
    
    File configFile = SPIFFS.open("/config.json", "r");
    if (!configFile) {
        Serial.println("⚠️  Fichier /config.json non trouvé");
        return false; // Pas de création automatique ici
    }
    
    Serial.println("✅ Fichier /config.json ouvert (" + String(configFile.size()) + " bytes)");
    
    DeserializationError error = deserializeJson(config, configFile);
    configFile.close();
    
    if (error) {
        Serial.println("❌ Erreur lors du parsing du JSON: " + String(error.c_str()));
        return false;
    }
    
    Serial.println("✅ Configuration chargée avec succès");
    return true;
}

bool ConfigManager::saveConfig() {
    Serial.println("💾 Sauvegarde de la configuration...");
    
    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
        Serial.println("❌ Impossible de créer/ouvrir config.json");
        return false;
    }
    
    serializeJson(config, configFile);
    configFile.close();
    
    Serial.println("✅ Configuration sauvegardée dans /config.json");
    return true;
}

String ConfigManager::getDeviceId() {
    return config["device"]["id"].as<String>();
}


void ConfigManager::setDeviceId(const String& id) {
    config["device"]["id"] = id;
}

void ConfigManager::printConfig() {
    Serial.println("=== Configuration ===");
    Serial.println("Device ID: " + getDeviceId());
    Serial.println("=====================");
} 