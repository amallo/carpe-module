# Tests Natifs CARPE MODULE

🧪 **Architecture de tests Clean avec injection de dépendances sur desktop**

## 🎯 Objectifs

Ce projet démontre comment tester la logique métier d'un projet ESP32 en utilisant l'injection de dépendances pour exécuter les tests directement sur votre machine de développement, sans hardware.

### Avantages des tests natifs

- ⚡ **Performance** : Tests 10-100x plus rapides que sur ESP32
- 🔄 **Feedback rapide** : Cycle de développement accéléré 
- 🏗️ **Architecture propre** : Force une séparation claire des responsabilités
- 🎯 **Tests isolés** : Chaque composant testé indépendamment
- 🔧 **Debugging facile** : Tous vos outils de debug desktop disponibles

## 🏗️ Architecture

### Clean Architecture avec injection de dépendances

```
┌─────────────────────────────────────────────────────────────┐
│                    Tests Natifs                             │
├─────────────────────────────────────────────────────────────┤
│  MockRandomService  │  MockTimeService  │ Test Framework    │
├─────────────────────┼───────────────────┼───────────────────┤
│      Interfaces     │                   │                   │
│  RandomService      │   TimeService     │  DeviceIdGenerator│
├─────────────────────┼───────────────────┼───────────────────┤
│  Implémentations    │                   │                   │
│  NativeRandom       │   NativeTime      │ RandomDeviceId    │
│  ArduinoRandom      │   ArduinoTime     │ MacAddressId      │
├─────────────────────┼───────────────────┼───────────────────┤
│                   Hardware Layer                            │
│            ESP32 Arduino / Desktop                          │
└─────────────────────────────────────────────────────────────┘
```

## 🔧 Technologies

- **Framework de test** : Unity (portable C/C++)
- **Mock Framework** : Framework custom léger
- **Build System** : Makefile + Unity GitHub
- **Architecture** : Clean Architecture, SOLID principles
- **Compilation** : g++ std=c++17

## 🚀 Exécution des tests

### Option 1 : Script tout-en-un (recommandé)

```bash
# Exécuter les tests
./run_native_tests.sh

# Autres options
./run_native_tests.sh clean      # Nettoyer
./run_native_tests.sh rebuild    # Reconstruire tout
./run_native_tests.sh help       # Aide
```

### Option 2 : Makefile direct

```bash
# Compiler et exécuter
make test

# Nettoyer
make clean

# Nettoyer Unity aussi
make distclean
```

## 📁 Structure du projet

```
carpe-module/
├── src/core/
│   ├── device/generators/           # Générateurs d'ID
│   │   └── RandomDeviceIdGenerator.*
│   └── services/                    # Interfaces de services
│       ├── RandomService.h          # Interface random
│       ├── TimeService.h            # Interface temps
│       └── native/                  # Implémentations natives
│           ├── NativeRandomService.h
│           └── NativeTimeService.h
├── test/
│   ├── mocks/                       # Framework de mocks
│   │   ├── MockFramework.h          # Framework de base
│   │   ├── MockRandomService.h      # Mock du random
│   │   └── MockTimeService.h        # Mock du temps
│   ├── test_framework.h             # Extensions Unity
│   ├── test_main_native.cpp         # Point d'entrée tests
│   └── test_random_device_id_generator_native.cpp
├── Makefile                         # Build natif
├── run_native_tests.sh             # Script d'exécution
└── unity/                          # Framework Unity (auto-téléchargé)
```

## 🧪 Tests implémentés

### RandomDeviceIdGenerator (5 tests)

1. **Format correct** : Vérifie le format "carpe-XXXXXX"
2. **Unicité** : Different seeds → IDs différents  
3. **Déterminisme** : Même seed → même ID
4. **Injection de dépendances** : Services correctement appelés
5. **Validité caractères** : Seulement 0-9, A-Z

### Exemple de test avec mocks

```cpp
void test_deterministic_behavior() {
    // ARRANGE - Programmer des valeurs déterministes
    std::vector<int> values = {0, 35, 18, 7, 14, 31}; // "0ZI7EV"
    mockRandom->setNextRandomValues(values);
    
    // ACT
    std::string id1 = generator->generate();
    
    // ASSERT
    TEST_ASSERT_EQUAL_STDSTRING("carpe-0ZI7EV", id1);
    TEST_ASSERT_TRUE(mockRandom->was_set_seed_called());
    TEST_ASSERT_TRUE(mockTime->was_get_micros_called());
}
```

