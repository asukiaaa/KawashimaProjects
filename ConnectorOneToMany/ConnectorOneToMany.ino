#include <HaLakeKitFirst.h>
#include <SoftwareSerial.h>

//#define DEBUG_MODE

HaLakeKitFirst kitFirst(&Serial1);
SoftwareSerial someSerial1(2,3);
SoftwareSerial someSerial2(4,5);
SoftwareSerial someSerial3(7,8);

String kitStr;
String strToSend;

void setup() {
  kitFirst.begin();
  someSerial1.begin(HALAKEKITFIRST_SERIAL_SPEED);
  someSerial2.begin(HALAKEKITFIRST_SERIAL_SPEED);
  someSerial3.begin(HALAKEKITFIRST_SERIAL_SPEED);
#ifdef DEBUG_MODE
  while (!Serial);
  Serial.begin(115200);
#endif
}

void loop() {
  if (kitFirst.receive()) {
    kitStr = kitFirst.getReceivedString();
    if (kitStr.length() > 0) {
      strToSend = kitStr + "\n";
      someSerial1.print(strToSend);
      someSerial2.print(strToSend);
      someSerial3.print(strToSend);
#ifdef DEBUG_MODE
      Serial.print(strToSend);
#endif
    }
  }
  delay(10);
}


