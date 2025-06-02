# Makefile pour les tests natifs CARPE MODULE - Device Use Case
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -DNATIVE_BUILD -Itest -Isrc
LDFLAGS = 

# Dossiers
SRC_DIR = src
TEST_DIR = test
BUILD_DIR = build

# Sources pour notre nouveau test device
TEST_SOURCES = $(TEST_DIR)/device/test_connect.cpp

# Unity framework (téléchargé depuis GitHub)
UNITY_DIR = unity
UNITY_SRC = $(UNITY_DIR)/src/unity.c

# Exécutable
TARGET = $(BUILD_DIR)/test_device

all: $(TARGET)

# Télécharger Unity si nécessaire
$(UNITY_DIR):
	@echo "Téléchargement de Unity..."
	git clone https://github.com/ThrowTheSwitch/Unity.git $(UNITY_DIR)

# Créer le dossier de build
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compiler l'exécutable de test device
$(TARGET): $(BUILD_DIR) $(UNITY_DIR) $(TEST_SOURCES)
	@echo "Compilation du test Device Use Case..."
	$(CXX) $(CXXFLAGS) -I$(UNITY_DIR)/src $(TEST_SOURCES) $(UNITY_SRC) -o $(TARGET) $(LDFLAGS)

# Exécuter les tests
test: $(TARGET)
	@echo "Exécution du test Device Use Case..."
	./$(TARGET)

# Nettoyer
clean:
	rm -rf $(BUILD_DIR)

# Nettoyer tout (y compris Unity)
distclean: clean
	rm -rf $(UNITY_DIR)

.PHONY: all test clean distclean 