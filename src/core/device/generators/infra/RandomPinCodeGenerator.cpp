#include "RandomPinCodeGenerator.h"
#include <sstream>
#include <iomanip>

RandomPinCodeGenerator::RandomPinCodeGenerator(RandomProvider* randomProvider) 
    : randomProvider(randomProvider) {
}

std::string RandomPinCodeGenerator::generatePinCode() {
    // Générer un nombre aléatoire entre 0 et 9999
    int randomNumber = randomProvider->getRandomInt(0, 9999);
    
    // Formater en 4 chiffres avec des zéros en préfixe si nécessaire
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(4) << randomNumber;
    
    return oss.str();
}
