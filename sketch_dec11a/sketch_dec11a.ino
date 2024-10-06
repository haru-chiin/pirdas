#define BLYNK_TEMPLATE_ID "TMPL6kd9D-rr2"
#define BLYNK_TEMPLATE_NAME "dht"
#define BLYNK_AUTH_TOKEN "3NIdt19Z9EBInIfarOpZOO1zjdS4zols"
#define BLYNK_PRINT Serial 
#include <DHT.h> 

#define DHT_SENSOR_PIN 33  
#define DHT_SENSOR_TYPE DHT11 
#define BUZZER_PIN 23  

#include <WiFi.h> 
#include <WiFiClient.h> 
#include <BlynkSimpleEsp32.h> 

char auth[] = BLYNK_AUTH_TOKEN; 
char ssid[] = "punyaku"; 
char pass[] = "12345678"; 

BlynkTimer timer; 

DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE); 

void readDHT(){ 
 float humi = dht_sensor.readHumidity(); 
 float tempC = dht_sensor.readTemperature();  
 float tempF = dht_sensor.readTemperature(true); 

 if (isnan(tempC) || isnan(tempF) || isnan(humi)) { 
 Serial.println("Failed to read from DHT sensor!"); 
 } else { 
 Serial.print("Humidity: "); 
 Serial.print(humi); 
 Serial.print("%"); 

 Serial.print(" | "); 

 Serial.print("Temperature: "); 
 Serial.print(tempC); 
 Serial.print("°C ~ "); 
 Serial.print(tempF); 
 Serial.println("°F"); 
 Blynk.virtualWrite(V0, tempC); 
 Blynk.virtualWrite(V1, tempF);
 Blynk.virtualWrite(V2, humi);  

 if (tempC > 32.0) { 
 tone(BUZZER_PIN, 3000); 
 } else if (tempC > 29.0) { 
 tone(BUZZER_PIN, 1000); 
 } else if (tempC > 25.0) { 
 noTone(BUZZER_PIN); 
 } 
 } 
} 

void setup() { 
 delay(800); 
 Serial.begin(115200); 
 Blynk.begin(auth, ssid, pass, "blynk.cloud", 80); 
 timer.setInterval(1000L, readDHT); 
 dht_sensor.begin();
 pinMode(BUZZER_PIN, OUTPUT);
} 

void loop() { 
 Blynk.run(); 
 timer.run(); 
}