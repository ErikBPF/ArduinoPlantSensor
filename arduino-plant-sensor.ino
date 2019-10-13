#include <Thermistor.h>
#include "DHT.h"


#define DHTTYPE DHT11
#define DHTPIN A0

Thermistor temp(2);
DHT dht(DHTPIN, DHTTYPE);

int WaterCapacitancePin = A1;
int LightSensorPin = A3;
int RainSensorPin = A4;

const int AirCapacitance = 780;   //you need to replace this value with Value_1
const int WaterCapacitance = 330;  //you need to replace this value with Value_2

void setup() {
  Serial.begin(9600);
  Serial.println(F("Sensor de condições de plantio"));

  dht.begin();
}

void loop() {
  float AirHumidity = dht.readHumidity();
  float AirTemperature = dht.readTemperature();
  float HeatIndex = dht.computeHeatIndex(AirTemperature, AirHumidity);
  int SoilTemperature = temp.getTemp();
  int Light = analogRead(LightSensorPin);
  int Rain = analogRead(RainSensorPin);
  float Capacitance = analogRead(WaterCapacitancePin);
  float WaterHumidity = ((1-((Capacitance-WaterCapacitance)/(AirCapacitance-WaterCapacitance)))*100);
  
  Serial.print(F("Temperatura do solo: "));
  Serial.print(SoilTemperature);
  Serial.print(F("°C  "));
  Serial.print(F("Humidade do solo: "));
  Serial.print(WaterHumidity);
  Serial.print(F("  Temperatura do ar: "));
  Serial.print(AirTemperature);
  Serial.print(F("°C  "));
  Serial.print(F("%  Humidade do ar: "));
  Serial.print(AirHumidity);
  Serial.print(F("%  Temperatura do ar percebida: "));
  Serial.print(HeatIndex);
  Serial.print(F("°C  "));
  Serial.print(F("Luz: "));
  Serial.print(Light);
  Serial.print(F(" Chuva: "));
  Serial.println(Rain);
  
  delay(3000);
}
