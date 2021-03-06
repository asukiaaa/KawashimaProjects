#include <MPU9250_asukiaaa.h>
#include <Adafruit_MPR121.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

#define TOUCH_PIN_NUM 12
#define MAX_CHANNEL 3
#define PLAY_CHECK_PIN 9
#define STATE_BUFF_MS 1000
#define VOLUME_PIN 3
#define VOLUME_ANALOG_MAX 610
#define VOLUME_ANALOG_MIN 0
#define VOLUME_MAX 30
#define VOLUME_MIN 1

MPU9250 mySensor;
Adafruit_MPR121 cap = Adafruit_MPR121();
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

uint8_t currentChannel = 1;
uint8_t currentVolume = 1;
boolean playingMusic = false;
unsigned long change_state_at = 0;

void setup() {
  pinMode(PLAY_CHECK_PIN, INPUT);
  Serial.begin(115200);
  //Serial.println("start setup");
  mySoftwareSerial.begin(9600);
  Wire.begin();
  mySensor.setWire(&Wire);
  mySensor.beginAccel();
  cap.begin(0x5A);

  if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  myDFPlayer.volume(currentVolume);
}

void loop() {
  uint8_t candidateVolume = getVolume();
  static bool isTouched;
  static int touchedPin;

  if (candidateVolume != currentVolume) {
    currentVolume = candidateVolume;
    //Serial.println("set volume " + String(candidateVolume));
    myDFPlayer.volume(currentVolume);
  }

  mySensor.accelUpdate();
  updateTouchStatus(&isTouched, &touchedPin);
  float accelX = -mySensor.accelX();
  //Serial.println(accel);

  // wait STATE_BUFF_MS from last state changing
  if (change_state_at + STATE_BUFF_MS < millis()) {
    if (playingMusic && isPlaying() && (accelX < -0.8 || isTouched)) {
      change_state_at = millis();
      Serial.println("stop music and play short sound " + String(currentChannel));
      playingMusic = false;
      myDFPlayer.playFolder(currentChannel, 2);
      currentChannel = getNextChannel(currentChannel);
    } else if (!playingMusic && (-0.7 < accelX || isTouched)) {
      change_state_at = millis();
      Serial.println("play music " + String(currentChannel));
      playingMusic = true;
      myDFPlayer.playFolder(currentChannel, 1);
    }
  }

  delay(100);
}

int getVolume() {
  int analogValue = analogRead(VOLUME_PIN);
  int volume =
    (analogValue - VOLUME_ANALOG_MIN)
    * (VOLUME_MAX - VOLUME_MIN)
    / (VOLUME_ANALOG_MAX - VOLUME_ANALOG_MIN)
    + VOLUME_MIN;
  volume = max(volume, VOLUME_MIN);
  volume = min(volume, VOLUME_MAX);
  //Serial.println(volume);
  return volume;
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

