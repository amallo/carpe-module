#include "MockConfigProvider.h"
#include <iostream>

MockConfigProvider::MockConfigProvider() 
    : deviceId(""), pinCode(""), lastSetDeviceIdValue("") {
    // Initialise les valeurs par défaut
    loadReturnManager.setDefaultResult(BoolResult::createSuccess(true));
    saveReturnManager.setDefaultResult(BoolResult::createSuccess(true));
    deviceIdReturnManager.setDefaultResult(StringResult::createSuccess(""));
    pinCodeReturnManager.setDefaultResult(StringResult::createSuccess(""));
}

bool MockConfigProvider::loadConfig() {
    loadCallTracker.recordCall();
    lastLoadResult = loadReturnManager.getNextResult();
    return lastLoadResult.success;
}

bool MockConfigProvider::saveConfig() {
    saveCallTracker.recordCall();
    lastSaveResult = saveReturnManager.getNextResult();
    return lastSaveResult.success;
}

std::string MockConfigProvider::getDeviceId() {
    getDeviceIdCallTracker.recordCall();
    
    // Si deviceId a été explicitement set, retourne ça
    if (!deviceId.empty()) {
        return deviceId;
    }
    
    // Sinon utilise le return manager pour des comportements configurés
    auto result = deviceIdReturnManager.getNextResult();
    return result.value;
}

void MockConfigProvider::setDeviceId(const std::string& id) {
    setDeviceIdCallTracker.recordCall();
    deviceId = id;
    lastSetDeviceIdValue = id;
}

void MockConfigProvider::setPinCode(const std::string& pin) {
    setPinCodeCallTracker.recordCall();
    pinCode = pin;
}

std::string MockConfigProvider::getPinCode() {
    getPinCodeCallTracker.recordCall();
    
    // Si pinCode a été explicitement set, retourne ça
    if (!pinCode.empty()) {
        return pinCode;
    }
    
    // Sinon utilise le return manager pour des comportements configurés
    auto result = pinCodeReturnManager.getNextResult();
    return result.value;
}

void MockConfigProvider::printConfig() {
#ifdef NATIVE_BUILD
    // Version native pour tests - utilise std::cout
    std::cout << "[Mock Config]" << std::endl;
    std::cout << "Device ID: " << deviceId << std::endl;
    std::cout << "Load called: " << wasLoadCalled() << " times: " << getLoadCallCount() << std::endl;
    std::cout << "Save called: " << wasSaveCalled() << " times: " << getSaveCallCount() << std::endl;
    if (!lastLoadResult.errorMessage.empty()) {
        std::cout << "Last load error: " << lastLoadResult.errorMessage << std::endl;
    }
    if (!lastSaveResult.errorMessage.empty()) {
        std::cout << "Last save error: " << lastSaveResult.errorMessage << std::endl;
    }
#else
    // Version Arduino - utilise Serial (pour compatibilité)
    Serial.println("[Mock Config]");
    Serial.print("Device ID: ");
    Serial.println(deviceId.c_str());
    Serial.print("Load called: ");
    Serial.print(wasLoadCalled() ? "true" : "false");
    Serial.print(" times: ");
    Serial.println(getLoadCallCount());
    Serial.print("Save called: ");
    Serial.print(wasSaveCalled() ? "true" : "false");
    Serial.print(" times: ");
    Serial.println(getSaveCallCount());
#endif
}

// === Configuration des comportements de mock ===

// Configuration loadConfig()
void MockConfigProvider::setLoadDefaultResult(bool success, const std::string& error) {
    loadReturnManager.setDefaultResult(BoolResult(success, success, error));
}

void MockConfigProvider::scheduleLoadResult(bool success, const std::string& error) {
    loadReturnManager.scheduleResult(BoolResult(success, success, error));
}

void MockConfigProvider::scheduleLoadSuccess() {
    loadReturnManager.scheduleSuccess(true);
}

void MockConfigProvider::scheduleLoadFailure(const std::string& error) {
    loadReturnManager.scheduleFailure(error);
}

void MockConfigProvider::scheduleLoadResults(const std::vector<BoolResult>& results) {
    loadReturnManager.scheduleResults(results);
}

// Configuration saveConfig()
void MockConfigProvider::setSaveDefaultResult(bool success, const std::string& error) {
    saveReturnManager.setDefaultResult(BoolResult(success, success, error));
}

