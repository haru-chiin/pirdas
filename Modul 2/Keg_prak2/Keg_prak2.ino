#define LED 2
#define BUZZER 4
int delayDuration = 1000;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

}

void loop() {
  digitalWrite(LED, HIGH);
  digitalWrite(BUZZER, HIGH);
  delay(delayDuration);
  digitalWrite(LED, LOW);
  digitalWrite(BUZZER, LOW);
  delay(delayDuration);

  delayDuration -= 100;
  if (delayDuration < 100) {
    delayDuration = 100;
  }

}
