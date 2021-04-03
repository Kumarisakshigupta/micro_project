#include <SoftwareSerial.h>
#include <ArduinoJson.h>
SoftwareSerial s(5,6);
#include "DHT.h"
#define DHTPIN A4// what pin we're connected to // Uncomment whatever type you're using!
#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT22 // DHT 22 (AM2302)
//#define DHTTYPE DHT21 // DHT 21 (AM2301)
// Initialize DHT sensor for normal 16mhz Arduino DHT dht(DHTPIN, DHTTYPE);
DHT dht(DHTPIN, DHTTYPE);
const int sensorPin = A0;
void setup() { s.begin(9600);
Serial.begin(9600);
Serial.println("DHTxx test!");
dht.begin();
pinMode(A0, INPUT);
}
void loop()
{
// Reading data from DHT11 to operate Fan for controlling Temp. and humidity
//delay(2OOO);
// Reading temperature or humidity takes about 25O milliseconds!
// Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor) float h = dht.readHumid
ity();
// Read temperature as Celsius
float t = dht.readTemperature();
// Read temperature as Fahrenheit
float f = dht.readTemperature(true);
float h = dht.readHumidity();
// Check if any reads failed and exit early (to try again).
if (isnan(h) || isnan(t) || isnan(f)) {
Serial.println("Failed to read from DHT sensor!");
return;
}
// Compute heat index
// Must send in temp in Fahrenheit!
// Compute heat index in Fahrenheit (the default)
 float hif = dht.computeHeatIndex(f, h);
 // Compute heat index in Celsius (isFahreheit = false)
 float hic = dht.computeHeatIndex(t, h, false);
Serial.print("Humidity: ");
Serial.print(h);
Serial.print(" %\t");
Serial.print("Temperature: ");
Serial.print(t);
Serial.print(" *C ");
Serial.print(f);
Serial.print(" *F\t");
Serial.print("Heat index: ");
Serial.print(hic);
Serial.println(" *C");
Serial.print (hif);
Serial.println (" *F");
////////////////////////////////////////////////////////////////////////////////////////////////
float h2 = analogRead(A0);
Serial.print("Gas Level: ");
Serial.println(h2);
////////////////////////////////////////////////////////////////////////////
StaticJsonDocument<1000> jsonBuffer;
JsonObject root = jsonBuffer.to<JsonObject>();
root["h"] = h;
root["t"] = t;
root["f"]=f;
root["hic"]=hic;
root["gas"]=h2;
if(s.available()>0)
{
serializeJsonPretty(root, Serial);
}
}