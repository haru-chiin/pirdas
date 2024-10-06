#include <Arduino.h>

const int LDRPin = 35; 
const int darkLED = 25;
const int dimLED = 33;
const int brightLED = 32;
const int buzzerPin = 27;

void setup() {
  pinMode(darkLED, OUTPUT);
  pinMode(dimLED, OUTPUT);
  pinMode(brightLED, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(LDRPin);
  Serial.println(sensorValue);

  if (sensorValue < 500) {
    analogWrite(darkLED, 0);
    analogWrite(dimLED, 0); 
    analogWrite(brightLED, 255); 
    digitalWrite(buzzerPin, HIGH);
    Serial.println("Gelap");
  } else if (sensorValue >= 500 && sensorValue < 1000) {
    // Cahaya redup
    analogWrite(darkLED, 0); 
    analogWrite(dimLED, 255); 
    analogWrite(brightLED, 0); 
    digitalWrite(buzzerPin, LOW);
    Serial.println("Sedang");
  } else {
    // Cahaya terang
    analogWrite(darkLED, 255); 
    analogWrite(dimLED, 0); 
    analogWrite(brightLED, 0); 
    digitalWrite(buzzerPin, LOW);
    Serial.println("Terang");
  }
}
