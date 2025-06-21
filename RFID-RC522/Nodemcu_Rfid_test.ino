/*
  NodeMCU with RC522 RFID Reader - Read and Display Card Details

  "TESTED & WORKING"


  This Arduino code uses the MFRC522 RFID reader with a NodeMCU (ESP8266)
  to scan 13.56 MHz RFID tags or cards. When a card is scanned, its UID and
  card type will be printed in the Serial Monitor.

  Connections (RC522 -> NodeMCU):
    SDA  -> D2 (GPIO4)
    SCK  -> D5 (GPIO14)
    MOSI -> D7 (GPIO13)
    MISO -> D6 (GPIO12)
    RST  -> D1 (GPIO5)
    3.3V -> 3.3V
    GND  -> GND

  Required Libraries:
    - MFRC522 by GithubCommunity (Install via Library Manager)
    - SPI (Built-in with Arduino IDE)

  Baud Rate: 115200

  Author: Faizul
  Date: 20 June 2025
*/




#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN D2   // SDA
#define RST_PIN D1  // RST

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
  Serial.begin(115200);
  SPI.begin();           // Init SPI bus
  mfrc522.PCD_Init();    // Init MFRC522
  Serial.println("Scan an RFID card...");
}

void loop() {
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial()) return;

  // Show UID on serial monitor
  Serial.print("Card UID: ");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    Serial.print(i < mfrc522.uid.size - 1 ? " " : "");
  }
  Serial.println();

  // Show card type
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  Serial.print("Card Type: ");
  Serial.println(mfrc522.PICC_GetTypeName(piccType));

  mfrc522.PICC_HaltA();      // Stop reading
  mfrc522.PCD_StopCrypto1(); // Stop encryption
}
