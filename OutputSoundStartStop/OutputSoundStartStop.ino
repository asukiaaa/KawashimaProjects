#include <HaLakeKitFirst.h>

#include "tones.h"
#define SPEAKER_PIN A0

//#define DEBUG_MODE

#define MIN_FREQUENCY 50
#define MAX_FREQUENCY 1000

const int TONE_LIST[] = {
  TONE_B4,
  TONE_C4,
  TONE_D4,
  TONE_E4,
  TONE_F4,
  TONE_G4,
  TONE_A4,
  TONE_B4,
  TONE_C5,
  TONE_D5,
  TONE_E5,
  TONE_F5,
  TONE_G5,
  TONE_A5,
  TONE_B5,
  TONE_C6,
  TONE_D6
};

const int TONES_NUM = sizeof(TONE_LIST)/sizeof(int);

bool requestedToStop = false;
bool requestedToPlay = false;
bool requestedToChange = false;

bool isPlaying = false;
int playMode = 0;
const int MAX_PLAY_MODE = 2;

#ifdef USBCON
HaLakeKitFirst kitFirst(&Serial1);
#else
HaLakeKitFirst kitFirst(&Serial);
#endif

void setup() {
  kitFirst.begin();
  pinMode(SPEAKER_PIN, OUTPUT);
#ifdef DEBUG_MODE
  while(!Serial);
  Serial.begin(HALAKEKITFIRST_SERIAL_SPEED);
  Serial.println("started debugmode");
#endif
  //Scheduler.startLoop(loop1);
}

void loop() {
  if (kitFirst.receive()) {
    int receivedValue = kitFirst.getReceivedValue(0, HALAKEKITFIRST_MAX_VALUE);
    int soundMode = 2;
    if (receivedValue < HALAKEKITFIRST_MAX_VALUE / 3 ) {
      soundMode = 0;
    } else if (receivedValue < ( HALAKEKITFIRST_MAX_VALUE / 3 ) * 2 ) {
      soundMode = 1;
    }
#ifdef DEBUG_MODE
    Serial.print(kitFirst.getReceivedString());
    Serial.print(soundMode);
#endif
    if (soundMode == 0) {
      requestedToChange = true;
    } else if (soundMode == 1) {
      requestedToStop = true;
    } else {
      requestedToPlay = true;
    }
  }

  if (isPlaying && requestedToStop) {
#ifdef DEBUG_MODE
    Serial.println("stop");
#endif
    isPlaying = false;
    requestedToStop = false;
    tone(SPEAKER_PIN, TONE_LIST[0], 100);
    delay(100);
    tone(SPEAKER_PIN, TONE_LIST[0], 100);
  } else if (requestedToChange) {
    requestedToChange = false;
#ifdef DEBUG_MODE
    Serial.println("change");
#endif
    playMode ++;
    if (playMode > MAX_PLAY_MODE) {
      playMode = 0;
    }
  } else if (requestedToPlay) {
    requestedToPlay = false;
#ifdef DEBUG_MODE
    Serial.println("play");
#endif
    tone(SPEAKER_PIN, TONE_LIST[0], 500);
  } if (isPlaying) {
#ifdef DEBUG_MODE
    Serial.println("play");
#endif
    tone(SPEAKER_PIN, TONE_LIST[1], 10);
    delay(500);
  } else {
#ifdef DEBUG_MODE
    Serial.println("none");
#endif
    delay(500);
  }
  delay(100);
}

void loop1() {
#ifdef DEBUG_MODE
  Serial.println("in loop1");
#endif
  if (kitFirst.receive()) {
    int soundMode = kitFirst.getReceivedValue(0, 2);
    Serial.println(soundMode);
#ifdef DEBUG_MODE
    Serial.print(kitFirst.getReceivedString());
    Serial.print(soundMode);
#endif
    if (soundMode == 0) {
      requestedToChange = true;
    } else if (soundMode == 1) {
      requestedToStop = true;
    } else {
      requestedToPlay = true;
    }
  }
  Serial.println("end loop1");
  delay(10);
  yield();
}

