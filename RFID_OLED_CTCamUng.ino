                                      /* ĐỒ ÁN CƠ ĐIỆN TỬ */


#include "SPI.h"
#include "MFRC522.h"

#include <DHT.h>
#include "U8glib.h"

 /* Typical pin layout used: RFID
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
 
/* ##NodeMcu##    SDA(SS) D4 (Có Thể Đổi)
                  RST     D3 (Có Thể Đổi)
                  SCK     D5
                  MISO    D6
                  MOSI    D7 */

#define SS_PIN  53  //   RFID
#define RST_PIN 5   //   RFID

#define DHTPIN 2 // CB DHT22
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
#define gasSensor A0 // Gas

#define touch1 30 // đèn ngủ 1 1
#define touch2 32 // quạt ngủ  2
#define touch3 34 // đèn vườn  3
#define touch4 36 // đèn khách 4
#define touch5 38 // quạt khách 5
#define touch6 40 // đèn cổng 6
#define touch7 42 // đèn gara  7
#define touch8 44 // đèn bếp   8
#define touch9 46 // quạt bếp  9
#define touch10 48 // đèn tắm  10
#define touch11 26 // đèn ngủ 2 11


#define denngu1 31
#define quatngu 33
#define denvuon 35
#define denkhach 37
#define quatkhach 39
#define dencong 41
#define dengara 43
#define denbep 45
#define quatbep 47
#define dentam 49
#define denngu2 28

int LED = 6; //dentam
int PIR = 7; //PIR

DHT dht(DHTPIN, DHTTYPE);

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);  // Display which does not send AC

MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

const uint8_t logo[] PROGMEM =
{
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x18, 0x0, 0x38, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0xc3,
  0x80, 0x0, 0x0, 0x0, 0x18, 0x0, 0x38, 0x6, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x1,
  0xc3, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0xc0, 0x0, 0x0, 0x0, 0x0,
  0x1, 0xc3, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0xc0, 0x0, 0x0, 0x0,
  0x0, 0x1, 0xc3, 0x8e, 0xc, 0x6e, 0x60, 0xf8, 0x7, 0xb8, 0x3e, 0x3, 0xfc, 0x38, 0x18,
  0x0, 0x0, 0x1, 0xc3, 0x8e, 0xc, 0x7e, 0xf0, 0xf8, 0xf, 0xf8, 0x3e, 0x3, 0xfc, 0x38,
  0x38, 0x0, 0x0, 0x1, 0xff, 0x8e, 0xc, 0x77, 0x30, 0x18, 0xe, 0x38, 0x6, 0x0, 0xc0,
  0x18, 0x30, 0x0, 0x0, 0x1, 0xff, 0x8e, 0xc, 0x67, 0x30, 0x18, 0x1c, 0x38, 0x6, 0x0,
  0xc0, 0x1c, 0x30, 0x0, 0x0, 0x1, 0xff, 0x8e, 0xc, 0x63, 0x30, 0x18, 0x1c, 0x38, 0x6,
  0x0, 0xc0, 0xc, 0x70, 0x0, 0x0, 0x1, 0xc3, 0x8e, 0xc, 0x63, 0x30, 0x18, 0x1c, 0x18,
  0x6, 0x0, 0xc0, 0xc, 0x60, 0x0, 0x0, 0x1, 0xc3, 0x8e, 0xc, 0x63, 0x30, 0x18, 0x1c,
  0x18, 0x6, 0x0, 0xc0, 0xe, 0x60, 0x0, 0x0, 0x1, 0xc3, 0x86, 0x1c, 0x63, 0x30, 0x18,
  0x1c, 0x18, 0x6, 0x0, 0xc0, 0x6, 0xc0, 0x0, 0x0, 0x1, 0xc3, 0x87, 0x1c, 0x63, 0x30,
  0x18, 0xe, 0x38, 0x6, 0x0, 0xe0, 0x7, 0xc0, 0x0, 0x0, 0x1, 0xc3, 0x87, 0xec, 0x63,
  0x31, 0xff, 0x8f, 0xd8, 0x7f, 0xe0, 0xfe, 0x3, 0xc0, 0x0, 0x0, 0x1, 0xc3, 0x83, 0xcc,
  0x63, 0x31, 0xff, 0x87, 0x98, 0x7f, 0xe0, 0x7e, 0x3, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x10, 0x0, 0x0, 0x0, 0x3, 0x80, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1f, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1e, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3c, 0x38, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3c, 0x78, 0x0, 0x1, 0x80, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3c, 0x78, 0x0, 0x1, 0x80, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3e, 0x78, 0x3e, 0x7, 0xf8,
  0xf, 0x81, 0xcf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x36, 0xd8, 0x7f, 0x7,
  0xf8, 0x1f, 0xc0, 0xdf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x36, 0xd8, 0xe1,
  0x81, 0x80, 0x38, 0x60, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x33, 0xd8,
  0xc1, 0xc1, 0x80, 0x30, 0x70, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x33,
  0x99, 0xff, 0xc1, 0x80, 0x7f, 0xf0, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x33, 0x99, 0xff, 0xc1, 0x80, 0x7f, 0xf0, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x31, 0x99, 0xc0, 0x1, 0x80, 0x70, 0x0, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x30, 0x18, 0xc0, 0x1, 0x80, 0x30, 0x0, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x30, 0x18, 0xe1, 0xc1, 0xc0, 0x38, 0x70, 0xc0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x30, 0x18, 0x7f, 0x81, 0xfc, 0x1f, 0xe0, 0xc0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x30, 0x18, 0x3e, 0x0, 0xfc, 0xf, 0x80, 0xc0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0
};

  int dem;
  
  bool first = true;
  float hum = 0.0;
  float temp = 0.0;
  int ctht1,ctht2;
  int gas = 0;

  int val1, val2, val3, val4, val5, val6, val7, val8, val9, val10, val11 ;
  int dem1, dem2, dem3, dem4, dem5, dem6, dem7, dem8, dem9, dem10, dem11 ;

