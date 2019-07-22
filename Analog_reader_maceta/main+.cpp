/*
Analog Reader Maceta Nano:

Lee la se�al anal�gica A0 y la mapea para publicarla a 9600 Baudios por puerto serie

*/

#include <Arduino.h>

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(A0);
  int Humidity = map(sensorValue, 400, 1024, 100, 0);
  Serial.println(Humidity);
  delay(1000);
}
