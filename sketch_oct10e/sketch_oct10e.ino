const int IN1 = 4;
const int PWM1 = 5;
void setup() {
  // put your setup code here, to run once:
  pinMode(IN1, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(PWM1, 0);
  digitalWrite(IN1, LOW);
  delay(1000);
}
