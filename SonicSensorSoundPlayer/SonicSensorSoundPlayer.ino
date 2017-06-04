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
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

#define TRIG1_PIN A1
#define ECHO1_PIN A2
#define TRIG2_PIN A3
#define ECHO2_PIN A4
#define PLAY_CHECK_PIN 9
#define MAX_CHANNEL 2

uint8_t currentChannel = 1;
boolean playingMusic = false;

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
  pinMode(ECHO1_PIN, INPUT);
  pinMode(TRIG1_PIN, OUTPUT);
  pinMode(ECHO2_PIN, INPUT);
  pinMode(TRIG2_PIN, OUTPUT);
  pinMode(PLAY_CHECK_PIN, INPUT);

  mySoftwareSerial.begin(9600);
  Serial.begin(115200);

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms

  //----Set volume----
  myDFPlayer.volume(10);  //Set volume value (0~30).
  myDFPlayer.volumeUp(); //Volume Up
  myDFPlayer.volumeDown(); //Volume Down

  //----Set different EQ----
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);

  //----Set device we use SD as default----
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);

  //Serial.println("play1");
  //myDFPlayer.play(1);
  //myDFPlayer.playMp3Folder(1);
  //delay(2000);
  //Serial.println("play2");
  //myDFPlayer.play(2);
  //myDFPlayer.playMp3Folder(2);
  //delay(2000);
  //Serial.println("play1-1");
  //myDFPlayer.play(3);
  //myDFPlayer.playLargeFolder(currentChannel, 1);
  //delay(2000);
  //Serial.println("play1-2");
  //myDFPlayer.play(4);
  //myDFPlayer.playLargeFolder(currentChannel, 2);
  //delay(2000);
  //myDFPlayer.stop();
}

void loop() {
  static float distance;
  Serial.print("distance: ");
  Serial.println(distance);
  Serial.print("playing?: ");
  Serial.println(isPlaying());


  if (isPlaying() && playingMusic) {
    Serial.println("watch to stop");
    distance = getDistance(TRIG2_PIN, ECHO2_PIN);
    if (distance < 40) {
      Serial.println("stop music");
      playingMusic = false;
      playMusic(currentChannel, 2);
      delay(2000);
    }
  
  } else {
    Serial.println("wait to trigger playing");
    distance = getDistance(TRIG1_PIN, ECHO1_PIN);
    if (distance < 40) {
      currentChannel ++;
      if (currentChannel > MAX_CHANNEL) {
        currentChannel = 1;
      }
      Serial.println("play music");
      playMusic(currentChannel, 1);
      playingMusic = true;
    }
  }
}

void playMusic(int channel, int number) {
  myDFPlayer.play(2 * (channel-1) + number);
  //myDFPlayer.playLargeFolder(channel, number);
}
