#include <MPU9250_asukiaaa.h>
#include <Adafruit_MPR121.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

#define TOUCH_PIN_NUM 12
#define MAX_CHANNEL 3
#define PLAY_CHECK_PIN 9

MPU9250 mySensor;
Adafruit_MPR121 cap = Adafruit_MPR121();
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX

uint8_t currentChannel = 1;
boolean playingMusic = false;

void setup() {
  pinMode(PLAY_CHECK_PIN, INPUT);
  Serial.begin(115200);
  mySoftwareSerial.begin(9600);
  mySensor.begin();
  cap.begin(0x5A);
  mp3_set_serial(mySoftwareSerial);
  mp3_set_volume(15);
}

void loop() {
  static bool isTouched;
  static int touchedPin;

  mySensor.accelUpdate();
  updateTouchStatus(&isTouched, &touchedPin);

  if (mySensor.accelSqrt() > 1.5 || isTouched) {
    if (isPlaying() && playingMusic) {
      playingMusic = false;
      mp3_play_file_in_folder(currentChannel, 2);
      updateChannel(&currentChannel);
    } else {
      playingMusic = true;
      mp3_play_file_in_folder(currentChannel, 1);
    }
  }

  delay(100);
}

void updateChannel(uint8_t* channel) {
  *channel ++;
  if (*channel > MAX_CHANNEL) {
    *channel = 1;
  }
}

boolean isPlaying() {
  return (LOW == digitalRead(PLAY_CHECK_PIN));
}

void updateTouchStatus(bool* isTouched, int* touchedPin) {
  static uint16_t lasttouched = 0;
  static uint16_t currtouched = 0;
  currtouched = cap.touched();
  *isTouched = false;

  for (uint16_t i=0; i<TOUCH_PIN_NUM; i++) {
    bool touched = currtouched & _BV(i);
    if (touched) {
      *touchedPin = i;
      *isTouched = true;
      break;
    }
  }

  lasttouched = currtouched;
}

