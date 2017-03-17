#include "HaLakeKitFirst.h"

//#define DEBUG_MODE

HaLakeKitFirst kitFirst(&Serial1);

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

void setup() {
  kitFirst.begin();
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
  if (kitFirst.receive()) {
    level = kitFirst.getReceivedValue(0, LED_NUM - 1);
#ifdef DEBUG_MODE
    Serial.println("level: " + String(level));
#endif
  }

  for (i=0; i<LED_NUM; i++) {
    if (level >= i) {
      digitalWrite(LED_PINS[i], HIGH);
    } else {
      digitalWrite(LED_PINS[i], LOW);
    }
  }
}