bool dht_test(float* hum, float* temp, int* gas);

void setup() {
  
    Serial.begin(9600);

    pinMode(LED ,OUTPUT);
    pinMode(PIR, INPUT);  //  PIR
    digitalWrite(LED,HIGH);
    
    pinMode(8, INPUT); // CTHT1
    pinMode(9, INPUT); // CTHT2
    pinMode(10 , OUTPUT); // motor cổng
    pinMode(11 ,OUTPUT); // motor cổng
    
    pinMode(dencong,OUTPUT);
    pinMode(dengara,OUTPUT);
    pinMode(denvuon,OUTPUT);
    pinMode(denkhach,OUTPUT);
    pinMode(denngu1,OUTPUT);
    pinMode(denngu2,OUTPUT);
    pinMode(denbep,OUTPUT);
    pinMode(dentam,OUTPUT);        //
    pinMode(quatngu,OUTPUT);
    pinMode(quatkhach,OUTPUT);
    pinMode(quatbep,OUTPUT);

    pinMode(touch1, INPUT);
    pinMode(touch2, INPUT);
    pinMode(touch3, INPUT);
    pinMode(touch4, INPUT);
    pinMode(touch5, INPUT);
    pinMode(touch6, INPUT);
    pinMode(touch7, INPUT);
    pinMode(touch8, INPUT);
    pinMode(touch9, INPUT);
    pinMode(touch10, INPUT);
    pinMode(touch11, INPUT);

    digitalWrite(3,HIGH);
    digitalWrite(4,HIGH);

    digitalWrite(dencong, HIGH);
    digitalWrite(dengara, HIGH);
    digitalWrite(denvuon, HIGH);
    digitalWrite(denkhach, HIGH);
    digitalWrite(denngu1, HIGH);
    digitalWrite(denngu2, HIGH);
    digitalWrite(denbep, HIGH);
    digitalWrite(dentam, HIGH);
    digitalWrite(quatkhach, HIGH);
    digitalWrite(quatngu, HIGH);
    digitalWrite(quatbep, HIGH);

    SPI.begin();
    
    dht.begin();
    
    rfid.PCD_Init();

    first = true;
  
    // assign default color value
    if (u8g.getMode() == U8G_MODE_R3G3B2)
    {
      u8g.setColorIndex(255);     // white
    }
    else if (u8g.getMode() == U8G_MODE_GRAY2BIT)
    {
      u8g.setColorIndex(3);         // max intensity
    }
    else if (u8g.getMode() == U8G_MODE_BW)
    {
      u8g.setColorIndex(1);         // pixel on
    }
    else if (u8g.getMode() == U8G_MODE_HICOLOR)
    {
      u8g.setHiColorByRGB(255, 255, 255);
    }
  
    // picture loop
    u8g.firstPage();
  
    do
    {
      u8g.drawBitmapP(0, 0, 16, 64, logo);
    }
    while (u8g.nextPage());
  
    dht_test(&hum, &temp, &gas);

}

