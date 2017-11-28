int sensors[3];
int INA = 4;
int PWMA = 5;
int INB = 7;
int PWMB = 6;
void motospd(int spdL, int spdR);

int base = 90;
int offset = 30;
bool whetherOut = false;
void setup() {
  // put your setup code here, to run once:
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10,INPUT);
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensors[0] = digitalRead(8);
  sensors[1] = digitalRead(9);
  sensors[2] = digitalRead(10);
  for (int i = 0; i < 3; ++i) {
    Serial.print(sensors[i]);
  }
  Serial.println();
  // 0--find path
  // 1--no path
  int option = 0;
  option += 1 * sensors[0];
  option += 2 * sensors[1];
  option += 4 * sensors[2];
  switch (option) {
    case 0:
      // 000
      if (whetherOut) {
        motospd(base, 0);
        delay(100);
        whetherOut = false;
      }
      motospd(base, base);
      break;
    case 1:
      // 001
      motospd(base - offset, base + offset);
      break;
    case 2:
      // 010
      motospd(base - offset, base + offset);
      break;
    case 3:
      motospd(0, base);
      keepTurn(sensors[0], sensors[1], sensors[2]);
      // 011
      break;
    case 4:
      // 100
      motospd(base + offset, base - offset);
      break;
    case 5:
      // 101
      motospd(base, base);
      break;
    case 6:
      // 110
      motospd(base, 0);
      keepTurn(sensors[0], sensors[1], sensors[2]);
      break;
    case 7:
      // 111
      motospd(base, 0);
      whetherOut = true;
      break;
  }
  delay(20);
}
void motospd(int spdL, int spdR) {
 if (spdR > 0) {
  digitalWrite(INA, LOW); 
 } else {
  digitalWrite(INA, HIGH);
 }
 if (spdL > 0) {
  digitalWrite(INB, HIGH);
  
 } else {
  digitalWrite(INB, LOW);
 }
 analogWrite(PWMA, abs(0));
 analogWrite(PWMB, abs(0));
}

void keepTurn(int s1, int s2, int s3) {
  while (digitalRead(8) == s1 && digitalRead(9) == s2 && digitalRead(10) == s3) {
    delay(10);
    }
}

