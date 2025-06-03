# Makefile pour les tests natifs CARPE MODULE - Device Use Case
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -DNATIVE_BUILD -I. -Itest -Isrc
LDFLAGS = 

# Dossiers
SRC_DIR = src
TEST_DIR = test
BUILD_DIR = build

# Sources pour les différents tests
TEST_DEVICE_SOURCES = $(TEST_DIR)/device/test_setup_device.cpp $(TEST_DIR)/config/providers/MockConfigProvider.cpp $(TEST_DIR)/core/device/generators/MockDeviceIdGenerator.cpp

# Unity framework (téléchargé depuis GitHub)
UNITY_DIR = unity
UNITY_SRC = $(UNITY_DIR)/src/unity.c

# Exécutables
TARGET_DEVICE = $(BUILD_DIR)/test_device

all: $(TARGET_DEVICE)

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

# Lancer les tests device
test-device: $(TARGET_DEVICE)
	@echo "Exécution du test Device Use Case..."
	$(TARGET_DEVICE)
	@echo ""
	@echo "✅ Tous les tests du use case passent !"

# Lancer tous les tests (maintenant seulement device)
test: test-device
	@echo ""
	@echo "🎯 Tous les tests sont passés avec succès !"

# Nettoyer
clean:
	rm -rf $(BUILD_DIR)
	@echo "Nettoyage terminé."

# Nettoyer complètement (avec Unity)
clean-all: clean
	rm -rf $(UNITY_DIR)
	@echo "Nettoyage complet terminé."

.PHONY: all test test-device clean clean-all 