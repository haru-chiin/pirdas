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
const String apiKey = "8124123";
const String phone_number = "+6282233955496";
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

  if (distance < 50) {
    for (int i = 0; i < 50; i++) {
      message_to_whatsapp("Someone entered your house!!!");
      perulangan();
    }

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

  delay(100);
}

void perulangan() {
  digitalWrite(buzzerpin, HIGH);
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(buzzerpin, LOW);
  digitalWrite(ledPin, LOW);
}

void message_to_whatsapp(String message) {
  String url = "https://api.callmebot.com/whatsapp.php?phone=" + phone_number + "&apikey=" + apiKey + "&text=" + urlencode(message);
  postData(url);
}

void postData(String url) {
  int httpCode;
  HTTPClient http;
  http.begin(url);
  httpCode = http.GET();
  if (httpCode == 200) {
    Serial.println("Data Sent success");
  } else {
    Serial.print("Error code :");
    Serial.print(httpCode);
  }
  http.end();
}

String urlencode(String str) {
  String encodedString = "";
  char c;
  char code0;
  char code1;
  char code2;
  for (int i = 0; i < str.length(); i++) {
    c = str.charAt(i);
    if (c == ' ') {
      encodedString += '+';
    } else if (isalnum(c)) {
      encodedString += c;
    } else {
      code1 = (c & 0xf) + '0';
      if ((c & 0xf) > 9) {
        code1 = (c & 0xf) - 10 + 'A';
      }
      c = (c >> 4) & 0xf;
      code0 = c + '0';
      if (c > 9) {
        code0 = c - 10 + 'A';
      }
      code2 = '\0';
      encodedString += '%';
      encodedString += code0;
      encodedString += code1;
    }
    yield();
  }
  return encodedString;
}
