#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

const int ldrPin = 15;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets();
  pinMode(ldrPin, INPUT);
}

void loop() {
  mpu6050.update();

  float sumbux = mpu6050.getAngleX();
  float sumbuy = mpu6050.getAngleY();

  Serial.print("angleX : ");
  Serial.print(sumbux);
  Serial.print("\tangleY : ");
  Serial.println(sumbuy);

  if (sumbux > 10) {
    Serial.println("\t\t\t\t\tSensor Miring Kanan");
  } else if (sumbux < -10) {
    Serial.println("\t\t\t\t\tSensor Miring Kiri");
  }

  if (sumbuy > 10) {
    Serial.println("\t\t\t\t\tSensor Miring Depan");
  } else if (sumbuy < -10) {
    Serial.println("\t\t\t\t\tSensor Miring Belakang");
  }

  // int sensorValue = analogRead(ldrPin);
  // Serial.print("\t\t\t\t\t\t\t\t\t\tLDR Value: ");
  // Serial.println(sensorValue);

  // if (sensorValue < 50) {
  //   Serial.println("\t\t\t\t\t\t\t\t\t\tCahaya Gelap");
  // } else if (sensorValue >= 50 && sensorValue < 500) {
  //   Serial.println("\t\t\t\t\t\t\t\t\t\tCahaya Redup");
  // } else if (sensorValue >= 500 && sensorValue < 2000) {
  //   Serial.println("\t\t\t\t\t\t\t\t\t\tCahaya Terang");
  // } else {
  //   Serial.println("\t\t\t\t\t\t\t\t\t\tSangat Terang");
  // }

  // delay(1000);
}