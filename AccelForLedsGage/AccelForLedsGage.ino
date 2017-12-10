#include "MPU9250_asukiaaa.h"

//#define DEBUG_MODE

MPU9250 mySensor;

const int LED_PINS[] = {
  4,
  5,
  A1,
  A0,
  6,
  7,
  15,
  14,
  8,
  9,
  16,
  10
};

const int LED_NUM = sizeof(LED_PINS) / sizeof(int);

int i;
int level;
float accel;

void setup() {
  Wire.begin();
  mySensor.setWire(&Wire);
  mySensor.beginAccel();
  for (i=0; i<LED_NUM; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], LOW);
  }
#ifdef DEBUG_MODE
  while(!Serial);
  Serial.begin(115200);
  Serial.println("started debug mode");
#endif
}

void loop() {
  mySensor.accelUpdate();
  accel = mySensor.accelX();
  level = min((max(accel, 0) * 13), 11);
#ifdef DEBUG_MODE
  Serial.println("accel: " + String(accel));
  Serial.println("level: " + String(level));
#endif

  for (i=0; i<LED_NUM; i++) {
    if (level >= i) {
      digitalWrite(LED_PINS[i], HIGH);
    } else {
      digitalWrite(LED_PINS[i], LOW);
    }
  }
}
