/*
Analog Reader Maceta Nano:

v0.1: Lee la se�al anal�gica A0 y la mapea para publicarla a 9600 Baudios por puerto serie
v0.2: Envia la humedad por UDP a traves de la red de casa al server InfluxDB

*/
void loop() {
  int sensorValue = analogRead(A0);
  int Humidity = map(sensorValue, 400, 1024, 100, 0);
  Serial.println(Humidity);
  delay(1000);
}


#include <Arduino.h>
#include <SPI.h>
#include <WiFi.h>
#include <WiFiUDP.h>

char ssid[] = "WifiSiTo";     			 //  your network SSID (name)
char pass[] = "2210198531011990";    // your network password
int status = WL_IDLE_STATUS;     		 // the Wifi radio's status

// the IP address of your InfluxDB host
byte host[] = {192, 168, 1, 213};

// the port that the InfluxDB UDP plugin is listening on
int port = 8080;

WiFiUDP udp;

void setup() {
  // initialize serial port
  Serial.begin(9600);

  // attempt to connect using WPA2 encryption
  Serial.println("Attempting to connect to WPA network...");
  status = WiFi.begin(ssid, pass);

  // if unable to connect, halt
  if ( status != WL_CONNECTED) {
    Serial.println("Couldn't get a WiFi connection");
    while(true);
  }
  // if the conneciton succeeded, print network info
  else {
    Serial.println("Connected to network");
    // print your WiFi shield's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    // print the received signal strength:
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
  }
}

void loop() {
  String line, temperature;

  // get the current temperature from the sensor, to 2 decimal places
  //temperature = String(getTemperature(), 2);

  // concatenate the temperature into the line protocol
  //line = String("temperature value=" + temperature);
  //Serial.println(line);

	int sensorValue = analogRead(A0);
	int Humidity = map(sensorValue, 400, 1024, 100, 0);

  // send the packet
  Serial.println("Sending UDP packet...");
  udp.beginPacket(host, port);
  Serial.println("Humidity= ");
	Serial.println(Humidity);
  udp.print(line);
  udp.endPacket();
  delay(1000);
}
