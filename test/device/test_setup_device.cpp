#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <iostream>
#include <core/device/SetupDeviceUseCase.h>
#include <test/config/providers/MockConfigProvider.h>
#include <test/core/device/generators/MockDeviceIdGenerator.h>
#include <test/core/device/generators/MockPinCodeGenerator.h>
#include <core/logging/providers/infra/ConsoleLogger.h>
#include <test/common/TestDisplay.h>

// Global variables for use case and mocks
SetupDeviceUseCase* useCase = nullptr;
MockConfigProvider* configProvider = nullptr;
MockDeviceIdGenerator* deviceIdGenerator = nullptr;
MockPinCodeGenerator* pinCodeGenerator = nullptr;
ConsoleLogger* logger = nullptr;

struct TestFixture {
    TestFixture() {
        logger = new ConsoleLogger(false);
        logger->setLevel(LogLevel::DEBUG);
        logger->debug("🧪 Initialisation des mocks pour test");
        configProvider = new MockConfigProvider();
        deviceIdGenerator = new MockDeviceIdGenerator();
        pinCodeGenerator = new MockPinCodeGenerator();
        useCase = new SetupDeviceUseCase(configProvider, deviceIdGenerator, pinCodeGenerator);
        logger->debug("✅ Setup terminé");
    }
    ~TestFixture() {
        logger->debug("🧹 Nettoyage des mocks");
        delete useCase;
        delete configProvider;
        delete deviceIdGenerator;
        delete logger;
        useCase = nullptr;
        configProvider = nullptr;
        deviceIdGenerator = nullptr;
        logger = nullptr;
    }
};

TEST_CASE_FIXTURE(TestFixture, "Device deja initialise") {
    TestDisplay::print(TestDisplay::TEST, "Test: Device déjà initialisé");
    
    SetupDeviceRequest request;
    configProvider->scheduleDeviceIdResult("carpe-TEST123");
    SetupDeviceResponse response = useCase->execute(request);
    
    logger->debug("Response success: " + std::string(response.success ? "true" : "false"));
    logger->debug("Response device_id: " + response.device_id);
    logger->debug("Response error: " + response.error_message);
    
    CHECK_FALSE(response.success);
    CHECK(response.device_id == "carpe-TEST123");
    CHECK(response.error_message == "ALREADY_INITIALIZED");
    
    TestDisplay::print(TestDisplay::SUCCESS, "Test device déjà initialisé: PASS");
}

TEST_CASE_FIXTURE(TestFixture, "Setup nouveau device") {
    TestDisplay::print(TestDisplay::TEST, "Test: Setup nouveau device");
    
    SetupDeviceRequest request;
    configProvider->scheduleDeviceIdResult("");
    deviceIdGenerator->scheduleGenerateResult("carpe-TEST123");
    pinCodeGenerator->scheduleGeneratedPinCode("6532");
    
    SetupDeviceResponse response = useCase->execute(request);
    
    logger->debug("Response success: " + std::string(response.success ? "true" : "false"));
    logger->debug("Response device_id: " + response.device_id);
    logger->debug("Generated ID: carpe-TEST123");
    
    CHECK(response.success);
    CHECK(response.device_id == "carpe-TEST123");
    CHECK(response.error_message == "");
    
    // Vérifier que le code PIN a été généré et sauvegardé
    CHECK(configProvider->getLastPinCode() == "6532");
    
    TestDisplay::print(TestDisplay::SUCCESS, "Test setup nouveau device: PASS");
}