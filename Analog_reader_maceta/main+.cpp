/*
Analog Reader Maceta Nano:

Lee la se�al anal�gica A0 y la mapea para publicarla a 9600 Baudios por puerto serie

*/

void loop() {
  int sensorValue = analogRead(A0);
  int Humidity = map(sensorValue, 400, 1024, 100, 0);
  Serial.println(Humidity);
  delay(1000);
}

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <InfluxDb.h>
#include <Arduino.h>

#define INFLUXDB_HOST "192.168.1.213:8080"
#define INFLUXDB_USER "admin"
#define INFLUXDB_PASS "emperador"
#define WIFI_SSID "WifiSiTo"
#define WIFI_PASS "2210198531011990"

ESP8266WiFiMulti WiFiMulti;
Influxdb influx(INFLUXDB_HOST);

int getHumidity () {
  int sensorValue = analogRead(A0);
  int Humidity = map(sensorValue, 400, 1024, 100, 0);
  return Humidity;
}

void setup() {
  Serial.begin(9600);
  Serial.println(" ### Hello ###");

  WiFiMulti.addAP(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting to WIFI");
  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  influx.setDbAuth("test", INFLUXDB_USER, INFLUXDB_PASS);

  Serial.println("Setup done");
}

void loop() {

  InfluxData row("Humidity");
  row.addTag(getHumidity());
  influx.write(row);

  delay(1000);
}
