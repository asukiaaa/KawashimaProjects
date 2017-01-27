#include <HaLakeKitFirstConnector.h>
#include "tones.h"
#define SPEAKER_PIN 10

//#define DEBUG_MODE

#define MIN_FREQUENCY 50
#define MAX_FREQUENCY 1000

const int MODE_PINS[] = {2,3,4,5,6,7};
const int MODE_NUM = sizeof(MODE_PINS)/sizeof(int);

const int TONES_8[] = {
  TONE_C4,
  TONE_D4,
  TONE_E4,
  TONE_F4,
  TONE_G4,
  TONE_A4,
  TONE_B4,
  TONE_C5
};

const int TONES_10[] = {
  TONE_B3,
  TONE_C4,
  TONE_D4,
  TONE_E4,
  TONE_F4,
  TONE_G4,
  TONE_A4,
  TONE_B4,
  TONE_C5,
  TONE_D5
};

#ifdef USBCON
HaLakeKitFirstConnector kitConnector(&Serial1);
#else
HaLakeKitFirstConnector kitConnector(&Serial);
#endif

int i;
int currentMode;
String kitStr;
int receivedValue;
int soundFrequency;

void setup() {
  kitConnector.begin();
  pinMode(SPEAKER_PIN, OUTPUT);
  for (i=0; i<MODE_NUM; i++) {
    pinMode(MODE_PINS[i], INPUT_PULLUP);
  }
#ifdef DEBUG_MODE
  Serial.begin(HALAKEKITFIRST_SERIAL_SPEED);
#endif
}

void loop() {
  kitStr = kitConnector.waitLine();
  receivedValue = kitConnector.valueFromLine(kitStr);
  currentMode = getMode();

#ifdef DEBUG_MODE
  Serial.print(kitStr);
#endif

  if (receivedValue < 0) {
    soundFrequency = 0;
  } else {
    soundFrequency = calcFrequency(receivedValue, currentMode);
  }

  tone(SPEAKER_PIN, soundFrequency, 100);
  delay(1);
}

int getMode() {
  for (i=0; i<MODE_NUM; i++) {
    if (digitalRead(MODE_PINS[i]) == LOW) {
      return i;
    }
  }
  return -1;
}

int calcFrequency(int receivedValue, int currentMode) {
  switch(currentMode) {
    case 3:
    return getLevel(receivedValue, 10);
    case 2:
    return getLevel(receivedValue, 8);
    case 1:
    return map(receivedValue, 0, 1023, MIN_FREQUENCY, MAX_FREQUENCY/2);
    default: // case 0
    return map(receivedValue, 0, 1023, MIN_FREQUENCY, MAX_FREQUENCY);
  }
}

int getLevel(int value, int levelLessThan) {
  return value * (levelLessThan - 1) / 1023;
}
