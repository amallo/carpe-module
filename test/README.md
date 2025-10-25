# 🧪 CARPE Module - Test Suite

Environnement de tests unitaires et d'intégration pour le projet ESP32 avec Clean Architecture.

## 🏗️ Architecture des Tests

### Structure des Dossiers
```
test/
├── README.md                           # Cette documentation
├── test_framework.h                    # Framework de test personnalisé
├── test_main.cpp                      # Point d'entrée des tests
├── desktop_stubs.h/.cpp               # Simulation Arduino pour desktop
├── test_random_device_id_generator.cpp # Tests unitaires
├── test_bluetooth_integration.cpp     # Tests d'intégration
└── mocks/                             # Test doubles
    └── MockFramework.h                # Framework de mocks
```

## 🚀 Utilisation

### ⚡ Tests Desktop (RAPIDE - Recommandé pour le développement)
```bash
# Tests natifs sur votre PC - TRÈS RAPIDE (< 1 seconde)
./run_native_tests.sh test

# Nettoyer et relancer
./run_native_tests.sh rebuild

# Nettoyer seulement
./run_native_tests.sh clean

# Voir l'aide
./run_native_tests.sh help
```

### 🔧 Tests ESP32 (Pour tests d'intégration matériel)
```bash
# Tests sur ESP32 réel - plus lent mais teste le matériel
pio test -e test

# Avec monitoring en temps réel
pio test -e test --monitor
```

### 📦 Build Principal (SANS les tests)
```bash
# Build du firmware principal
pio run -e carpe-lora

# Upload sur l'ESP32
pio run -e carpe-lora --target upload
```

## ⚖️ Desktop vs ESP32 : Quand utiliser quoi ?

### 🖥️ **Tests Desktop** (run_native_tests.sh) - **Recommandé à 95%**
- ✅ **Vitesse** : < 1 seconde vs 30-60 secondes
- ✅ **Pas besoin de matériel** : Fonctionne sans ESP32 connecté  
- ✅ **Debug facile** : Debugger desktop standard
- ✅ **CI/CD** : Parfait pour l'intégration continue
- ✅ **Développement** : Feedback instantané
- ✅ **Script dédié** : `./run_native_tests.sh` avec options
- 🎯 **Usage** : Tests unitaires, logique métier, mocks

### 📟 **Tests ESP32** (pio test -e test) - **Pour cas spécifiques**
- ✅ **Matériel réel** : Teste les drivers, timing réels
- ✅ **Mémoire** : Vérifie les contraintes mémoire
- ✅ **Performance** : Timing critique, interruptions
- ⚠️ **Lent** : 30-60 secondes par cycle
- ⚠️ **Matériel requis** : ESP32 connecté
- 🎯 **Usage** : Tests d'intégration matériel, validation finale

## 🎯 Types de Tests

### 1. Tests Unitaires (Desktop)
- **Fichier** : `test/device/test_setup_device.cpp`
- **Script** : `./run_native_tests.sh test` ⚡
- **Caractéristiques** :
  - Aucune dépendance externe
  - Très rapides (< 1 seconde)
  - Couvrent les cas nominaux et limites
  - Feedback instantané pendant le développement
  - Tests du SetupDeviceUseCase avec mocks

### 2. Tests d'Intégration avec Mocks (Desktop)
- **Fichier** : `test/device/test_demo_colors.cpp`
- **Script** : `./run_native_tests.sh test` ⚡
- **Caractéristiques** :
  - Utilisation de test doubles (mocks)
  - Vérification des comportements
  - Simulation de pannes
  - Validation de l'architecture
  - Démonstration des couleurs Unity

### 3. Tests d'Intégration Matériel (ESP32)
- **Usage** : Validation finale avant déploiement
- **Commande** : `pio test -e test` 🔧
- **Fréquence** : Avant release ou pour debug hardware

## 🎭 Framework de Mocks

### Création d'un Mock

```cpp
#include "mocks/MockFramework.h"
#include "../src/core/YourInterface.h"

class MockYourInterface : public YourInterface, public MockBase {
private:
    CallTracker<CallInfo> call_tracker;
    ReturnValueManager<bool> return_manager;

public:
    MockYourInterface() : return_manager(true) {}
    
    // Implémentation des méthodes virtuelles
    bool yourMethod(const String& param) override {
        call_tracker.record_call({param});
        return return_manager.get_next_return_value();
    }
    
    // Méthodes de contrôle
    void set_return_value(bool value) { 
        return_manager.set_return_value(value); 
    }
    
    bool was_called_with(const String& param) const {
        return call_tracker.was_called_with({param});
    }
    
    void reset() override {
        call_tracker.reset();
        return_manager.reset();
    }
};
```

### Utilisation dans les Tests

