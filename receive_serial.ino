#include <ArduinoJson.h>
#include <SoftwareSerial.h>

// Declare the "link" serial port
// Please see SoftwareSerial library for detail
SoftwareSerial linkSerial(10, 11); // RX, TX

void setup() {
  // Initialize "debug" serial port
  // The data rate must be much higher than the "link" serial port
  Serial.begin(9600);
  while (!Serial) continue;

  // Initialize the "link" serial port
  // Use the lowest possible data rate to reduce error ratio
  Serial1.begin(9600);
}

void loop() {
  // Check if the other Arduino is transmitting
  if (Serial1.available())
  {
    // Allocate the JSON document
    // This one must be bigger than for the sender because it must store the strings
    StaticJsonDocument<300> doc;

    // Read the JSON document from the "link" serial port
    DeserializationError err = deserializeJson(doc, Serial1);

    if (err == DeserializationError::Ok)
    {
      // Print the values
      // (we must use as<T>() to resolve the ambiguity)
      Serial.print("ES = ");
      Serial.println(doc["ES"].as<int>());
      Serial.print("PS = ");
      Serial.println(doc["PS"].as<int>());
      Serial.print("R3_STATS = ");
      Serial.println(doc["R3_STATS"].as<int>());
      Serial.print("battery = ");
      Serial.println(doc["battery"].as<float>());
      Serial.print("ampere1 = ");
      Serial.println(doc["ampere1"].as<float>());
      Serial.print("ampere2 = ");
      Serial.println(doc["ampere2"].as<float>());
      Serial.print("ampere3 = ");
      Serial.println(doc["ampere3"].as<float>());
      Serial.print("bbm = ");
      Serial.println(doc["bbm"].as<float>());
      Serial.print("temp = ");
      Serial.println(doc["temp"].as<float>());
      Serial.print("pressu = ");
      Serial.println(doc["pressu"].as<float>());
      Serial.print("lat = ");
      Serial.println(doc["lat"].as<float>());
      Serial.print("lon = ");
      Serial.println(doc["lon"].as<float>());
    }
    else
    {
      // Print error to the "debug" serial port
      Serial.print("deserializeJson() returned ");
      Serial.println(err.c_str());

      // Flush all bytes in the "link" serial port buffer
      while (Serial1.available() > 0)
        Serial1.read();
    }
  }
}
