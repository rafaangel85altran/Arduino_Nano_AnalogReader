/*
Analog Reader Maceta Nano:

Lee la señal analógica A0 y la mapea para publicarla a 9600 Baudios por puerto serie

*/

#include <Arduino.h>

char Mode = '';

void stateLed(char Mode) {
	if (Mode == 'ComOk') {
		digitalWrite(LED_BUILTIN, HIGH); 	// COM OK = Led always ON
	} else if (Mode == 'ComNok') {
		digitalWrite(LED_BUILTIN, HIGH); 	// COM NOK = Led gives two blinks in 1 sec
		delay(250);
		digitalWrite(LED_BUILTIN, LOW);
		delay(250);
	} else if (Mode == 'Unknow') {
		digitalWrite(LED_BUILTIN, LOW);		//COM Unknow = LED always OFF
	}
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(A0);
  int Humidity = map(sensorValue, 400, 1024, 100, 0);
  Serial.println(Humidity);
  delay(1000);
  void stateLed();
}
