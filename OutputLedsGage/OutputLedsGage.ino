#include "HaLakeKitFirstConnector.h"

//#define DEBUG_MODE

HaLakeKitFirstConnector kitConnector(&Serial1);

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

String kitStr;
int receivedValue;

void setup() {
  kitConnector.begin();
  for (i=0; i<LED_NUM; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], LOW);
  }
#ifdef DEBUG_MODE
  Serial.begin(115200);
#endif
}

void loop() {
  kitStr = kitConnector.waitLine();
  receivedValue = kitConnector.valueFromLine(kitStr);
  level = receivedValue * LED_NUM / 1023;

  for (i=0; i<LED_NUM; i++) {
    if (level >= i) {
      digitalWrite(LED_PINS[i], HIGH);
    } else {
      digitalWrite(LED_PINS[i], LOW);
    }
  }
}

#ifdef DEBUG_MODE
  Serial.println("receivedValue: " + String(receivedValue));
  Serial.println("level: " + String(level));
#endif
