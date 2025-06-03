#include <test/common/services/MockRandomService.h>

MockRandomService::MockRandomService() 
    : randomIntReturnManager(42)  // Valeur par défaut aléatoire mais prévisible
    , seedReturnManager(true)      // setSeed réussit par défaut
    , lastMinValue(0)
    , lastMaxValue(0)
    , lastSeedValue(0)
    , lastRandomIntResult(42)
{
}

// === Implémentation de l'interface RandomService ===

int MockRandomService::getRandomInt(int min, int max) {
    lastMinValue = min;
    lastMaxValue = max;
    getRandomIntCallTracker.recordCall();
    
    lastRandomIntResult = randomIntReturnManager.getNextValue();
    return lastRandomIntResult;
}

void MockRandomService::setSeed(unsigned long seed) {
    lastSeedValue = seed;
    setSeedCallTracker.recordCall();
    
    // Pour setSeed, on peut juste enregistrer l'appel
    // Le comportement réel dépend de l'implémentation
    seedReturnManager.getNextValue();  // Consomme la valeur programmée si besoin
}

// === Configuration des comportements de mock ===

void MockRandomService::setRandomIntDefaultResult(int value) {
    randomIntReturnManager.setDefaultValue(value);
}

void MockRandomService::scheduleRandomIntResult(int value) {
    randomIntReturnManager.scheduleValue(value);
}

void MockRandomService::scheduleRandomIntResults(const std::vector<int>& values) {
    randomIntReturnManager.scheduleValues(values);
}

void MockRandomService::setSeedDefaultSuccess(bool success) {
    seedReturnManager.setDefaultValue(success);
}

void MockRandomService::scheduleSeedResult(bool success) {
    seedReturnManager.scheduleValue(success);
}

// === Vérifications des appels (Spy behavior) ===

bool MockRandomService::wasGetRandomIntCalled() const {
    return getRandomIntCallTracker.wasCalled();
}

int MockRandomService::getGetRandomIntCallCount() const {
    return getRandomIntCallTracker.getCallCount();
}

int MockRandomService::getLastMinValue() const {
    return lastMinValue;
}

int MockRandomService::getLastMaxValue() const {
    return lastMaxValue;
}

bool MockRandomService::wasSetSeedCalled() const {
    return setSeedCallTracker.wasCalled();
}

int MockRandomService::getSetSeedCallCount() const {
    return setSeedCallTracker.getCallCount();
}

unsigned long MockRandomService::getLastSeedValue() const {
    return lastSeedValue;
}

// === Contrôle du mock ===

void MockRandomService::reset() {
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

void MockRandomService::resetCallTrackers() {
    getRandomIntCallTracker.reset();
    setSeedCallTracker.reset();
}

void MockRandomService::clearScheduledResults() {
    randomIntReturnManager.clearScheduledValues();
    seedReturnManager.clearScheduledValues();
}

// === Accès aux derniers paramètres (pour debug) ===

int MockRandomService::getLastRandomIntResult() const {
    return lastRandomIntResult;
} 