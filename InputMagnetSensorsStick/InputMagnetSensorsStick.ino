#include "HaLakeKitFirst.h"
//#define DEBUG_MODE

const unsigned long SENSE_TIME_BUFF_MILLIS = 50;
const int MAGNET_PINS[] = {9,8,7,6,5,4,3,2};
const int MAGNET_NUM = sizeof(MAGNET_PINS)/sizeof(int);
int i;

bool isSensing  = false;
unsigned long sensingFrom = 0;
int sensingPin;

HaLakeKitFirst kitFirst(&Serial1);

void setup() {
  kitFirst.begin();
  for (i=0; i<MAGNET_NUM; i++) {
    pinMode(MAGNET_PINS[i], INPUT_PULLUP);
  }
#ifdef DEBUG_MODE
  while (!Serial);
  Serial.begin(115200);
#endif
}

void loop() {
  isSensing = false;
  for (i=0; i<MAGNET_NUM; i++) {
    if (digitalRead(MAGNET_PINS[i]) == LOW) {
      isSensing = true;
      if (sensingPin != i) {
        sensingPin = i;
        sensingFrom = millis();
      }
      break;
    }
  }
  if (isSensing && sensingFrom > SENSE_TIME_BUFF_MILLIS) {
    kitFirst.sendValue(sensingPin, 0, MAGNET_NUM - 1);
#ifdef DEBUG_MODE
    Serial.println("sendingPin: " + String(sensingPin));
    Serial.println("valueToSend: " + String(valueToSend));
    Serial.println("");
#endif
  }
  delay(50);
}
