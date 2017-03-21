#include <HaLakeKitFirst.h>
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

const int TONES_12[] = {
  TONE_A3,
  TONE_B3,
  TONE_C4,
  TONE_D4,
  TONE_E4,
  TONE_F4,
  TONE_G4,
  TONE_A4,
  TONE_B4,
  TONE_C5,
  TONE_D5,
  TONE_D6
};

#ifdef USBCON
HaLakeKitFirst kitFirst(&Serial1);
#else
HaLakeKitFirst kitFirst(&Serial);
#endif

int i;
int currentMode;
String kitStr;
int receivedValue;
int soundFrequency;

void setup() {
  kitFirst.begin();
  pinMode(SPEAKER_PIN, OUTPUT);
  for (i=0; i<MODE_NUM; i++) {
    pinMode(MODE_PINS[i], INPUT_PULLUP);
  }
#ifdef DEBUG_MODE
  Serial.begin(HALAKEKITFIRST_SERIAL_SPEED);
#endif
}

void loop() {
  currentMode = getMode();

  if (kitFirst.receive()) {
    soundFrequency = getFrequency(&kitFirst, currentMode);
#ifdef DEBUG_MODE
    Serial.print(kitFirst.getReceivedString());
#endif
  } else {
    soundFrequency = 0;
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

int getFrequency(HaLakeKitFirst* kitFirst, int currentMode) {
  switch(currentMode) {
    case 3:
    return TONES_12[kitFirst->getReceivedValue(0, 11)];
    case 2:
    return TONES_8[kitFirst->getReceivedValue(0, 7)];
    case 1:
    return kitFirst->getReceivedValue(MIN_FREQUENCY, MAX_FREQUENCY/2);
    default: // case 0
    return kitFirst->getReceivedValue(MIN_FREQUENCY, MAX_FREQUENCY);
  }
}

int getLevel(int value, int levelLessThan) {
  return value * (levelLessThan - 1) / 1023;
}
