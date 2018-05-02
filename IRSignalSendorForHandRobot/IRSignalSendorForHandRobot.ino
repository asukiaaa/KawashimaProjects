#include <IRremote.h>

IRsend irsend; // Send pin is 3 for atmega328(Uno, Nano) and 13 for atmega23u4 (Leonardo, Micro)
const unsigned int signalA = 0x8F71FE0;
const unsigned int signalB = 0x8F71EE1;
const unsigned int signalC = 0x8F71AE5;

void setup() {
  Serial.begin(115200);
}

void loop() {
  delay(2000);
  irsend.sendNEC(signalA, 32);
  delay(2000);
  irsend.sendNEC(signalB, 32);
  delay(2000);
  irsend.sendNEC(signalC, 32);
  delay(2000);
}
