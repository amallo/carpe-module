#include <test/core/device/generators/MockDeviceIdGenerator.h>

MockDeviceIdGenerator::MockDeviceIdGenerator() 
    : generateReturnManager()
    , lastGenerateResult("carpe-MOCK123", true, "")  // Valeur par défaut prévisible
{
    // Configuration par défaut : génère toujours "carpe-MOCK123"
    generateReturnManager.setDefaultResult(StringResult::createSuccess("carpe-MOCK123"));
}

// === Implémentation de l'interface DeviceIdGenerator ===

std::string MockDeviceIdGenerator::generate() {
    generateCallTracker.recordCall();
    
    lastGenerateResult = generateReturnManager.getNextResult();
    
    // Si le résultat est un échec, on peut soit retourner une chaîne vide
    // soit lever une exception selon le comportement souhaité
    if (!lastGenerateResult.success) {
        // Pour simplifier, on retourne une chaîne vide en cas d'échec
        return "";
    }
    
    return lastGenerateResult.value;
}

// === Configuration des comportements de mock ===

void MockDeviceIdGenerator::setGenerateDefaultResult(const std::string& deviceId) {
    generateReturnManager.setDefaultResult(StringResult::createSuccess(deviceId));
}

void MockDeviceIdGenerator::scheduleGenerateResult(const std::string& deviceId) {
    generateReturnManager.scheduleResult(StringResult::createSuccess(deviceId));
}

void MockDeviceIdGenerator::scheduleGenerateSuccess(const std::string& deviceId) {
    generateReturnManager.scheduleSuccess(deviceId);
}

void MockDeviceIdGenerator::scheduleGenerateFailure(const std::string& error) {
    generateReturnManager.scheduleFailure(error);
}

void MockDeviceIdGenerator::scheduleGenerateResults(const std::vector<StringResult>& results) {
    generateReturnManager.scheduleResults(results);
}

// === Vérifications des appels (Spy behavior) ===

bool MockDeviceIdGenerator::wasGenerateCalled() const {
    return generateCallTracker.wasMethodCalled();
}

int MockDeviceIdGenerator::getGenerateCallCount() const {
    return generateCallTracker.getCallCount();
}

// === Contrôle du mock ===

void MockDeviceIdGenerator::reset() {
    resetCallTrackers();
    clearScheduledResults();
    
    // Reset des valeurs par défaut
    generateReturnManager.setDefaultResult(StringResult::createSuccess("carpe-MOCK123"));
    
    // Reset des derniers résultats
    lastGenerateResult = StringResult("carpe-MOCK123", true, "");
}

void MockDeviceIdGenerator::resetCallTrackers() {
    generateCallTracker.reset();
}

void MockDeviceIdGenerator::clearScheduledResults() {
    generateReturnManager.clearScheduled();
}

// === Accès aux derniers résultats (pour debug) ===

StringResult MockDeviceIdGenerator::getLastGenerateResult() const {
    return lastGenerateResult;
}

std::string MockDeviceIdGenerator::getLastGeneratedDeviceId() const {
    return lastGenerateResult.value;
} 