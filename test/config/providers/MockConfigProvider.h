#pragma once

#include <string>
#include <core/config/providers/ConfigProvider.h>
#include <test/common/MockFramework.h>

/**
 * @brief Test Double (Mock) de ConfigProvider pour tests unitaires
 * Stocke la configuration en mémoire (pas de persistance)
 * Utilise MockResult et ReturnValueManager pour des comportements configurables
 * Suit les principes de Clean Architecture avec Dependency Inversion
 */
class MockConfigProvider : public ConfigProvider {
public:
    MockConfigProvider();

    // Implémentation de l'interface ConfigProvider
    std::string getDeviceId() override;
    void setDeviceId(const std::string& id) override;
    void setPinCode(const std::string& pinCode) override;
    std::string getPinCode() override;
    
    // Méthodes supplémentaires pour les tests
    bool loadConfig();    
    bool saveConfig();    
    void printConfig();

    // === Configuration des comportements de mock ===
    
    // Configuration des résultats pour loadConfig()
    void setLoadDefaultResult(bool success, const std::string& error = "");
    void scheduleLoadResult(bool success, const std::string& error = "");
    void scheduleLoadSuccess();
    void scheduleLoadFailure(const std::string& error);
    void scheduleLoadResults(const std::vector<BoolResult>& results);
    
    // Configuration des résultats pour saveConfig()
    void setSaveDefaultResult(bool success, const std::string& error = "");
    void scheduleSaveResult(bool success, const std::string& error = "");
    void scheduleSaveSuccess();
    void scheduleSaveFailure(const std::string& error);
    void scheduleSaveResults(const std::vector<BoolResult>& results);
    
    // Configuration des résultats pour getDeviceId()
    void setDeviceIdDefaultResult(const std::string& deviceId);
    void scheduleDeviceIdResult(const std::string& deviceId);
    
    // Configuration des résultats pour getPinCode()
    void setPinCodeDefaultResult(const std::string& pinCode);
    void schedulePinCodeResult(const std::string& pinCode);

    // === Vérifications des appels (Spy behavior) ===
    
    // Vérifications loadConfig()
    bool wasLoadCalled() const;
    int getLoadCallCount() const;
    
    // Vérifications saveConfig()
    bool wasSaveCalled() const;
    int getSaveCallCount() const;
    
    // Vérifications getDeviceId()
    bool wasGetDeviceIdCalled() const;
    int getGetDeviceIdCallCount() const;
    
    // Vérifications setDeviceId()
    bool wasSetDeviceIdCalled() const;
    int getSetDeviceIdCallCount() const;
    std::string getLastSetDeviceId() const;
    
    // Vérifications getPinCode()
    bool wasGetPinCodeCalled() const;
    int getGetPinCodeCallCount() const;
    
    // Vérifications setPinCode()
    bool wasSetPinCodeCalled() const;
    int getSetPinCodeCallCount() const;
    std::string getLastPinCode() const;

    // === Contrôle du mock ===
    void reset();                    // Remet à zéro toutes les valeurs et call trackers
    void resetCallTrackers();        // Remet à zéro seulement les call trackers
    void clearScheduledResults();    // Vide les résultats programmés

    // === Accès aux derniers résultats (pour debug) ===
    BoolResult getLastLoadResult() const;
    BoolResult getLastSaveResult() const;

private:
    // Stockage en mémoire
    std::string deviceId;
    std::string pinCode;
    
    // Gestionnaires de retour
    BoolReturnManager loadReturnManager;
    BoolReturnManager saveReturnManager;
    StringReturnManager deviceIdReturnManager;
    StringReturnManager pinCodeReturnManager;
    
    // Traqueurs d'appels
    CallTracker loadCallTracker;
    CallTracker saveCallTracker;
    CallTracker getDeviceIdCallTracker;
    CallTracker setDeviceIdCallTracker;
    CallTracker getPinCodeCallTracker;
    CallTracker setPinCodeCallTracker;
    
    // Derniers résultats (pour debug)
    mutable BoolResult lastLoadResult;
    mutable BoolResult lastSaveResult;
    
    // Dernière valeur setDeviceId
    std::string lastSetDeviceIdValue;
}; 