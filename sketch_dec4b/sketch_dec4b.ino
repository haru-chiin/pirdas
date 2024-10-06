#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_TEMPLATE_ID "TMPL6kBgdRalz"
#define BLYNK_TEMPLATE_NAME "tes"
#define BLYNK_AUTH_TOKEN "mr9BcQVA_RAXwUJbMA5JV1jy2JX8KqgL"
#define LIGHT_SENSOR_PIN 34
#define RELAY_PIN 33

BlynkTimer timer;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "punyaku";
char pass[] = "12345678";
int manualControlStatus = 0;
int relayStatus = 0;

void send_data() {
  int analogValue = analogRead(LIGHT_SENSOR_PIN);
  Serial.print("Analog Value = ");
  Serial.println(analogValue);
  
  if (manualControlStatus == HIGH) {
    if (relayStatus == HIGH) {
      Blynk.virtualWrite(V2, "Lampu Menyala");
      if (digitalRead(RELAY_PIN) == LOW) {
        digitalWrite(RELAY_PIN, HIGH);
      }
    } else {
      Blynk.virtualWrite(V2, "Lampu Mati");
      if (digitalRead(RELAY_PIN) == HIGH) {
        digitalWrite(RELAY_PIN, LOW);
      }
    }
  } else {
    Blynk.virtualWrite(V0, analogValue);
    if (analogValue < 500) {
    Blynk.virtualWrite(V2, "Gelap");

    if (digitalRead(RELAY_PIN) == LOW) {
      digitalWrite(RELAY_PIN, HIGH);
      Blynk.virtualWrite(V1, HIGH);
    }
  } else {
    Blynk.virtualWrite(V2, "Terang");

    if (digitalRead(RELAY_PIN) == HIGH) {
      digitalWrite(RELAY_PIN, LOW);
      Blynk.virtualWrite(V1, LOW);
    }
  }
  }
}


void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, LOW);
  
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  timer.setInterval(1000L, send_data);
}

void loop() {
  Blynk.run();
  timer.run();
  Serial.print("Relay State: ");
  Serial.println(digitalRead(RELAY_PIN));
}

BLYNK_WRITE(V1) {
  relayStatus = param.asInt();
}

BLYNK_WRITE(V3) {
  manualControlStatus = param.asInt();
}