void loop() {

    val1 = digitalRead(touch1);
    val2 = digitalRead(touch2);
    val3 = digitalRead(touch3);
    val4 = digitalRead(touch4);
    val5 = digitalRead(touch5);
    val6 = digitalRead(touch6);
    val7 = digitalRead(touch7);
    val8 = digitalRead(touch8);
    val9 = digitalRead(touch9);
    val10 = digitalRead(touch10);
    val11 = digitalRead(touch11);

   nutnhan();
  
   rfidtest();

   pirsensor();

   bool result = dht_test(&hum, &temp, &gas);
  
    if (first)
    {
      // skip displaying readings first time, as its stale data.
      first = false;
    }
    else
    {
      if(result == false)
      {
        u8g.firstPage();
        do 
        {
          // sensor error
          u8g.setFont(u8g_font_fub11);
          u8g.setFontRefHeightExtendedText();
          u8g.setDefaultForegroundColor();
          u8g.setFontPosTop();
          u8g.drawStr(10, 30, "Sensor Error");
        }
        while (u8g.nextPage());
      }
      else
      {
        u8g.firstPage();
        do
        {
          HumMeter(&hum, &temp, &gas);
        }
        while (u8g.nextPage());
      }
    }
    
    delay(10);
}

bool dht_test(float* hum, float* temp,int* gas)
{
  // Wait a few seconds between measurements.
  delay(500);
  *hum = 0;
  *temp = 0;
  *gas = 0;

  
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // gas
  int g = analogRead(gasSensor);
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f))
  {
    Serial.println("Failed to read from DHT sensor!");
    return false;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C\t");
  Serial.print("Gas: ");
  Serial.print(g);
  Serial.println(" PPM");
  
  *hum = h;
  *temp = t;
  *gas = g;

  return true;
}

void rfidtest()
{
  ctht1=digitalRead(8);
   ctht2=digitalRead(9);
 //////
 if(dem%2==1)
 {
 if (ctht1==1 && ctht2==0  || ctht1==1 && ctht2==1)
      {
        digitalWrite(10,HIGH);
        digitalWrite(11,LOW);
      }
      if( (ctht1==0 && ctht2==1) || (ctht1==0 && ctht2==0) )
      {
        digitalWrite(10,LOW);
        digitalWrite(11,LOW);
      }
        
    }
    else
    {
        if( ctht1==0 && ctht2==1 || ctht1==1 && ctht2==1 )
      {
        digitalWrite(11,HIGH);
        digitalWrite(10,LOW);
      }
      if( (ctht1==1 && ctht2==0) || (ctht1==0 && ctht2==0) )
      {
        digitalWrite(10,LOW);
        digitalWrite(11,LOW);
      }
       
    }
    //////
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
   
    if (strID.indexOf("70:82:41:A8") >= 0) {
      dem = dem + 1; }
//    if ((dem % 2)  == 1 ) 
//    {     
//        digitalWrite(3,HIGH);
//        digitalWrite(4,LOW);  
//    }
//    else
//    {    
//        digitalWrite(4,HIGH);
//        digitalWrite(3,LOW);
//    }

    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
    if (dem >= 2) dem=0;
}

