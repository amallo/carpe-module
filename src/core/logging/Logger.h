#pragma once
#include <string>

/**
 * @brief Niveaux de logging disponibles
 */
enum class LogLevel {
    DEBUG = 0,
    INFO = 1,
    WARN = 2,
    ERROR = 3
};

/**
 * @brief Interface pour les services de logging
 * Abstraction permettant d'injecter différentes implémentations (Serial, File, Network, etc.)
 * Suit les principes de Clean Architecture avec Dependency Inversion
 */
class Logger {
public:
    virtual ~Logger() = default;
    
    /**
     * @brief Configure le niveau minimum de logging
     * @param level niveau minimum (messages en dessous ignorés)
     */
    virtual void setLevel(LogLevel level) = 0;
    
    /**
     * @brief Retourne le niveau de logging actuel
     * @return LogLevel niveau actuel
     */
    virtual LogLevel getLevel() const = 0;
    
    /**
     * @brief Log un message de debug
     * @param message le message à logger
     */
    virtual void debug(const std::string& message) = 0;
    
    /**
     * @brief Log un message d'information
     * @param message le message à logger
     */
    virtual void info(const std::string& message) = 0;
    
    /**
     * @brief Log un message d'avertissement
     * @param message le message à logger
     */
    virtual void warn(const std::string& message) = 0;
    
    /**
     * @brief Log un message d'erreur
     * @param message le message à logger
     */
    virtual void error(const std::string& message) = 0;
    
    /**
     * @brief Log un message avec un niveau spécifique
     * @param level niveau du message
     * @param message le message à logger
     */
    virtual void log(LogLevel level, const std::string& message) = 0;

protected:
    Logger() = default;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
}; 