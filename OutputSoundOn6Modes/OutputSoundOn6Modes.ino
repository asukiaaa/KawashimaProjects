#include <HaLakeKitFirstConnector.h>
#define SPEAKER_PIN 10

HaLakeKitFirstConnector kitConnector(&Serial);

const int MODE_PINS[] = {2,3,4,5,6,7};
const int MODE_NUM = sizeof(MODE_PINS)/sizeof(int);
int i;
int currentMode;
String kitStr;
int receivedValue;
int soundFrequency;

#define MIN_FREQUENCY 100
#define MAX_FREQUENCY 1000

void setup() {
  pinMode(SPEAKER_PIN, OUTPUT);
  for (i=0; i<MODE_NUM; i++) {
    pinMode(MODE_PINS[i], INPUT_PULLUP);
  }
s}

void loop() {
  kitStr = kitConnector.waitLine();
  receivedValue = kitConnector.valueFromLine(kitStr);
  currentMode = getMode();

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
    case 1:
    return map(receivedValue, 0, 1023, MIN_FREQUENCY, MAX_FREQUENCY/2);
    default: // case 0
    return map(receivedValue, 0, 1023, MIN_FREQUENCY, MAX_FREQUENCY);
  }
}
