#pragma once

#include <core/common/services/RandomProvider.h>
#include <test/common/MockFramework.h>

/**
 * @brief Test Double (Mock) de RandomService pour tests unitaires
 * Permet de contrôler les valeurs aléatoires retournées pour des tests prévisibles
 * Utilise MockResult et ReturnValueManager pour des comportements configurables
 * Suit les principes de Clean Architecture avec Dependency Inversion
 */
class MockRandomProvider : public RandomProvider {
public:
    MockRandomProvider();

    // Implémentation de l'interface RandomService
    int getRandomInt(int min, int max) override;
    void setSeed(unsigned long seed) override;

    // === Configuration des comportements de mock ===
    
    // Configuration des résultats pour getRandomInt()
    void setRandomIntDefaultResult(int value);
    void scheduleRandomIntResult(int value);
    void scheduleRandomIntResults(const std::vector<int>& values);
    
    // Configuration pour setSeed()
    void setSeedDefaultSuccess(bool success = true);
    void scheduleSeedResult(bool success);
    
    // === Vérifications des appels (Spy behavior) ===
    
    // Vérifications getRandomInt()
    bool wasGetRandomIntCalled() const;
    int getGetRandomIntCallCount() const;
    int getLastMinValue() const;
    int getLastMaxValue() const;
    
    // Vérifications setSeed()
    bool wasSetSeedCalled() const;
    int getSetSeedCallCount() const;
    unsigned long getLastSeedValue() const;

    // === Contrôle du mock ===
    void reset();                    // Remet à zéro toutes les valeurs et call trackers
    void resetCallTrackers();        // Remet à zéro seulement les call trackers
    void clearScheduledResults();    // Vide les résultats programmés

    // === Accès aux derniers paramètres (pour debug) ===
    int getLastRandomIntResult() const;

private:
    // Gestionnaires de retour
    IntReturnManager randomIntReturnManager;
    BoolReturnManager seedReturnManager;
    
    // Traqueurs d'appels
    CallTracker getRandomIntCallTracker;
    CallTracker setSeedCallTracker;
    
    // Derniers paramètres d'appel
    mutable int lastMinValue;
    mutable int lastMaxValue;
    mutable unsigned long lastSeedValue;
    
    // Derniers résultats (pour debug)
    mutable int lastRandomIntResult;
}; 