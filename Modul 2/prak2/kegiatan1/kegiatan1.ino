#include <Arduino.h>

const int LDRPin = 35;
const int darkLED = 25;
const int dimLED = 33;
const int brightLED = 32;

void setup() {
  pinMode(darkLED, OUTPUT);
  pinMode(dimLED, OUTPUT);
  pinMode(brightLED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(LDRPin);
  Serial.println(sensorValue);

  if (sensorValue < 500) {
    // Cahaya gelap
    digitalWrite(darkLED, HIGH);
    digitalWrite(dimLED, LOW);
    digitalWrite(brightLED, LOW);
  } else if (sensorValue >= 500 && sensorValue < 1000) {
    // Cahaya redup
    digitalWrite(darkLED, LOW);
    digitalWrite(dimLED, HIGH);
    digitalWrite(brightLED, LOW);
  } else {
    // Cahaya terang
    digitalWrite(darkLED, LOW);
    digitalWrite(dimLED, LOW);
    digitalWrite(brightLED, HIGH);
  }
}
