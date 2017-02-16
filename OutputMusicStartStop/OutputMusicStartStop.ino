#include <SD.h>
#include <SPI.h>
#include <AudioZero.h>

void setup() {
  while(!Serial);

  // debug output at 115200 baud
  Serial.begin(115200);

  // setup SD-card
  Serial.print("Initializing SD card...");
  if (!SD.begin(4)) {
    Serial.println(" failed!");
    return;
  }
  Serial.println(" done.");
  // hi-speed SPI transfers
  SPI.setClockDivider(4);

  // 88200 sample rate
  AudioZero.begin(88200);
}

void loop()
{
  int count = 0;

  // open wave file from sdcard
  File myFile = SD.open("test.wav");
  if (!myFile) {
    // if the file didn't open, print an error and stop
    Serial.println("error opening test.wav");
    while (true);
  }

  Serial.print("Playing");

  // until the file is not finished
  AudioZero.play(myFile);
  AudioZero.end();

  Serial.println("End of file. Thank you for listening!");
  while (true) ;
}
