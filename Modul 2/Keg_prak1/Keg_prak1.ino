int sensorValue;
void setup() {
  Serial.begin(9600);
  delay(100);

}

void loop() {
  sensorValue = analogRead(4);
  Serial.println(sensorValue);
  delay(100);

}
