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
                     $(TEST_DIR)/core/device/generators/MockPinCodeGenerator.cpp \
                     $(TEST_DIR)/core/device/generators/MockCommonIDGenerator.cpp \
                     src/core/device/generators/infra/ESP32CommonIDGenerator.cpp


# Fichiers sources pour les tests Transport Bluetooth
TEST_TRANSPORT_SOURCES = \
                            $(TEST_DIR)/peer/test_initiate_auth_challenge.cpp \
                            $(TEST_DIR)/peer/test_pin_negotiation.cpp \
                            $(TEST_DIR)/peer/test_receive_message.cpp \
                            $(TEST_DIR)/transport/MockChallengeGenerator.cpp \
                            $(TEST_DIR)/transport/MockMessageGateway.cpp \
                            $(TEST_DIR)/transport/MockScreen.cpp \
                            $(TEST_DIR)/transport/MockMessageEncoder.cpp \
                            $(TEST_DIR)/transport/MockAuthChallengeStore.cpp \
                            $(TEST_DIR)/core/device/generators/MockCommonIDGenerator.cpp \
                            src/core/peer/providers/infra/NimBLEMessageGateway.cpp \
                            src/core/peer/providers/infra/InMemoryAuthChallengeStore.cpp \
                            src/core/peer/model/AuthChallenge.cpp \
                            src/core/peer/protocol/messages/InitiateAuthChallengeMessage.cpp \
                            src/core/peer/protocol/messages/AuthChallengeNegociationMessageSucceded.cpp \
                            src/core/peer/protocol/messages/AuthChallengeNegociationFailureMessage.cpp \
                            src/core/peer/model/AuthSession.cpp \
                            src/core/peer/protocol/MessageHeader.cpp \
                            src/core/peer/protocol/UserMessageHeader.cpp \
                            src/core/peer/protocol/decoders/MessageDecoder.cpp \
                            src/core/peer/providers/infra/InMemoryAuthSessionStore.cpp \
                            src/core/peer/usecases/InitiateAuthChallengeUseCase.cpp \
                            src/core/peer/usecases/NegociateAuthChallengeUseCase.cpp \
                            src/core/peer/usecases/ReceiveMessageUseCase.cpp

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
	$(CXX) $(CXXFLAGS) $(DOCTEST_FLAGS) -I$(DOCTEST_DIR) $(TEST_TRANSPORT_SOURCES) test/main.cpp -o $(TARGET_TRANSPORT)

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