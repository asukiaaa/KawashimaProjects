#include "HaLakeKitFirst.h"

//#define DEBUG_MODE

HaLakeKitFirst kitFirst(&Serial1);

const int LED_PINS[] = {
  3,
  5,
  6,
  9,
};

const int LED_NUM = (sizeof(LED_PINS) / sizeof(int));

int i;
int level = 0;

void setup() {
  kitFirst.begin();
  for (i=0; i<LED_NUM; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], LOW);
  }
#ifdef DEBUG_MODE
  while(!Serial);
  Serial.begin(115200);
  Serial.println("started in DEBUG_MODE");
#endif
}

void loop() {
  if (kitFirst.receive()) {
    level = kitFirst.getReceivedValue(0, LED_NUM*2 + 2);
#ifdef DEBUG_MODE
    Serial.println("level: " + String(level));
#endif
  }

  //Serial.println("level: " + String(level));
  //Serial.println(millis());
  brightLED(level);
  //delay(10);
}

void brightLED(int level) {
  static bool ledStatus[LED_NUM];

  if (level == 0) {
    for (i=0; i<LED_NUM; i++) {
      ledStatus[i] = false;
    }
  } else if (level <= LED_NUM) {
    for (i=0; i<LED_NUM; i++) {
      ledStatus[i] = (i == level -1);
    }
  } else if (level <= LED_NUM*2) {
    int target = level - LED_NUM - 1;
    for (i=0; i<LED_NUM; i++) {
      ledStatus[i] = !(i == target);
    }
  } else {
    for (i=0; i<LED_NUM; i++) {
      ledStatus[i] = true;
    }
  }

  for (i=0; i<LED_NUM; i++) {
    if (ledStatus[i]) {
      digitalWrite(LED_PINS[i], HIGH);
    } else {
      digitalWrite(LED_PINS[i], LOW);
    }
  }
}