void HumMeter(float* hum, float* temp, int* gas)
{
    u8g.setFont(u8g_font_fub11);
    u8g.setFontRefHeightExtendedText();
    u8g.setDefaultForegroundColor();
    u8g.setFontPosTop();
    u8g.drawStr(4, 0, "Hum % :");
    u8g.setPrintPos(85, 0);
    u8g.print(*hum);
  //#ifdef METRIC
    // if metric system, display Celsius
    u8g.drawStr(4, 20, "Temp *C :");
  //#else
    //display Farenheit
    //u8g.drawStr(4, 20, "Temp F");
  //#endif
  
    u8g.setPrintPos(85, 20);
    u8g.print(*temp);
    u8g.drawStr(4, 40, "Gas PPM :");
    u8g.setPrintPos(90, 40);
    u8g.print(*gas);
}
void nutnhan()
{
    if (val1 == 1)  
  {  
    dem1 ++;
  }
  if (dem1 == 2 ) dem1 = 0;
  if (dem1 == 1) digitalWrite(denngu1, LOW);
  else            digitalWrite(denngu1, HIGH);

   if (val2 == 1)  
  {
    dem2 ++;
  }
  if (dem2 == 2 ) dem2 = 0;
  if (dem2 == 1) digitalWrite(quatngu, LOW);
  else            digitalWrite(quatngu, HIGH);

   if (val3 == 1)  
  {
    dem3 ++;
  }
  if (dem3 == 2 ) dem3 = 0;
  if (dem3 == 1) digitalWrite(denvuon, LOW);
  else            digitalWrite(denvuon, HIGH);

  if (val4 == 1)  
  {
    dem4 ++;
  }
  if (dem4 == 2 ) dem4 = 0;
  if (dem4 == 1) digitalWrite(denkhach, LOW);
  else           digitalWrite(denkhach, HIGH);

  if (val5 == 1)  
  {
    dem5 ++;
  }
  if (dem5 == 2 ) dem5 = 0;
  if (dem5 == 1) digitalWrite(quatkhach, LOW);
  else digitalWrite(quatkhach, HIGH);

  if (val6 == 1)  
  {
    dem6 ++;
  }
  if (dem6 == 2 ) dem6 = 0;
  if (dem6 == 1) digitalWrite(dencong, LOW);
  else digitalWrite(dencong, HIGH);

  if (val7 == 1)  
  {
    dem7 ++; 
  }
  if (dem7 == 2 ) dem7 = 0;
  if (dem7 == 1) digitalWrite(dengara, LOW);
  else digitalWrite(dengara, HIGH);

  if (val8 == 1)  
  {
    dem8 ++; 
  }
  if (dem8 == 2 ) dem8 = 0;
  if (dem8 == 1) digitalWrite(denbep, LOW);
  else digitalWrite(denbep, HIGH);

  if (val9 == 1)  
  {
    dem9 ++;
  }
  if (dem9 == 2 ) dem9 = 0;
  if (dem9 == 1) digitalWrite(quatbep, LOW);
  else digitalWrite(quatbep, HIGH);

  if (val10 == 1)  
  {
    dem10 ++;
  }
  if (dem10 == 2 ) dem10 = 0;
  if (dem10 == 1) digitalWrite(dentam, LOW);
  else digitalWrite(dentam, HIGH);

  if (val11 == 1)  
  {
    dem11 ++;
  }
  if (dem11 == 2 ) dem11 = 0;
  if (dem11 == 1) digitalWrite(denngu2, LOW);
  else digitalWrite(denngu2, HIGH);
  
}

void pirsensor() {
  
  int value = digitalRead(PIR);
  if (value == HIGH){
    digitalWrite(LED, LOW);
  }
  else {
    digitalWrite(LED, HIGH);
  }
}

