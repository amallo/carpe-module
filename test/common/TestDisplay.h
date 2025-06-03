#pragma once
#include <iostream>
#include <string>

/**
 * @brief Utilitaires pour améliorer l'affichage des tests
 * Fournit des couleurs ANSI et des formatages pour les tests Unity
 */
namespace TestDisplay {
    
    // Couleurs ANSI
    const std::string RED = "\x1b[31m";
    const std::string GREEN = "\x1b[32m";
    const std::string YELLOW = "\x1b[33m";
    const std::string BLUE = "\x1b[34m";
    const std::string MAGENTA = "\x1b[35m";
    const std::string CYAN = "\x1b[36m";
    const std::string WHITE = "\x1b[37m";
    const std::string BOLD = "\x1b[1m";
    const std::string RESET = "\x1b[0m";
    
    // Styles prédéfinis
    const std::string SUCCESS = GREEN + "✅ ";
    const std::string ERROR = RED + "❌ ";
    const std::string INFO = CYAN + "ℹ️  ";
    const std::string TEST = YELLOW + "🧪 ";
    const std::string DEBUG = BLUE + "🔍 ";
    const std::string WARNING = YELLOW + "⚠️  ";
    
    /**
     * @brief Affiche un message avec une couleur et un style
     */
    inline void print(const std::string& style, const std::string& message) {
        std::cout << style << message << RESET << std::endl;
    }
    
    /**
     * @brief Affiche un titre de section encadré
     */
    inline void printSectionTitle(const std::string& title) {
        std::string border = std::string(title.length() + 4, '=');
        std::cout << MAGENTA << BOLD << border << RESET << std::endl;
        std::cout << MAGENTA << BOLD << "  " << title << "  " << RESET << std::endl;
        std::cout << MAGENTA << BOLD << border << RESET << std::endl;
    }
    
    /**
     * @brief Affiche un résumé des tests
     */
    inline void printTestSummary(int total, int passed, int failed) {
        std::cout << std::endl;
        std::cout << BOLD << "📊 RÉSUMÉ DES TESTS:" << RESET << std::endl;
        std::cout << "  Total: " << CYAN << total << RESET << " tests" << std::endl;
        
        if (passed > 0) {
            std::cout << "  " << SUCCESS << passed << " tests réussis" << RESET << std::endl;
        }
        
        if (failed > 0) {
            std::cout << "  " << ERROR << failed << " tests échoués" << RESET << std::endl;
        }
        
        if (failed == 0) {
            print(SUCCESS, "🎉 TOUS LES TESTS SONT PASSÉS !");
        } else {
            print(ERROR, "💥 CERTAINS TESTS ONT ÉCHOUÉ");
        }
        std::cout << std::endl;
    }
    
    /**
     * @brief Affiche une barre de progression simple
     */
    inline void printProgressBar(int current, int total, const std::string& message = "") {
        float progress = static_cast<float>(current) / total;
        int barWidth = 30;
        int pos = static_cast<int>(barWidth * progress);
        
        std::cout << "\r[";
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) std::cout << GREEN << "█" << RESET;
            else if (i == pos) std::cout << YELLOW << "▶" << RESET;
            else std::cout << " ";
        }
        std::cout << "] " << int(progress * 100.0) << "% ";
        if (!message.empty()) {
            std::cout << message;
        }
        std::cout.flush();
    }
} 