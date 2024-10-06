const int switchPin = 15;
const int ledPin = 4;
int switchState = 0;

void blink(int waktu){
  digitalWrite(ledPin,LOW);
  delay(waktu);
  digitalWrite(ledPin,HIGH);
  delay(waktu);
}

void setup() {
  Serial.begin(115200); 
  pinMode(switchPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  switchState = digitalRead(switchPin);
  if (switchState == HIGH ){
    blink(100);
  } else {
    digitalWrite(ledPin,LOW);
  }
}
