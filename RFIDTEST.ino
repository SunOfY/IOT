

#include "SPI.h"
#include "MFRC522.h"

 /* Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */
 
// ##NodeMcu##    SDA(SS) D4 (Có Thể Đổi)
//                RST     D3 (Có Thể Đổi)
//                SCK     D5
//                MISO    D6
//                MOSI    D7

#define SS_PIN  10   //10 Arduino UNO
#define RST_PIN 9   //9  Arduino UNO
#define LED_PIN 8   

int dem;

MFRC522 rfid(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;

void setup() {
    Serial.begin(9600);
    SPI.begin();
    rfid.PCD_Init();
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
  rfidtest();
  //Serial.println("Have Fun");
  //delay(100);
}
void rfidtest()
{
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;

  // Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  // Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  String strID = "";
  for (byte i = 0; i < 4; i++) {
    strID +=
    (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
    String(rfid.uid.uidByte[i], HEX) +
    (i!=3 ? ":" : "");
  }
  strID.toUpperCase();

  Serial.print("Tap card key: ");
  Serial.println(strID);
  
  if (strID.indexOf("2F:E8:A2:79") >= 0) {
    dem = dem + 1; }
  if ((dem % 2)  == 1 ) digitalWrite(LED_PIN,HIGH);
  else   digitalWrite(LED_PIN,LOW);
  Serial.println(dem);

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  if (dem == 2) dem=0;
}