```cpp
void test_with_mock() {
    // ARRANGE
    MockYourInterface mock;
    mock.set_return_value(false);
    
    // ACT
    bool result = mock.yourMethod("test");
    
    // ASSERT
    TEST_ASSERT_FALSE(result);
    TEST_ASSERT_TRUE(mock.was_called_with("test"));
}
```

## 📋 Bonnes Pratiques

### 1. Workflow Recommandé
```bash
# 1. Développement quotidien (très rapide)
./run_native_tests.sh test

# 2. Avant commit (validation complète)
./run_native_tests.sh test && pio run -e carpe-lora

# 3. Avant release (validation matériel)
pio test -e test
```

### 2. Structure AAA (Arrange-Act-Assert)
```cpp
void test_example() {
    // ARRANGE - Préparation
    MockComponent mock;
    mock.set_expected_behavior();
    
    // ACT - Action
    auto result = systemUnderTest.doSomething();
    
    // ASSERT - Vérification
    TEST_ASSERT_TRUE(result);
    TEST_ASSERT_TRUE(mock.was_called());
}
```

### 3. Tests Déterministes
- Éviter les `delay()` longs
- Utiliser des mocks plutôt que du matériel réel
- Tester un comportement à la fois

### 4. Nommage Expressif
```cpp
void test_should_return_false_when_initialization_fails()
void test_should_call_callback_when_data_received()
void test_should_throw_exception_when_invalid_parameter()
```

## 🔧 Configuration

### Flags de Compilation
- **Desktop** : C++17, Unity Doubles, stubs Arduino
- **ESP32** : Arduino framework + C++17
- **Both** : Framework de mocks personnalisé

### Exclusion du Build Principal
- Les tests sont dans `/test/` → **automatiquement exclus**
- Le `build_src_filter` garantit la séparation
- Zero overhead sur le firmware final

## 🐛 Debugging

### Logs de Test
```cpp
TEST_LOG("Message de debug");
DEBUG_PRINT("Valeur: " + String(value));
```

### Assertions Personnalisées
```cpp
ASSERT_STRING_NOT_EMPTY(deviceId);
ASSERT_NOT_NULL(pointer);
ASSERT_STRING_EQUALS("expected", actual);
TEST_ASSERT_NOT_EQUAL_STRING("different", actual);
```

## 🔧 Résolution de Problèmes Courants

### Erreur "only virtual member functions can be marked 'override'"
**Problème** : Les mocks essaient d'override des méthodes qui ne sont pas virtuelles dans l'interface de base.

**Solution** : Supprimer `override` des méthodes qui ne sont pas dans l'interface :
```cpp
// ❌ Incorrect
bool loadConfig() override;    // loadConfig n'existe pas dans ConfigProvider

// ✅ Correct  
bool loadConfig();            // Méthode supplémentaire du mock
std::string getDeviceId() override;  // Méthode de l'interface
```

### Erreur "Nothing to build"
**Problème** : PlatformIO ne trouve pas les tests.

**Solution** : Utiliser le script natif à la place :
```bash
# ❌ Ne fonctionne pas
pio test -e test_native

# ✅ Fonctionne
./run_native_tests.sh test
```

## 📈 Workflow de Développement

### 🔄 Cycle de Développement Rapide
1. **Écrire le test** (TDD) → `./run_native_tests.sh test`
2. **Implémenter le code** 
3. **Valider rapidement** → `./run_native_tests.sh test` (< 1s)
4. **Refactorer** si nécessaire
5. **Répéter**

### 🚀 Avant Déploiement
1. **Tests desktop** → `./run_native_tests.sh test`
2. **Build production** → `pio run -e carpe-lora`
3. **Tests ESP32** (optionnel) → `pio test -e test`
4. **Deploy** → `pio run -e carpe-lora --target upload`

## 📈 Ajout de Nouveaux Tests

1. **Créer le fichier de test** : `test/device/test_your_component.cpp`
2. **Développer avec desktop** : `./run_native_tests.sh test`
3. **Ajouter au Makefile** si nécessaire
4. **Créer les mocks** si nécessaire dans `/test/`

## 🛠️ Script de Tests Natifs

Le script `run_native_tests.sh` fournit une interface simple pour les tests :

```bash
# Options disponibles
./run_native_tests.sh test      # Exécuter les tests
./run_native_tests.sh clean     # Nettoyer les fichiers de build
./run_native_tests.sh rebuild   # Clean + build + test
./run_native_tests.sh help      # Afficher l'aide
```

### Avantages du script :
- ✅ **Compilation automatique** avec les bons flags
- ✅ **Gestion des dépendances** Unity et mocks
- ✅ **Affichage coloré** des résultats
- ✅ **Nettoyage automatique** des fichiers temporaires

---

✅ **Les tests sont complètement isolés du build de production !**
⚡ **Utilisez `./run_native_tests.sh test` pour 95% de vos tests - c'est 50x plus rapide !** 