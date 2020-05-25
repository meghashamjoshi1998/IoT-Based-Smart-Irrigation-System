#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

#include "time.h"

#define BLYNK_PRINT Serial
#define DHTTYPE DHT22
#define DHTPIN 27
DHT dht(DHTPIN, DHTTYPE);
const int sensorPin = 34;//soil moisture sensor 1
const int sensorPin1 = 35;//soil moisture sensor 2
int value_1, value_2; //output values for

int min_value_1 = 2500;
int min_value_2 = 2500;
int min_temp = 25;
int min_humidity = 60;
const int relayPin = 25;

bool isMoistureLow = false;

char auth[] = "9CfduEw4f3TNSo3R-n4z1NAmvUeqqBJ-";

const char* ssid       = "Meghasham08";
const char* pass       = "123456789";

BlynkTimer timer;

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 19800;
const int   daylightOffset_sec = 3600;

bool isPumpOn = false;


void printLocalTime()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}


void sendSensor()
{
  value_1 = analogRead(sensorPin);//for reading soilmoisture sensor connected to analog pin 34
  value_2 = analogRead(sensorPin1);//for reading soil moisture sensor connected to analog pin 36

  Serial.print(value_1); Serial.print("\t");
  Serial.println(value_2);

  //moisturelevel_1 = constrain ( map(value_1, 1000, 4095, 100, 0), 0, 100);
  //moisturelevel_2 = constrain ( map(value_2, 1000, 4095, 100, 0), 0, 100);

  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  float f = dht.readTemperature(true);
  float hif = dht.computeHeatIndex(f, h);

  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
  Blynk.virtualWrite(V9, f);
  Blynk.virtualWrite(V10, hif);
  Blynk.virtualWrite(V7, value_1);
  Blynk.virtualWrite(V8, value_2);

  if (value_1 >= min_value_1 || value_2 >= min_value_2)
  {
    isMoistureLow = true;
    Blynk.email("joshimeghashyam33@gmail.com", "Irrigation System", "Watering Plants");
    delay(1);
    PumpOn();
    delay(1);
  }
  else
  {
    isMoistureLow = false;
    PumpOff();
    delay(1);
  }

}


void setup()
{
  // Debug console
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);

  Serial.begin(9600);


  Serial.print("Connecting..."); Serial.println();

  Blynk.begin(auth, ssid, pass);

  Serial.print("Connected!!"); Serial.println();

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  checkPumpStatus();

  printLocalTime();

  dht.begin();

  PumpOff();
}

void loop()
{

  Blynk.run();
  sendSensor();
  checkPumpStatus();
  delay(1);
}

void checkPumpStatus() {

  if (isMoistureLow) {
    return;
  }

  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }


  int hrs = timeinfo.tm_hour;
  int mins = timeinfo.tm_min;
  int secs = timeinfo.tm_sec;

  int timeInSec = (hrs * 3600) + (mins * 60) + secs;

  Serial.println(timeInSec);
  //9:00 AM - 9:45 AM
  if ((timeInSec > 32400 && timeInSec < 34200) || (timeInSec > 57600 && timeInSec < 59400)) {
    Serial.println("Pump On!");
    PumpOn();
  } else {
    Serial.println("Pump Off!");
    PumpOff();
  }

}

void PumpOn() {
  if (!isPumpOn) {
    isPumpOn = true;
    //Serial.println("Pump On!");
    digitalWrite(relayPin, LOW);
  }
}

void PumpOff() {
  if (isPumpOn) {
    isPumpOn = false;
    //Serial.println("Pump Off!");
    digitalWrite(relayPin, HIGH);
  }
}