void MockConfigProvider::scheduleSaveResult(bool success, const std::string& error) {
    saveReturnManager.scheduleResult(BoolResult(success, success, error));
}

void MockConfigProvider::scheduleSaveSuccess() {
    saveReturnManager.scheduleSuccess(true);
}

void MockConfigProvider::scheduleSaveFailure(const std::string& error) {
    saveReturnManager.scheduleFailure(error);
}

void MockConfigProvider::scheduleSaveResults(const std::vector<BoolResult>& results) {
    saveReturnManager.scheduleResults(results);
}

// Configuration getDeviceId()
void MockConfigProvider::setDeviceIdDefaultResult(const std::string& deviceIdValue) {
    deviceIdReturnManager.setDefaultResult(StringResult::createSuccess(deviceIdValue));
}

void MockConfigProvider::scheduleDeviceIdResult(const std::string& deviceIdValue) {
    deviceIdReturnManager.scheduleResult(StringResult::createSuccess(deviceIdValue));
}

// Configuration getPinCode()
void MockConfigProvider::setPinCodeDefaultResult(const std::string& pinCodeValue) {
    pinCodeReturnManager.setDefaultResult(StringResult::createSuccess(pinCodeValue));
}

void MockConfigProvider::schedulePinCodeResult(const std::string& pinCodeValue) {
    pinCodeReturnManager.scheduleResult(StringResult::createSuccess(pinCodeValue));
}

// === Vérifications des appels (Spy behavior) ===

bool MockConfigProvider::wasLoadCalled() const {
    return loadCallTracker.wasMethodCalled();
}

int MockConfigProvider::getLoadCallCount() const {
    return loadCallTracker.getCallCount();
}

bool MockConfigProvider::wasSaveCalled() const {
    return saveCallTracker.wasMethodCalled();
}

int MockConfigProvider::getSaveCallCount() const {
    return saveCallTracker.getCallCount();
}

bool MockConfigProvider::wasGetDeviceIdCalled() const {
    return getDeviceIdCallTracker.wasMethodCalled();
}

int MockConfigProvider::getGetDeviceIdCallCount() const {
    return getDeviceIdCallTracker.getCallCount();
}

bool MockConfigProvider::wasSetDeviceIdCalled() const {
    return setDeviceIdCallTracker.wasMethodCalled();
}

int MockConfigProvider::getSetDeviceIdCallCount() const {
    return setDeviceIdCallTracker.getCallCount();
}

std::string MockConfigProvider::getLastSetDeviceId() const {
    return lastSetDeviceIdValue;
}

bool MockConfigProvider::wasGetPinCodeCalled() const {
    return getPinCodeCallTracker.wasMethodCalled();
}

int MockConfigProvider::getGetPinCodeCallCount() const {
    return getPinCodeCallTracker.getCallCount();
}

bool MockConfigProvider::wasSetPinCodeCalled() const {
    return setPinCodeCallTracker.wasMethodCalled();
}

int MockConfigProvider::getSetPinCodeCallCount() const {
    return setPinCodeCallTracker.getCallCount();
}

std::string MockConfigProvider::getLastPinCode() const {
    return pinCode;
}

// === Contrôle du mock ===

void MockConfigProvider::reset() {
    deviceId = "";
    pinCode = "";
    lastSetDeviceIdValue = "";
    resetCallTrackers();
    clearScheduledResults();
    lastLoadResult = BoolResult();
    lastSaveResult = BoolResult();
}

void MockConfigProvider::resetCallTrackers() {
    loadCallTracker.reset();
    saveCallTracker.reset();
    getDeviceIdCallTracker.reset();
    setDeviceIdCallTracker.reset();
    getPinCodeCallTracker.reset();
    setPinCodeCallTracker.reset();
}

void MockConfigProvider::clearScheduledResults() {
    loadReturnManager.clearScheduled();
    saveReturnManager.clearScheduled();
    deviceIdReturnManager.clearScheduled();
    pinCodeReturnManager.clearScheduled();
}

// === Accès aux derniers résultats (pour debug) ===

BoolResult MockConfigProvider::getLastLoadResult() const {
    return lastLoadResult;
}

BoolResult MockConfigProvider::getLastSaveResult() const {
    return lastSaveResult;
} 