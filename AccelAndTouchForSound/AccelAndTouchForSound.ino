#include <MPU9250_asukiaaa.h>
#include <Adafruit_MPR121.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

#define TOUCH_PIN_NUM 12
#define MAX_CHANNEL 3
#define PLAY_CHECK_PIN 9
#define ACTIVE_BUFF_MS 1000
#define ACCEL_SMALL 1.3
#define ACCEL_LARGE 1.8

MPU9250 mySensor;
Adafruit_MPR121 cap = Adafruit_MPR121();
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX

uint8_t currentChannel = 1;
boolean playingMusic = false;
unsigned long active_at = 0;

void setup() {
  pinMode(PLAY_CHECK_PIN, INPUT);
  Serial.begin(115200);
  //Serial.println("start setup");
  mySoftwareSerial.begin(9600);
  mySensor.begin();
  cap.begin(0x5A);
  //Serial.println("init mp3 player");
  mp3_set_serial(mySoftwareSerial);
  mp3_set_volume(1);
  //Serial.println("finished setup");
}

void loop() {
  static bool isTouched;
  static int touchedPin;

  mySensor.accelUpdate();
  updateTouchStatus(&isTouched, &touchedPin);
  float accel = mySensor.accelSqrt();
  Serial.println(accel);

  // wait ACTIVE_BUFF_MS from last activation
  if ((accel > ACCEL_SMALL || isTouched) &&
      active_at + ACTIVE_BUFF_MS < millis()) {
    Serial.print("active ");
    active_at = millis();
    if ((!isTouched && accel < ACCEL_LARGE) ||
        (isTouched && playingMusic && isPlaying())) {
      Serial.print("stop");
      Serial.print(currentChannel);
      mp3_play_file_in_folder(currentChannel, 2);
      if (isPlaying() && playingMusic) {
        currentChannel = getNextChannel(currentChannel);
      }
      playingMusic = false;
    } else {
      Serial.print("play ");
      Serial.println(currentChannel);
      playingMusic = true;
      mp3_play_file_in_folder(currentChannel, 1);
    }
  }

  delay(100);
}

uint8_t getNextChannel(uint8_t channel) {
  channel ++;
  if (channel > MAX_CHANNEL) {
    channel = 1;
  }
  return channel;
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

