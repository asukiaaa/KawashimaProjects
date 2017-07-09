#include <MPU9250_asukiaaa.h>
#include <Adafruit_MPR121.h>

#define TOUCH_PIN_NUM 12

MPU9250 mySensor;
Adafruit_MPR121 cap = Adafruit_MPR121();

void setup() {
  Serial.begin(115200);
  mySensor.begin();
  cap.begin(0x5A);
}

void loop() {
  static bool isTouched;
  static int touchedPin;

  mySensor.accelUpdate();
  updateTouchStatus(&isTouched, &touchedPin);

  Serial.println(mySensor.accelSqrt());
  if(isTouched) {
    Serial.println(touchedPin);
  } else {
    Serial.println("not touched");
  }

  delay(100);
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