## 🎭 Framework de Mocks

### MockRandomService

- ✅ Valeurs déterministes programmables
- ✅ Tracking des appels de méthodes  
- ✅ Vérification des paramètres
- ✅ Reset entre tests

### MockTimeService

- ✅ Temps contrôlable manuellement
- ✅ Simulation d'avancement du temps
- ✅ Tracking des appels delay()

### CallTracker<T>

Template générique pour traquer les appels :

```cpp
// Enregistrer un appel
call_tracker.record_call({"setSeed", seed, 0});

// Vérifier un appel spécifique  
bool called = call_tracker.was_called_with({"setSeed", 1000, 0});

// Compter les appels
int count = call_tracker.get_call_count();
```

## 🔄 Cycle de développement

1. **Écrire le test** avec mocks déterministes
2. **Implémenter** la logique métier avec interfaces
3. **Exécuter** `./run_native_tests.sh` 
4. **Debugger** sur desktop avec vos outils habituels
5. **Refactorer** en confiance
6. **Intégrer** sur ESP32 avec les vraies implémentations

## 🆚 Comparaison ESP32 vs Native

| Aspect | ESP32 | Native |
|--------|-------|--------|
| **Vitesse** | ~30s compilation + upload | ~2s compilation |
| **Feedback** | Serial monitor | Console direct |
| **Debugging** | Print statements | GDB, IDE debugger |
| **Isolation** | Hardware dependencies | Pure logic |
| **CI/CD** | Complex setup | Simple `make test` |

## 🎓 Patterns démontrés

### Dependency Injection

```cpp
// ❌ Couplage fort
class RandomGenerator {
    String generate() {
        randomSeed(micros());  // Dépendance Arduino directe
        // ...
    }
};

// ✅ Injection de dépendances
class RandomDeviceIdGenerator {
    RandomDeviceIdGenerator(RandomService* random, TimeService* time)
        : randomService(random), timeService(time) {}
    
    std::string generate() {
        randomService->setSeed(timeService->getMicros());
        // ...
    }
};
```

### Strategy Pattern avec polymorphisme

```cpp
// Même interface, implémentations différentes
DeviceIdGenerator* generators[] = {
    new RandomDeviceIdGenerator(&randomService, &timeService),
    new MacAddressDeviceIdGenerator(),
    new MockDeviceIdGenerator()
};

for (auto gen : generators) {
    std::string id = gen->generate();  // Polymorphisme
}
```

## 📊 Résultats

```
🧪 CARPE MODULE - Native Test Suite
====================================
Framework: Unity + Custom Mock Framework
Architecture: Clean Architecture with Dependency Injection
Platform: Native (Desktop)

📋 Running Unit Tests...
[TEST] === RandomDeviceIdGenerator Native Tests ===
[TEST] Testing carpe-XXXXXX format with mocked random values
[TEST] Generated ID: carpe-123456
✅ test_native_generate_format:PASS

[TEST] Testing uniqueness with different time seeds  
[TEST] ID1: carpe-ABCDEF
[TEST] ID2: carpe-KLMNOP
✅ test_native_different_seeds:PASS

[TEST] Testing deterministic behavior with same values
[TEST] Deterministic ID: carpe-0ZI7EV
✅ test_native_deterministic:PASS

[TEST] Testing dependency injection calls
[TEST] Was getMicros called? YES
[TEST] Was setSeed called? YES
[TEST] Dependencies correctly injected and called
✅ test_native_dependency_injection:PASS

[TEST] Testing character validity in generated ID
[TEST] All characters valid: 09AZIP
✅ test_native_character_validity:PASS

📊 Test Summary:
-----------------------
5 Tests 0 Failures 0 Ignored 
OK
```

## 🎯 Conclusion

Cette architecture démontre comment :

- ✅ **Séparer** la logique métier des dépendances hardware
- ✅ **Tester** rapidement sur desktop avec injection de dépendances  
- ✅ **Mocker** de manière déterministe les services externes
- ✅ **Maintenir** un code propre et testable
- ✅ **Accélérer** le cycle de développement

L'injection de dépendances transforme votre code ESP32 en code C++ portable et facilement testable ! 🚀 