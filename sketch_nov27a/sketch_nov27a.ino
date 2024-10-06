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
// bool tes  = false;

// void send_data() {
//   int analogValue = analogRead(LIGHT_SENSOR_PIN);
//   Serial.print("Analog Value = ");
//   Serial.println(analogValue);

//   // Kirim nilai keadaan cahaya ke Blynk
//   Blynk.virtualWrite(V0, analogValue);

//   if (! && analogValue < 500) {
//     // Kontrol relay otomatis hanya jika tidak dikendalikan secara manual dan dalam keadaan gelap
//     Blynk.virtualWrite(V2, "Gelap");

//     if (digitalRead(RELAY_PIN) == LOW) {
//       digitalWrite(RELAY_PIN, HIGH); 
//       Blynk.virtualWrite(V1, HIGH); 
//     }
//   } else {
//     // Kontrol relay sesuai dengan 
//     if () {
//       Blynk.virtualWrite(V2, "Manual");
//     } else {
//       Blynk.virtualWrite(V2, "Terang");
//     }

//     if (digitalRead(RELAY_PIN) == HIGH) {
//       digitalWrite(RELAY_PIN, LOW);
//       Blynk.virtualWrite(V1, LOW); 
//     }
//   }
// }

void send_data() {
  int analogValue = analogRead(LIGHT_SENSOR_PIN);
  Serial.print("Analog Value = ");
  Serial.println(analogValue);

  Blynk.virtualWrite(V0, analogValue);

  if ( analogValue < 500 || digitalRead(RELAY_PIN) == HIGH) {
      Blynk.virtualWrite(V2, "Gelap");
      digitalWrite(RELAY_PIN, HIGH);  
    } else {
      Blynk.virtualWrite(V2, "Terang");
      digitalWrite(RELAY_PIN, LOW);
      }
}

BLYNK_WRITE(V1) {
  int relayState = param.asInt();
  
  if (relayState == HIGH) {
    digitalWrite(RELAY_PIN, HIGH);
  } else {
    digitalWrite(RELAY_PIN, LOW);
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
  delay(1000);
  Serial.print("Relay State: ");
  Serial.println(digitalRead(RELAY_PIN));
}
