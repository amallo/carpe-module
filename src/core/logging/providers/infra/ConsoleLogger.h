#pragma once
#include <core/logging/Logger.h>
#include <iostream>
#include <chrono>

/**
 * @brief Implémentation de Logger utilisant std::cout
 * Pour les tests natifs et environnements non-Arduino
 * Affiche les logs sur la console standard avec préfixes et horodatage
 */
class ConsoleLogger : public Logger {
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
     * @brief Retourne le timestamp actuel en millisecondes
     * @return unsigned long timestamp
     */
    unsigned long getCurrentTimestamp() const {
        auto now = std::chrono::steady_clock::now();
        auto duration = now.time_since_epoch();
        return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    }
    
    /**
     * @brief Affiche le préfixe du log (timestamp + niveau)
     * @param level niveau du message
     */
    void printPrefix(LogLevel level) const {
        if (showTimestamp) {
            std::cout << "[" << getCurrentTimestamp() << "] ";
        }
        std::cout << "[" << levelToString(level) << "] ";
    }

public:
    /**
     * @brief Constructeur avec niveau par défaut INFO
     * @param enableTimestamp activer l'affichage du timestamp (défaut: true)
     */
    explicit ConsoleLogger(bool enableTimestamp = true) 
        : currentLevel(LogLevel::INFO), showTimestamp(enableTimestamp) {
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
        std::cout << message << std::endl;
    }
    
    /**
     * @brief Active/désactive l'affichage du timestamp
     * @param enable true pour activer, false pour désactiver
     */
    void enableTimestamp(bool enable) {
        showTimestamp = enable;
    }
}; 