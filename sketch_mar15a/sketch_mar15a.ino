#define POWER 32
#define SENSOR 34

void setup() {
  // put your setup code here, to run once:
  pinMode(POWER, OUTPUT);
  digitalWrite(POWER, LOW);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead(SENSOR);
  // Serial.print("Output: ");
  // Serial.println(val);
  Serial.print("Pesentase: ");
  Serial.print(map(val, 4095, 0, 0, 100));
  Serial.println("%");
  // Serial.println(readSensor());

  delay(1000);
}

int readSensor() {
  digitalWrite(POWER, HIGH);
  delay(10);
  int val = analogRead(SENSOR);
  digitalWrite(POWER, LOW);
  return val;
}