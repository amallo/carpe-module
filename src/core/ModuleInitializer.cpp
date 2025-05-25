#include "ModuleInitializer.h"
#include <WiFi.h>

const char* ModuleInitializer::MODULE_CONFIG_FILE = "/module_config.json";

ModuleInitializer::ModuleInitializer() {
    // Initialiser SPIFFS si ce n'est pas déjà fait
    if (!SPIFFS.begin(true)) {
        Serial.println("Erreur lors de l'initialisation de SPIFFS");
    }
}

String ModuleInitializer::generateModuleId() {
    // Obtenir l'adresse MAC de l'ESP32
    uint8_t mac[6];
    WiFi.macAddress(mac);
    
    // Créer un ID hexadécimal sur 6 chiffres à partir des 3 derniers octets de la MAC
    String moduleId = "carpe-";
    
    // Utiliser les 3 derniers octets de l'adresse MAC
    for (int i = 3; i < 6; i++) {
        if (mac[i] < 16) {
            moduleId += "0"; // Ajouter un zéro devant si nécessaire
        }
        moduleId += String(mac[i], HEX);
    }
    
    moduleId.toUpperCase(); // Convertir en majuscules
    return moduleId;
}

bool ModuleInitializer::createConfigFile(const String& moduleId) {
    DynamicJsonDocument doc(JSON_BUFFER_SIZE);
    
    // Créer la structure JSON
    doc["module"]["id"] = moduleId;
    doc["module"]["name"] = moduleId;
    doc["module"]["version"] = "1.0.0";
    doc["module"]["created"] = millis(); // Timestamp de création
    doc["module"]["initialized"] = true;
    
    // Ajouter quelques paramètres par défaut
    doc["lora"]["frequency"] = 868000000;
    doc["lora"]["power"] = 20;
    doc["security"]["encryption_enabled"] = true;
    
    // Sauvegarder dans SPIFFS
    File configFile = SPIFFS.open(MODULE_CONFIG_FILE, "w");
    if (!configFile) {
        Serial.println("Impossible de créer le fichier de configuration");
        return false;
    }
    
    serializeJson(doc, configFile);
    configFile.close();
    
    Serial.println("✅ Fichier de configuration créé : " + String(MODULE_CONFIG_FILE));
    return true;
}

bool ModuleInitializer::initialize() {
    if (isAlreadyInitialized()) {
        Serial.println("🔄 Module déjà initialisé, chargement de la configuration...");
        return true;
    }
    
    Serial.println("🚀 Premier lancement détecté - Initialisation du module...");
    
    // Générer l'ID unique
    String moduleId = generateModuleId();
    Serial.println("📝 ID généré : " + moduleId);
    
    // Créer le fichier de configuration
    if (createConfigFile(moduleId)) {
        Serial.println("✅ Initialisation terminée avec succès !");
        printModuleInfo();
        return true;
    } else {
        Serial.println("❌ Erreur lors de l'initialisation");
        return false;
    }
}

bool ModuleInitializer::isAlreadyInitialized() {
    return SPIFFS.exists(MODULE_CONFIG_FILE);
}

String ModuleInitializer::getModuleId() {
    if (!isAlreadyInitialized()) {
        return ""; // Pas encore initialisé
    }
    
    File configFile = SPIFFS.open(MODULE_CONFIG_FILE, "r");
    if (!configFile) {
        return "";
    }
    
    DynamicJsonDocument doc(JSON_BUFFER_SIZE);
    DeserializationError error = deserializeJson(doc, configFile);
    configFile.close();
    
    if (error) {
        return "";
    }
    
    return doc["module"]["id"].as<String>();
}

void ModuleInitializer::printModuleInfo() {
    String moduleId = getModuleId();
    if (moduleId.length() > 0) {
        Serial.println("==========================================");
        Serial.println("📡 INFORMATIONS DU MODULE");
        Serial.println("==========================================");
        Serial.println("🆔 ID Module    : " + moduleId);
        Serial.println("📁 Config File  : " + String(MODULE_CONFIG_FILE));
        Serial.println("💾 SPIFFS       : Actif");
        Serial.println("==========================================");
    }
} 