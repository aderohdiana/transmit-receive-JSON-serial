#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#define RX 8 //Serial Receive pin
#define TX 9 //Serial Transmit pin

SoftwareSerial SSerial(RX, TX); // RX, TX
int byteReceived;
int byteSend;

unsigned long interval = 5000; // the time we need to wait
unsigned long previousMillis = 0; // millis() returns an unsigned long.

int ES;
int PS;
int R3_STATS;
float battery;
float ampere1;
float ampere2;
float ampere3;
float bbm;
float temp;
float pressu;
float lat;
float lon;


void setup() {
  Serial.begin(9600);
  SSerial.begin(9600);

}

void loop() {
  unsigned long currentMillis = millis(); // grab current time

  // check if "interval" time has passed (1000 milliseconds)
  if ((unsigned long)(currentMillis - previousMillis) >= interval) {
    ES = 0;
    PS = 1;
    R3_STATS = 0;
    battery = 12.4;
    ampere1 = 8.5;
    ampere2 = 9.2;
    ampere3 = 8;
    bbm = 5;
    temp = 120;
    pressu = 4;
    lat = -7.017587971917217;
    lon = 108.63739431304614;

    StaticJsonDocument<200> doc;
    doc["ES"] = ES;
    doc["PS"] = PS;
    doc["R3_STATS"] = R3_STATS;
    doc["battery"] = battery;
    doc["ampere1"] = ampere1;
    doc["ampere2"] = ampere2;
    doc["ampere3"] = ampere3;
    doc["bbm"] = bbm;
    doc["temp"] = temp;
    doc["pressu"] = pressu;
    doc["lat"] = lat;
    doc["lon"] = lon;


    serializeJson(doc, SSerial);

    // save the "current" time
    previousMillis = millis();
  }

  Serial.println("waktu");
  delay(1000);
}
