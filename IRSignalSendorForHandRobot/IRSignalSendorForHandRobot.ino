#include <IRremote.h>

#define TOUCH_THRESHOLD_COUNT 10
#define A_OUT_PIN 4
#define A_IN_PIN  5
#define B_OUT_PIN 6
#define B_IN_PIN  7
#define C_OUT_PIN 8
#define C_IN_PIN  9

IRsend irsend; // Send pin is 3 for atmega328(Uno, Nano) and 13 for atmega23u4 (Leonardo, Micro)
const unsigned int signalA = 0x8F71FE0;
const unsigned int signalB = 0x8F71EE1;
const unsigned int signalC = 0x8F71AE5;

void setup() {
  Serial.begin(115200);
  pinMode(A_OUT_PIN, OUTPUT);
  pinMode(A_IN_PIN, INPUT);
  pinMode(B_OUT_PIN, OUTPUT);
  pinMode(B_IN_PIN, INPUT);
  pinMode(C_OUT_PIN, OUTPUT);
  pinMode(C_IN_PIN, INPUT);
}

void loop() {
  if (isTouched(A_OUT_PIN, A_IN_PIN)) {
    irsend.sendNEC(signalA, 32);
  }
  if (isTouched(B_OUT_PIN, B_IN_PIN)) {
    irsend.sendNEC(signalB, 32);
  }
  if (isTouched(C_OUT_PIN, C_IN_PIN)) {
    irsend.sendNEC(signalC, 32);
  }
  delay(10);
}

bool isTouched(int outPin, int inPin) {
  digitalWrite(outPin, HIGH);
  unsigned int count = 0;
  while (digitalRead(inPin) == LOW) {
    count++;
  }
  digitalWrite(outPin, LOW);
  return (count > TOUCH_THRESHOLD_COUNT);
}
