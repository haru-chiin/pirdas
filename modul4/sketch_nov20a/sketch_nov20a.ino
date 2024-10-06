#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <MPU6050_tockn.h>
#include <Wire.h>

#define BUZZER_PIN 23
#define LED 18

MPU6050 mpu6050(Wire);

const char* ssid = "punyaku";
const char* password = "12345678";
const char* servername = "http://192.168.137.1:8000/?";

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets();
  pinMode(LED, OUTPUT);

  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.println("Connecting");
  }
  String wifiName = WiFi.SSID();
  String localWifiIP = WiFi.localIP().toString();
  Serial.println( );
  Serial.println("Connected to " + wifiName);
  Serial.println("Local IP : " + localWifiIP);
}

void loop() {
  mpu6050.update();
  float angleX, angleY, angleZ;
 
  angleX = mpu6050.getAngleX();
  angleY = mpu6050.getAngleY();
  angleZ = mpu6050.getAngleZ();

  Serial.print("Sudut X: ");
  Serial.println(angleX);

  Serial.print("Sudut Y: ");
  Serial.println(angleY);

  Serial.print("Sudut Z: ");
  Serial.println(angleZ);

  if (angleX > 10) {
    Serial.println("Arah: Kanan");
    tone(BUZZER_PIN, 1000, 500);
    digitalWrite(LED, LOW); 
  } else if (angleX < -10) {
    Serial.println("Arah: Kiri");
    tone(BUZZER_PIN, 1000, 500);
    digitalWrite(LED, LOW); 
  } else if (angleY > 10) {
    Serial.println("Arah: Belakang");
    tone(BUZZER_PIN, 1000, 500);
    digitalWrite(LED, LOW); 
  } else if (angleY < -10) {
    Serial.println("Arah: Depan");
    tone(BUZZER_PIN, 1000, 500);
    digitalWrite(LED, LOW); 
  } else {
    Serial.println("Tidak ada perubahan arah.");
    tone(BUZZER_PIN, 0, 0);
    digitalWrite(LED, HIGH);
  }

  // delay(1000);

  String url = servername;
  url += "&angleX=";
  url += String(angleX);
  url += "&angleY=";
  url += String(angleY);
  url += "&angleZ=";
  url += String(angleZ);

  HTTPClient http;
  http.begin(url);
  int httpResponseCode = http.GET();
  if (httpResponseCode == 200) {
    Serial.println("Data Sent success");
  } else{
    Serial.print("Error code :");
    Serial.print(httpResponseCode);
  }
  http.end();
  // delay(1000);
}
