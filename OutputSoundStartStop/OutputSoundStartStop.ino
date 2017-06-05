#include <HaLakeKitFirst.h>
#include "tones.h"
#define SPEAKER_PIN A0

//#define DEBUG_MODE

#define SOUND_CONTINUE 0
#define SOUND_STOP 1
#define SOUND_PLAY 2
#define SOUND_CHANGE 3

const int TONE_LIST[] = {
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
int baseTone = 1;

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
  int soundAction = SOUND_CONTINUE;

  if (kitFirst.receive()) {
    int receivedValue = kitFirst.getReceivedValue(0, HALAKEKITFIRST_MAX_VALUE);
    if (receivedValue < HALAKEKITFIRST_MAX_VALUE / 3 ) {
      soundAction = SOUND_PLAY;
    } else if (receivedValue < ( HALAKEKITFIRST_MAX_VALUE / 3 ) * 2 ) {
      soundAction = SOUND_STOP;
    } else {
      soundAction = SOUND_CHANGE;
    }
#ifdef DEBUG_MODE
    Serial.println(kitFirst.getReceivedString());
    Serial.println("soundAction: " + String(soundAction));
#endif
  }

  if (isPlaying && soundAction == SOUND_STOP) {
    isPlaying = false;
#ifdef DEBUG_MODE
    Serial.println("stop");
#endif
    tone(SPEAKER_PIN, TONE_LIST[baseTone + 1], 100);
    delay(100);
    tone(SPEAKER_PIN, TONE_LIST[baseTone], 100);
    delay(100);
    tone(SPEAKER_PIN, TONE_LIST[baseTone + 1], 100);
    delay(100);
    tone(SPEAKER_PIN, TONE_LIST[baseTone], 100);
    delay(100);
    tone(SPEAKER_PIN, TONE_LIST[baseTone - 1], 100);
    delay(100);
    //tone(SPEAKER_PIN, TONE_LIST[0], 100);
  } else if (!isPlaying && soundAction == SOUND_CHANGE) {
#ifdef DEBUG_MODE
    Serial.println("change");
#endif
    baseTone ++;
    if (baseTone >= TONES_NUM - 1) {
      baseTone = 1;
    }
    tone(SPEAKER_PIN, TONE_LIST[baseTone], 100);
    delay(100);
  } else if (! isPlaying && soundAction == SOUND_PLAY) {
    isPlaying = true;
#ifdef DEBUG_MODE
    Serial.println("play");
#endif
  }

  if (isPlaying) {
#ifdef DEBUG_MODE
    Serial.println("playing");
#endif
    tone(SPEAKER_PIN, TONE_LIST[baseTone], 100);
    delay(1);
  } else {
#ifdef DEBUG_MODE
    Serial.println("not playing");
#endif
  }
  delay(10);
}

