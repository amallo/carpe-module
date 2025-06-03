#pragma once

#include <core/device/DeviceIdGenerator.h>
#include <test/common/MockFramework.h>

/**
 * @brief Test Double (Mock) de DeviceIdGenerator pour tests unitaires
 * Permet de contrôler les IDs de device générés pour des tests prévisibles
 * Utilise MockResult et ReturnValueManager pour des comportements configurables
 * Suit les principes de Clean Architecture avec Dependency Inversion
 */
class MockDeviceIdGenerator : public DeviceIdGenerator {
public:
    MockDeviceIdGenerator();

    // Implémentation de l'interface DeviceIdGenerator
    std::string generate() override;

    // === Configuration des comportements de mock ===
    
    // Configuration des résultats pour generate()
    void setGenerateDefaultResult(const std::string& deviceId);
    void scheduleGenerateResult(const std::string& deviceId);
    void scheduleGenerateSuccess(const std::string& deviceId);
    void scheduleGenerateFailure(const std::string& error);
    void scheduleGenerateResults(const std::vector<StringResult>& results);
    
    // === Vérifications des appels (Spy behavior) ===
    
    // Vérifications generate()
    bool wasGenerateCalled() const;
    int getGenerateCallCount() const;

    // === Contrôle du mock ===
    void reset();                    // Remet à zéro toutes les valeurs et call trackers
    void resetCallTrackers();        // Remet à zéro seulement les call trackers
    void clearScheduledResults();    // Vide les résultats programmés

    // === Accès aux derniers résultats (pour debug) ===
    StringResult getLastGenerateResult() const;
    std::string getLastGeneratedDeviceId() const;

private:
    // Gestionnaire de retour
    StringReturnManager generateReturnManager;
    
    // Traqueur d'appels
    CallTracker generateCallTracker;
    
    // Derniers résultats (pour debug)
    mutable StringResult lastGenerateResult;
}; 