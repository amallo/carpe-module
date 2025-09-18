# Makefile pour les tests natifs CARPE MODULE - Device Use Case
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -DNATIVE_BUILD -I. -Itest -Isrc
UNITY_FLAGS = -DUNITY_INCLUDE_DOUBLE -DUNITY_DOUBLE_PRECISION=1e-12 -DUNITY_SUPPORT_TEST_CASES -DUNITY_OUTPUT_COLOR
LDFLAGS = 

# Répertoires
BUILD_DIR = build
UNITY_DIR = unity
TEST_DIR = test
UNITY_SRC = $(UNITY_DIR)/src/unity.c

# Fichiers sources pour les tests Device
TEST_DEVICE_SOURCES = \
                     $(TEST_DIR)/device/test_setup_device.cpp \
                     $(TEST_DIR)/config/providers/MockConfigProvider.cpp \
                     $(TEST_DIR)/core/device/generators/MockDeviceIdGenerator.cpp \
                     $(TEST_DIR)/core/device/generators/MockPinCodeGenerator.cpp


# Fichiers sources pour les tests Transport Bluetooth
TEST_TRANSPORT_SOURCES = \
                     $(TEST_DIR)/transport/test_bluetooth_pin_authentication.cpp \
                     $(TEST_DIR)/transport/MockPinCodeGenerator.cpp \
                     src/core/transport/providers/BluetoothConnectionCallback.cpp

# Cibles
TARGET_DEVICE = $(BUILD_DIR)/test_device
TARGET_TRANSPORT = $(BUILD_DIR)/test_transport

# Cibles principales
.PHONY: all test clean build-dirs

all: test

# Créer les répertoires nécessaires
build-dirs:
	@mkdir -p $(BUILD_DIR)

# Télécharger Unity si nécessaire
$(UNITY_DIR):
	@echo "Téléchargement d'Unity..."
	@git clone --depth 1 https://github.com/ThrowTheSwitch/Unity.git $(UNITY_DIR)

# Compiler le test Device
$(TARGET_DEVICE): $(BUILD_DIR) $(UNITY_DIR) $(TEST_DEVICE_SOURCES)
	@echo "Compilation du test Device Use Case..."
	$(CXX) $(CXXFLAGS) $(UNITY_FLAGS) -I$(UNITY_DIR)/src $(TEST_DEVICE_SOURCES) $(UNITY_SRC) -o $(TARGET_DEVICE)


# Compiler le test Transport Bluetooth
$(TARGET_TRANSPORT): $(BUILD_DIR) $(UNITY_DIR) $(TEST_TRANSPORT_SOURCES)
	@echo "Compilation du test Transport Bluetooth..."
	$(CXX) $(CXXFLAGS) $(UNITY_FLAGS) -I$(UNITY_DIR)/src $(TEST_TRANSPORT_SOURCES) $(UNITY_SRC) -o $(TARGET_TRANSPORT)

# Lancer tous les tests
test: build-dirs $(TARGET_DEVICE) $(TARGET_TRANSPORT)
	@echo "Exécution du test Device Use Case..."
	$(TARGET_DEVICE)
	@echo ""
	@echo "Exécution du test Transport Bluetooth..."
	$(TARGET_TRANSPORT)
	@echo ""
	@echo "🎯 Tous les tests sont passés avec succès !"


# Nettoyer
clean:
	@echo "Nettoyage..."
	@rm -rf $(BUILD_DIR)
	@rm -rf $(UNITY_DIR)

.PHONY: all test clean build-dirs 