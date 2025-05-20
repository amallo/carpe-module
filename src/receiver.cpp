#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  while (!Serial);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Écran OLED non détecté"));
    while(1);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  LoRa.setPins(18, 14, 26); // NSS, RST, DIO0
  if (!LoRa.begin(868E6)) {
    Serial.println("Erreur LoRa");
    while (1);
  }

  Serial.println("LoRa Receiver prêt !");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String msg = "";
    while (LoRa.available()) {
      msg += (char) LoRa.read();
    }
    Serial.println("Reçu : " + msg);

    display.clearDisplay();
    display.setCursor(0,0);
    display.println(msg);
    display.display();
  }
}