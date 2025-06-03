#pragma once

#include <string>
#include <queue>
#include <vector>
#include <functional>

/**
 * @brief Structure générique pour les résultats de mock
 * Permet de simuler succès, échecs et valeurs de retour
 */
template<typename T>
struct MockResult {
    T value;
    bool success;
    std::string errorMessage;
    
    MockResult() : value{}, success(true), errorMessage("") {}
    MockResult(const T& val) : value(val), success(true), errorMessage("") {}
    MockResult(const T& val, bool succ, const std::string& err = "") 
        : value(val), success(succ), errorMessage(err) {}
    
    // Constructeur pour échec uniquement
    static MockResult<T> createFailure(const std::string& error) {
        return MockResult<T>(T{}, false, error);
    }
    
    // Constructeur pour succès uniquement
    static MockResult<T> createSuccess(const T& val) {
        return MockResult<T>(val, true, "");
    }
};

/**
 * @brief Gestionnaire des valeurs de retour pour les mocks
 * Permet de configurer les résultats de façon séquentielle
 */
template<typename T>
class ReturnValueManager {
public:
    ReturnValueManager() : defaultResult(T{}, true, "") {}
    
    // Configure la valeur par défaut
    void setDefaultResult(const MockResult<T>& result) {
        defaultResult = result;
    }
    
    // Programme un résultat pour le prochain appel
    void scheduleResult(const MockResult<T>& result) {
        scheduledResults.push(result);
    }
    
    // Programme plusieurs résultats
    void scheduleResults(const std::vector<MockResult<T>>& results) {
        for (const auto& result : results) {
            scheduledResults.push(result);
        }
    }
    
    // Récupère le prochain résultat
    MockResult<T> getNextResult() {
        if (!scheduledResults.empty()) {
            MockResult<T> result = scheduledResults.front();
            scheduledResults.pop();
            return result;
        }
        return defaultResult;
    }
    
    // Vide la queue des résultats programmés
    void clearScheduled() {
        std::queue<MockResult<T>> empty;
        scheduledResults.swap(empty);
    }
    
    // Méthodes de commodité
    void scheduleSuccess(const T& value) {
        scheduleResult(MockResult<T>::createSuccess(value));
    }
    
    void scheduleFailure(const std::string& error) {
        scheduleResult(MockResult<T>::createFailure(error));
    }

private:
    std::queue<MockResult<T>> scheduledResults;
    MockResult<T> defaultResult;
};

/**
 * @brief Traqueur d'appels pour les méthodes de mock
 * Enregistre les appels et leurs paramètres
 */
class CallTracker {
public:
    CallTracker() : callCount(0), wasCalled(false) {}
    
    // Enregistre un appel
    void recordCall() {
        wasCalled = true;
        callCount++;
    }
    
    // Enregistre un appel avec paramètres
    template<typename... Args>
    void recordCall(Args&&...) {
        recordCall();
        // On pourrait stocker les paramètres si nécessaire
    }
    
    // Getters
    bool wasMethodCalled() const { return wasCalled; }
    int getCallCount() const { return callCount; }
    
    // Reset
    void reset() {
        wasCalled = false;
        callCount = 0;
    }

private:
    int callCount;
    bool wasCalled;
};

/**
 * @brief Spécialisation pour les méthodes qui retournent bool
 */
using BoolResult = MockResult<bool>;
using BoolReturnManager = ReturnValueManager<bool>;

/**
 * @brief Spécialisation pour les méthodes qui retournent string
 */
using StringResult = MockResult<std::string>;
using StringReturnManager = ReturnValueManager<std::string>; 