#include <SPI.h>
#include <LoRa.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define SERVICE_UUID        "6e400001-b5a3-f393-e0a9-e50e24dcca9e" // UART service UUID
#define CHARACTERISTIC_UUID "6e400003-b5a3-f393-e0a9-e50e24dcca9e" // RX characteristic

class MyCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    std::string value = pCharacteristic->getValue();
    if (value.length() > 0) {
      Serial.print("Received via BLE: ");
      for (int i = 0; i < value.length(); i++) {
        Serial.print(value[i]);
      }
      Serial.println();

      // Transmettre la valeur via LoRa
      LoRa.beginPacket();
      LoRa.print(value.c_str());
      LoRa.endPacket();
      
      // Afficher la valeur transmise sur LoRa
      Serial.print("Message transmis via LoRa: BLE->LoRa: ");
      Serial.println(value.c_str());
    }
  }
};

void setup() {
  Serial.begin(115200);
  while (!Serial);

  LoRa.setPins(18, 14, 26); // NSS, RST, DIO0

  if (!LoRa.begin(868E6)) {
    Serial.println("Erreur LoRa");
    while (1);
  }

  Serial.println("LoRa Sender prêt !");

  BLEDevice::init("ESP32-BLE-Server");

  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_WRITE
  );

  pCharacteristic->setCallbacks(new MyCallbacks());
  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->start();

  Serial.println("BLE Server prêt !");
}

void loop() {
  // Le loop est maintenant vide car nous envoyons les données uniquement quand nous recevons quelque chose en BLE
  delay(1000);
}