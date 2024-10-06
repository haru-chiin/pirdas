#define soil_moisture_pin 4

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Serial.println(analogRead(soil_moisture_pin));
  mois();
  delay(10000);
}

void mois(){
  int val = analogRead(soil_moisture_pin);
  int soilmoisturepercent = map(val, 4095, 0, 0, 100);
  // itoa(soilmoisturepercent, soilMoistureStr, 10);
  
  Serial.print("Nilai analog = ");
  Serial.println(val);

  Serial.print("Presentase kelembaban tanah= ");
  Serial.print(soilmoisturepercent);
  Serial.println("% ");
  delay(500);
}