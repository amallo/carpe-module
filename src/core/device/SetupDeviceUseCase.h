#include <string>

// Copie des définitions nécessaires
struct SetupDeviceRequest {
    // Paramètres vides pour l'instant comme demandé
};

struct SetupDeviceResponse {
    bool success;
    std::string device_id;
    std::string error_message;
    bool was_already_initialized;
    
    SetupDeviceResponse(bool success = false, 
                               const std::string& deviceId = "", 
                               const std::string& error = "",
                               bool alreadyInit = false)
        : success(success), device_id(deviceId), error_message(error), was_already_initialized(alreadyInit) {}
};

// Implémentation simple pour le test
class SetupDeviceUseCase {
public:
    SetupDeviceResponse execute(const SetupDeviceRequest& request)  {
        return SetupDeviceResponse(true, "carpe-TEST123", "", false);
    }
    
    bool isDeviceInitialized()  {
        return false;
    }
};
