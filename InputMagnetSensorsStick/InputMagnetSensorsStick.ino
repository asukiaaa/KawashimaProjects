#include "HaLakeKitFirstConnector.h"

const unsigned long SENSE_TIME_BUFF_MILLIS = 50;
const int MAGNET_PINS[] = {9,8,7,6,5,4,3,2};
const int MAGNET_NUM = sizeof(MAGNET_PINS)/sizeof(int);
int i;

bool isSensing  = false;
unsigned long sensingFrom = 0;
int sensingPin;
int valueToSend;

HaLakeKitFirstConnector kitConnector(&Serial1);

void setup() {
  //Serial.begin(115200);
  kitConnector.begin();
  for (i=0; i<MAGNET_NUM; i++) {
    pinMode(MAGNET_PINS[i], INPUT_PULLUP);
  }
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
    valueToSend = 1023 * sensingPin / (MAGNET_NUM - 1);
    kitConnector.sendValue(valueToSend);
  }
  //Serial.println(MAGNET_NUM);
  //Serial.println(sensingPin);
  //Serial.println(isSensing);
  //Serial.println("");
  delay(50);
}
