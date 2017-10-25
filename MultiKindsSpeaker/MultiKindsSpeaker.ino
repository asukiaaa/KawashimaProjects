/***************************************************
  DFPlayer - A Mini MP3 Player For Arduino
  <https://www.dfrobot.com/index.php?route=product/product&product_id=1121>

 ***************************************************
  This example shows the all the function of library for DFPlayer.

  Created 2016-12-07
  By [Angelo qiao](Angelo.qiao@dfrobot.com)

  GNU Lesser General Public License.
  See <http://www.gnu.org/licenses/> for details.
  All above must be included in any redistribution
 ****************************************************/

/***********Notice and Trouble shooting***************
  1.Connection and Diagram can be found here
  <https://www.dfrobot.com/wiki/index.php/DFPlayer_Mini_SKU:DFR0299#Connection_Diagram>
  2.This code is tested on Arduino Uno, Leonardo, Mega boards.
 ****************************************************/

#include "Arduino.h"
#include "SoftwareSerial.h"
#include <DFRobotDFPlayerMini.h>

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

#define TRIG_PIN A1
#define ECHO_PIN A2
#define LED_PIN 8
#define PLAY_CHECK_PIN 9
#define MAX_CHANNEL 3
#define VOLUME_PIN 3
#define VOLUME_ANALOG_MAX 610
#define VOLUME_ANALOG_MIN 0
#define VOLUME_MAX 30
#define VOLUME_MIN 1

uint8_t currentChannel = 1;
uint8_t currentVolume = 15;
boolean playingMusic = false;
unsigned long changedMusicAt = 0;

boolean isPlaying() {
  return (LOW == digitalRead(PLAY_CHECK_PIN));
}

float getDistance(int trig_pin, int echo_pin) {
  float duration = 0;
  float distance = 0;

  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  duration = pulseIn(echo_pin, HIGH);
  duration = duration / 2; // get harf distance
  distance = duration * 340 * 100 / 1000000; // carc with sound speed as 340m/s
  return distance;
}

void setup() {
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(PLAY_CHECK_PIN, INPUT);

  mySoftwareSerial.begin(9600);
  Serial.begin(115200);

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  myDFPlayer.volume(currentVolume);
}

void loop() {
  //Serial.println(getDistance(TRIG_PIN, ECHO_PIN));
  //delay(1000);
  updateLed();
  updatePlayer();
}

void updateLed() {
  if (!isPlaying()) {
    digitalWrite(LED_PIN, LOW);
  } else if (!playingMusic) {
    digitalWrite(LED_PIN, HIGH);
  } else if (millis() / 1000 < 500) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
}

void updatePlayer() {
  static float distance;
  distance = getDistance(TRIG_PIN, ECHO_PIN);
  Serial.print("distance: ");
  Serial.println(distance);
  Serial.print("playing?: ");
  Serial.println(isPlaying());
  // uint8_t candidateVolume = getVolume();

  // if (candidateVolume != currentVolume) {
  //   currentVolume = candidateVolume;
  //   //Serial.println("set volume " + String(candidateVolume));
  //   myDFPlayer.volume(currentVolume);
  // }

  // Keep music for a minimum of 1 sec
  if (millis() - changedMusicAt < 1000) {
    return;
  } else if (isPlaying() && playingMusic) {
    Serial.println("watch to stop");
    if (distance < 40) {
      Serial.println("stop music");
      playingMusic = false;
      myDFPlayer.playFolder(1, 2);
      changedMusicAt = millis();
    }
  } else {
    Serial.println("wait to trigger playing");
    if (distance < 40) {
      currentChannel ++;
      if (currentChannel > MAX_CHANNEL) {
        currentChannel = 1;
      }
      Serial.println("play music");
      myDFPlayer.playFolder(currentChannel, 1);
      playingMusic = true;
      changedMusicAt = millis();
    }
  }
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

