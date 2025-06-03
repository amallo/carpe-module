#pragma once
#include <core/logging/Logger.h>
#include <Arduino.h>

/**
 * @brief Implémentation Arduino de Logger utilisant Serial
 * Pour le hardware ESP32 et environnements Arduino
 * Affiche les logs sur le port série avec préfixes et horodatage
 */
class SerialLogger : public Logger {
private:
    LogLevel currentLevel;
    bool showTimestamp;
    
    /**
     * @brief Convertit un LogLevel en string pour l'affichage
     * @param level le niveau à convertir
     * @return const char* représentation textuelle
     */
    const char* levelToString(LogLevel level) const {
        switch (level) {
            case LogLevel::DEBUG: return "DEBUG";
            case LogLevel::INFO:  return "INFO ";
            case LogLevel::WARN:  return "WARN ";
            case LogLevel::ERROR: return "ERROR";
            default: return "UNKNOWN";
        }
    }
    
    /**
     * @brief Affiche le préfixe du log (timestamp + niveau)
     * @param level niveau du message
     */
    void printPrefix(LogLevel level) const {
        if (showTimestamp) {
            Serial.print("[");
            Serial.print(millis());
            Serial.print("] ");
        }
        Serial.print("[");
        Serial.print(levelToString(level));
        Serial.print("] ");
    }

public:
    /**
     * @brief Constructeur avec niveau par défaut INFO
     * @param enableTimestamp activer l'affichage du timestamp (défaut: true)
     */
    explicit SerialLogger(bool enableTimestamp = true) 
        : currentLevel(LogLevel::INFO), showTimestamp(enableTimestamp) {
    }
    
    /**
     * @brief Initialise le Serial avec une vitesse donnée
     * @param baudRate vitesse du port série (défaut: 115200)
     */
    void begin(unsigned long baudRate = 115200) {
        Serial.begin(baudRate);
        while (!Serial) {
            ; // Attendre que le port série soit prêt
        }
    }
    
    // Implémentation de l'interface Logger
    void setLevel(LogLevel level) override {
        currentLevel = level;
    }
    
    LogLevel getLevel() const override {
        return currentLevel;
    }
    
    void debug(const std::string& message) override {
        log(LogLevel::DEBUG, message);
    }
    
    void info(const std::string& message) override {
        log(LogLevel::INFO, message);
    }
    
    void warn(const std::string& message) override {
        log(LogLevel::WARN, message);
    }
    
    void error(const std::string& message) override {
        log(LogLevel::ERROR, message);
    }
    
    void log(LogLevel level, const std::string& message) override {
        // Filtrer selon le niveau configuré
        if (static_cast<int>(level) < static_cast<int>(currentLevel)) {
            return;
        }
        
        printPrefix(level);
        Serial.println(message.c_str());
    }
    
    /**
     * @brief Active/désactive l'affichage du timestamp
     * @param enable true pour activer, false pour désactiver
     */
    void enableTimestamp(bool enable) {
        showTimestamp = enable;
    }
}; 