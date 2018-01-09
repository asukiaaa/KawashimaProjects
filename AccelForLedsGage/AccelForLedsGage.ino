#include "MPU9250_asukiaaa.h"

//#define DEBUG_MODE

MPU9250 mySensor;

const int LED_PINS[] = {
  6,
  7,
  8,
  9,
  10,
  16,
  14,
  15,
  A0,
  A1,
  A2,
  A3
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
  accel = 0;
  for (i=0; i<10; i++) {
    mySensor.accelUpdate();
    accel += mySensor.accelX();
    delay(100);
  }
  accel = accel / 10;
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
