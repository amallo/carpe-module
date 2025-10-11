# Makefile pour les tests natifs CARPE MODULE - Device Use Case
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -DNATIVE_BUILD -I. -Itest -Isrc
DOCTEST_FLAGS =
LDFLAGS = 

# Répertoires
BUILD_DIR = build
DOCTEST_DIR = doctest
TEST_DIR = test

# Fichiers sources pour les tests Device
TEST_DEVICE_SOURCES = \
                     $(TEST_DIR)/device/test_setup_device.cpp \
                     $(TEST_DIR)/config/providers/MockConfigProvider.cpp \
                     $(TEST_DIR)/core/device/generators/MockDeviceIdGenerator.cpp \
                     $(TEST_DIR)/core/device/generators/MockPinCodeGenerator.cpp


# Fichiers sources pour les tests Transport Bluetooth
TEST_TRANSPORT_SOURCES = \
                            $(TEST_DIR)/transport/test_bluetooth_pin_authentication.cpp \
                            $(TEST_DIR)/transport/MockChallengeGenerator.cpp \
                            $(TEST_DIR)/transport/MockMessageTransport.cpp \
                            $(TEST_DIR)/transport/MockScreen.cpp \
                            $(TEST_DIR)/transport/MockAuthMessageEncoder.cpp \
                            src/core/transport/PeerConnection.cpp \
                            src/core/transport/model/Challenge.cpp \
                            src/core/transport/model/AuthRequestMessage.cpp \
                            src/core/transport/model/Message.cpp \
                            src/core/transport/model/MessageHeader.cpp

# Cibles
TARGET_DEVICE = $(BUILD_DIR)/test_device
TARGET_TRANSPORT = $(BUILD_DIR)/test_transport

# Cibles principales
.PHONY: all test clean build-dirs

all: test

# Créer les répertoires nécessaires
build-dirs:
	@mkdir -p $(BUILD_DIR)

# Télécharger doctest si nécessaire
$(DOCTEST_DIR):
	@echo "Téléchargement de doctest..."
	@git clone --depth 1 https://github.com/doctest/doctest.git $(DOCTEST_DIR)

# Compiler le test Device
$(TARGET_DEVICE): $(BUILD_DIR) $(DOCTEST_DIR) $(TEST_DEVICE_SOURCES)
	@echo "Compilation du test Device Use Case..."
	$(CXX) $(CXXFLAGS) $(DOCTEST_FLAGS) -I$(DOCTEST_DIR) $(TEST_DEVICE_SOURCES) -o $(TARGET_DEVICE)


# Compiler le test Transport Bluetooth
$(TARGET_TRANSPORT): $(BUILD_DIR) $(DOCTEST_DIR) $(TEST_TRANSPORT_SOURCES)
	@echo "Compilation du test Transport Bluetooth..."
	$(CXX) $(CXXFLAGS) $(DOCTEST_FLAGS) -I$(DOCTEST_DIR) $(TEST_TRANSPORT_SOURCES) -o $(TARGET_TRANSPORT)

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
	@rm -rf $(DOCTEST_DIR)

.PHONY: all test clean build-dirs 