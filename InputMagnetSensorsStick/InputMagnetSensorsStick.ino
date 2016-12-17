#include "HaLakeKitFirstConnector.h"

const unsigned long SENSE_TIME_BUFF_MILLIS = 50;
const int MAGNET_PINS[] = {2,3,4,5,6,7,8,9};
const int MAGNET_VALS[] = {100, 200, 300, 400, 500, 600, 700, 800, 900};
const int MAGNET_NUM = sizeof(MAGNET_PINS)/sizeof(int);
int i;

bool isSensing  = false;
unsigned long sensingFrom = 0;
int sensingPin;

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
    kitConnector.sendValue(MAGNET_VALS[sensingPin]);
  }
  //Serial.println(MAGNET_NUM);
  //Serial.println(sensingPin);
  //Serial.println(isSensing);
  //Serial.println("");
  delay(50);
}
