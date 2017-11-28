
const int INA = 4;
const int PMW1 = 5;
const int INB = 7;
const int PMW2 = 6;

bool work = true;
int leftOffset = 0;
int rightOffset = 0;
const int offset = 12;

const int value1 = 90;
const int value2 = 90;

#include <NewPing.h>
#define TRIGGER_PIN  11  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     12  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
// sensor pin num

const int sensor[] = {8, 9, 10};
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);


  for (int i = 0; i < 3; ++i) {
    pinMode(sensor[i], INPUT);
  }
}

void loop() {
  // define whether there is something ahead
  work = true;
  /*for (int i = 0; i < 3; ++i) {
    if (digitalRead(sensor[i]) == LOW) {
      work = false;
    }
  }*/
  if (digitalRead(sensor[0]) == LOW) {
   turnBiggerRight();
    turnRight();
  } else if (digitalRead(sensor[2]) == LOW) {
    turnBiggerLeft();
    turnLeft();
  } else if (digitalRead(sensor[1]) == LOW) {
    turnBiggerLeft();
    turnLeft();
  }
  float cm = sonar.ping_cm();
  Serial.println(cm);
  if (cm > 35 || 0 == cm) {
      //leftOffset = offset;
      //rightOffset = 0;
      // forward();
      int times = 1;
      while (times--) {
        turnBiggerRight();
      }
      leftOffset = 10;
      rightOffset = 0;
      
  } else if (cm > 20) {
    leftOffset = 6;
    rightOffset = 0;
  } else if (cm > 17) {
    leftOffset = 4;
    rightOffset = 0;
  } else if (cm > 15) {
    leftOffset = 3;
    rightOffset = 0;
  } else if (cm > 13) {
    leftOffset = 2;
    rightOffset = 0;
  } else if (cm < 1) {
      turnLeft();    
  } else if (cm < 5) {
    leftOffset = 0;
    rightOffset = 6;
  } else if (cm < 8) {
    leftOffset = 0;
    rightOffset = 4;
  } else if (cm < 10) {
    leftOffset = 0;
    rightOffset = 2;
  } else {
    leftOffset = 0;
    rightOffset = 0;
   }
  Serial.println(leftOffset);
  Serial.println(rightOffset);
  if (work) {
    digitalWrite(INA, LOW);
    digitalWrite(INB, HIGH);
    analogWrite(PMW1, value1 + leftOffset);
    analogWrite(PMW2, value2 + rightOffset);
  } else {
    digitalWrite(INA, LOW);
    digitalWrite(INB, HIGH);
    analogWrite(PMW1, 0);
    analogWrite(PMW2, 0);
  }

  delay(50);
}

void turnLeft() {
  while (digitalRead(sensor[1]) == LOW || digitalRead(sensor[2]) == LOW) {
    digitalWrite(INA,HIGH);
    digitalWrite(INB, HIGH);
    analogWrite(PMW1, 0);
    analogWrite(PMW2, 100);
  }
}

void turnRight() {
  while (digitalRead(sensor[1]) == LOW || digitalRead(sensor[0]) == LOW) {
    digitalWrite(INA, LOW);
    digitalWrite(INB, LOW);
    analogWrite(PMW1, 100);
    analogWrite(PMW2, 0);
  }
}

void turnBiggerRight() {
  digitalWrite(INA, LOW);
    digitalWrite(INB, LOW);
    analogWrite(PMW1, 100);
    analogWrite(PMW2, 0);
    delay(70);
}

void turnBiggerLeft() {
    digitalWrite(INA,HIGH);
    digitalWrite(INB, HIGH);
    analogWrite(PMW1, 0);
    analogWrite(PMW2, 100);
    delay(70);
}

void back() {
    digitalWrite(INA, HIGH);
    digitalWrite(INB, LOW);
    analogWrite(PMW1, value1);
    analogWrite(PMW2, value2);
    delay(20);
}

void forward() {
    digitalWrite(INA, LOW);
    digitalWrite(INB, HIGH);
    analogWrite(PMW1, value1);
    analogWrite(PMW2, value2);
    delay(50);
}


