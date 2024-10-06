#define LED 18

void blink(int waktu){
  digitalWrite(LED,LOW);
  delay(waktu);
  digitalWrite(LED,HIGH);
  delay(waktu);
}

void setup() {
  pinMode (LED, OUTPUT);
}

void loop() {
  blink(1000);
}
