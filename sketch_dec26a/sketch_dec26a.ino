#include <Wire.h>
#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <MPU6050_tockn.h>

#define echoPin 21
#define trigPin 22
#define buzzerpin 18
#define ledPin 14

const char* ssid = "punyaku";
const char* password = "12345678";
const char* servername = "http://192.168.137.1:8000/?";
long duration, distance;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerpin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting");
  }
  String wifiName = WiFi.SSID();
  String localWifiIP = WiFi.localIP().toString();
  Serial.println();
  Serial.println("Connected to " + wifiName);
  Serial.println("Local IP : " + localWifiIP);
}

void loop() {
  // Mengukur jarak menggunakan sensor ultrasonik
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;
  String disp = String(distance);

  Serial.print("Distance: ");
  Serial.print(disp);
  Serial.println(" cm");

  // Mengontrol buzzer dan lampu berdasarkan jarak
  if (distance < 50) {
    for (int i = 0; i < 50; i++) {
      perulangan();
    }

    // Menambahkan distance ke URL
    String url = servername;
    url += "&distance=";
    url += String(distance);

    HTTPClient http;
    http.begin(url);
    int httpResponseCode = http.GET();
    if (httpResponseCode == 200) {
      Serial.println("Data Sent success");
    } else {
      Serial.print("Error code :");
      Serial.print(httpResponseCode);
    }
    http.end();
  } else {
    digitalWrite(buzzerpin, LOW);
    digitalWrite(ledPin, LOW);
  }

  // Delay untuk membaca sensor secara periodik
  delay(100);
}

void perulangan() {
  digitalWrite(buzzerpin, HIGH);
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(buzzerpin, LOW);
  digitalWrite(ledPin, LOW);
  delay(100);
}
