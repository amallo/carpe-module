# Makefile pour les tests natifs CARPE MODULE - Device Use Case et Mocks
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -DNATIVE_BUILD -Itest -Isrc
LDFLAGS = 

# Dossiers
SRC_DIR = src
TEST_DIR = test
BUILD_DIR = build

# Sources pour les différents tests
TEST_DEVICE_SOURCES = $(TEST_DIR)/device/test_connect.cpp
TEST_CONFIG_SOURCES = $(TEST_DIR)/config/test_mock_config_provider.cpp $(TEST_DIR)/config/providers/MockConfigProvider.cpp
TEST_ADVANCED_CONFIG_SOURCES = $(TEST_DIR)/config/test_advanced_mock_config_provider.cpp $(TEST_DIR)/config/providers/MockConfigProvider.cpp

# Unity framework (téléchargé depuis GitHub)
UNITY_DIR = unity
UNITY_SRC = $(UNITY_DIR)/src/unity.c

# Exécutables
TARGET_DEVICE = $(BUILD_DIR)/test_device
TARGET_CONFIG = $(BUILD_DIR)/test_config
TARGET_ADVANCED_CONFIG = $(BUILD_DIR)/test_advanced_config

all: $(TARGET_DEVICE) $(TARGET_CONFIG) $(TARGET_ADVANCED_CONFIG)

# Télécharger Unity si nécessaire
$(UNITY_DIR):
	@echo "Téléchargement de Unity..."
	git clone https://github.com/ThrowTheSwitch/Unity.git $(UNITY_DIR)

# Créer le dossier de build
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compiler l'exécutable de test device
$(TARGET_DEVICE): $(BUILD_DIR) $(UNITY_DIR) $(TEST_DEVICE_SOURCES)
	@echo "Compilation du test Device Use Case..."
	$(CXX) $(CXXFLAGS) -I$(UNITY_DIR)/src $(TEST_DEVICE_SOURCES) $(UNITY_SRC) -o $(TARGET_DEVICE)

# Compiler l'exécutable de test config simple
$(TARGET_CONFIG): $(BUILD_DIR) $(UNITY_DIR) $(TEST_CONFIG_SOURCES)
	@echo "Compilation du test Mock Config Provider..."
	$(CXX) $(CXXFLAGS) -I$(UNITY_DIR)/src $(TEST_CONFIG_SOURCES) $(UNITY_SRC) -o $(TARGET_CONFIG)

# Compiler l'exécutable de test config avancé
$(TARGET_ADVANCED_CONFIG): $(BUILD_DIR) $(UNITY_DIR) $(TEST_ADVANCED_CONFIG_SOURCES)
	@echo "Compilation du test Advanced Mock Config Provider..."
	$(CXX) $(CXXFLAGS) -I$(UNITY_DIR)/src $(TEST_ADVANCED_CONFIG_SOURCES) $(UNITY_SRC) -o $(TARGET_ADVANCED_CONFIG)

# Lancer les tests device
test-device: $(TARGET_DEVICE)
	@echo "Exécution du test Device Use Case..."
	$(TARGET_DEVICE)
	@echo ""
	@echo "✅ Tous les tests du use case passent !"

# Lancer les tests config simple
test-config: $(TARGET_CONFIG)
	@echo "Exécution du test Mock Config Provider..."
	$(TARGET_CONFIG)
	@echo ""
	@echo "✅ Tous les tests du mock passent !"

# Lancer les tests config avancé
test-advanced-config: $(TARGET_ADVANCED_CONFIG)
	@echo "Exécution du test Advanced Mock Config Provider..."
	$(TARGET_ADVANCED_CONFIG)
	@echo ""
	@echo "✅ Tous les tests avancés du mock passent !"

# Lancer tous les tests
test: test-device test-config test-advanced-config
	@echo ""
	@echo "🎯 Tous les tests sont passés avec succès !"

# Tests partiels
test-mocks: test-config test-advanced-config
	@echo ""
	@echo "🎭 Tous les tests de mocks sont passés !"

# Nettoyer
clean:
	rm -rf $(BUILD_DIR)
	@echo "Nettoyage terminé."

# Nettoyer complètement (avec Unity)
clean-all: clean
	rm -rf $(UNITY_DIR)
	@echo "Nettoyage complet terminé."

.PHONY: all test test-device test-config test-advanced-config test-mocks clean clean-all 