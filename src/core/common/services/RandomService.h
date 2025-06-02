#pragma once

/**
 * @brief Interface pour les services de génération aléatoire
 * Abstraction permettant d'injecter différentes implémentations (Arduino random(), std::random, etc.)
 */
class RandomService {
public:
    virtual ~RandomService() = default;
    
    /**
     * @brief Génère un nombre aléatoire entre min et max (exclus)
     * @param min valeur minimale (incluse)
     * @param max valeur maximale (exclue)
     * @return int nombre aléatoire
     */
    virtual int getRandomInt(int min, int max) = 0;
    
    /**
     * @brief Initialise le générateur avec un seed
     * @param seed valeur de seed
     */
    virtual void setSeed(unsigned long seed) = 0;

protected:
    RandomService() = default;
    RandomService(const RandomService&) = delete;
    RandomService& operator=(const RandomService&) = delete;
}; 