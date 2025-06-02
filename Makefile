# Makefile pour les tests natifs CARPE MODULE
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -DNATIVE_BUILD -Itest -Isrc
LDFLAGS = 

# Dossiers
SRC_DIR = src
TEST_DIR = test
BUILD_DIR = build

# Sources
SOURCES = $(SRC_DIR)/core/device/generators/RandomDeviceIdGenerator.cpp
TEST_SOURCES = $(TEST_DIR)/test_random_device_id_generator_native.cpp $(TEST_DIR)/test_main_native.cpp

# Unity framework (téléchargé depuis GitHub)
UNITY_DIR = unity
UNITY_SRC = $(UNITY_DIR)/src/unity.c

# Exécutable
TARGET = $(BUILD_DIR)/test_native

all: $(TARGET)

# Télécharger Unity si nécessaire
$(UNITY_DIR):
	@echo "Téléchargement de Unity..."
	git clone https://github.com/ThrowTheSwitch/Unity.git $(UNITY_DIR)

# Créer le dossier de build
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compiler l'exécutable de test
$(TARGET): $(BUILD_DIR) $(UNITY_DIR) $(SOURCES) $(TEST_SOURCES)
	@echo "Compilation des tests natifs..."
	$(CXX) $(CXXFLAGS) -I$(UNITY_DIR)/src $(SOURCES) $(TEST_SOURCES) $(UNITY_SRC) -o $(TARGET) $(LDFLAGS)

# Exécuter les tests
test: $(TARGET)
	@echo "Exécution des tests natifs..."
	./$(TARGET)

# Nettoyer
clean:
	rm -rf $(BUILD_DIR)

# Nettoyer tout (y compris Unity)
distclean: clean
	rm -rf $(UNITY_DIR)

.PHONY: all test clean distclean 