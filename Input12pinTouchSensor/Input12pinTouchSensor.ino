#include <Adafruit_MPR121.h>
#include <HaLakeKitFirstConnector.h>

#define TOUCH_PIN_NUM 12

Adafruit_MPR121 cap = Adafruit_MPR121();
HaLakeKitFirstConnector kitConnector(&Serial1);

uint16_t lasttouched = 0;
uint16_t currtouched = 0;

bool isTouched;
int touchedPin;
int sendValue;

void setup() {
  while (!Serial);
  //Serial.begin(9600);

  kitConnector.begin();

  // Arrd pin and address
  // 5V or NC: 0x5A
  // 3.3V: 0x5B
  // SDA: 0x5C
  // SCL: 0x5D
  cap.begin(0x5A);
}

void loop() {
  // Get the currently touched pads
  currtouched = cap.touched();
  isTouched = false;

  for (uint16_t i=0; i<TOUCH_PIN_NUM; i++) {
    bool touched = currtouched & _BV(i);
    if (touched) {
      touchedPin = i;
      isTouched = true;
      break;
    }
  }

  lasttouched = currtouched;

  if (isTouched) {
    sendValue = 1023 * touchedPin / (TOUCH_PIN_NUM -1);
    kitConnector.sendValue(sendValue);
  }
  delay(50);
}
