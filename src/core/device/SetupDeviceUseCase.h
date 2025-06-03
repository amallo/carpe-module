#include <string>
#include <core/config/providers/ConfigProvider.h>
#include <core/device/generators/DeviceIdGenerator.h>

// Copie des définitions nécessaires
struct SetupDeviceRequest {
    // Paramètres vides pour l'instant comme demandé
};

struct SetupDeviceResponse {
    bool success;
    std::string device_id;
    std::string error_message;
    
    SetupDeviceResponse(bool success = false, 
                               const std::string& deviceId = "", 
                               const std::string& error = "")
        : success(success), device_id(deviceId), error_message(error) {}
};

class SetupDeviceUseCase {
    ConfigProvider* configProvider;
    DeviceIdGenerator* deviceIdGenerator;
public:
    SetupDeviceUseCase(ConfigProvider* configProvider, DeviceIdGenerator* deviceIdGenerator) : configProvider(configProvider), deviceIdGenerator(deviceIdGenerator) {}
    SetupDeviceResponse execute(const SetupDeviceRequest& request)  {
        std::string deviceId = configProvider->getDeviceId();
        if (deviceId == "") {
            // Appareil pas encore initialisé, générer un nouvel ID
            std::string newDeviceId = deviceIdGenerator->generate();
            // Sauvegarder l'ID dans la config
            configProvider->setDeviceId(newDeviceId);
            return SetupDeviceResponse(true, configProvider->getDeviceId(), "");
        }
        return SetupDeviceResponse(false, deviceId, "ALREADY_INITIALIZED");
    }
};
