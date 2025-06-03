#include <test/common/providers/MockRandomProvider.h>

MockRandomProvider::MockRandomProvider() 
    : randomIntReturnManager(42)  // Valeur par défaut aléatoire mais prévisible
    , seedReturnManager(true)      // setSeed réussit par défaut
    , lastMinValue(0)
    , lastMaxValue(0)
    , lastSeedValue(0)
    , lastRandomIntResult(42)
{
}

// === Implémentation de l'interface RandomService ===

int MockRandomProvider::getRandomInt(int min, int max) {
    lastMinValue = min;
    lastMaxValue = max;
    getRandomIntCallTracker.recordCall();
    
    lastRandomIntResult = randomIntReturnManager.getNextValue();
    return lastRandomIntResult;
}

void MockRandomProvider::setSeed(unsigned long seed) {
    lastSeedValue = seed;
    setSeedCallTracker.recordCall();
    
    // Pour setSeed, on peut juste enregistrer l'appel
    // Le comportement réel dépend de l'implémentation
    seedReturnManager.getNextValue();  // Consomme la valeur programmée si besoin
}

// === Configuration des comportements de mock ===

void MockRandomProvider::setRandomIntDefaultResult(int value) {
    randomIntReturnManager.setDefaultValue(value);
}

void MockRandomProvider::scheduleRandomIntResult(int value) {
    randomIntReturnManager.scheduleValue(value);
}

void MockRandomProvider::scheduleRandomIntResults(const std::vector<int>& values) {
    randomIntReturnManager.scheduleValues(values);
}

void MockRandomProvider::setSeedDefaultSuccess(bool success) {
    seedReturnManager.setDefaultValue(success);
}

void MockRandomProvider::scheduleSeedResult(bool success) {
    seedReturnManager.scheduleValue(success);
}

// === Vérifications des appels (Spy behavior) ===

bool MockRandomProvider::wasGetRandomIntCalled() const {
    return getRandomIntCallTracker.wasCalled();
}

int MockRandomProvider::getGetRandomIntCallCount() const {
    return getRandomIntCallTracker.getCallCount();
}

int MockRandomProvider::getLastMinValue() const {
    return lastMinValue;
}

int MockRandomProvider::getLastMaxValue() const {
    return lastMaxValue;
}

bool MockRandomProvider::wasSetSeedCalled() const {
    return setSeedCallTracker.wasCalled();
}

int MockRandomProvider::getSetSeedCallCount() const {
    return setSeedCallTracker.getCallCount();
}

unsigned long MockRandomProvider::getLastSeedValue() const {
    return lastSeedValue;
}

// === Contrôle du mock ===

void MockRandomProvider::reset() {
    resetCallTrackers();
    clearScheduledResults();
    
    // Reset des valeurs par défaut
    randomIntReturnManager.setDefaultValue(42);
    seedReturnManager.setDefaultValue(true);
    
    // Reset des derniers paramètres
    lastMinValue = 0;
    lastMaxValue = 0;
    lastSeedValue = 0;
    lastRandomIntResult = 42;
}

void MockRandomProvider::resetCallTrackers() {
    getRandomIntCallTracker.reset();
    setSeedCallTracker.reset();
}

void MockRandomProvider::clearScheduledResults() {
    randomIntReturnManager.clearScheduledValues();
    seedReturnManager.clearScheduledValues();
}

// === Accès aux derniers paramètres (pour debug) ===

int MockRandomProvider::getLastRandomIntResult() const {
    return lastRandomIntResult;
} 