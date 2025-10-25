#pragma once

// Mock pour NimBLE dans les tests natifs
#ifdef NATIVE_BUILD
// Forward declarations pour les tests
class NimBLECharacteristic {
public:
    void setValue(const uint8_t* data, size_t length) {}
    void notify() {}
};

class NimBLEServer {
public:
    void setCallbacks(void* callback) {}
    void* createService(const char* uuid) { return nullptr; }
};

class NimBLEAdvertising {
public:
    void addServiceUUID(const char* uuid) {}
    void setScanResponse(bool enable) {}
    void setMinPreferred(uint16_t value) {}
    void setMaxPreferred(uint16_t value) {}
    void start() {}
};

class NimBLEDevice {
public:
    static void init(const std::string& deviceName) {}
    static void setPower(int level) {}
    static void* createServer() { return nullptr; }
    static void* getAdvertising() { return nullptr; }
};
#endif
