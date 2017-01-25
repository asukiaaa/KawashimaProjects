#include <HaLakeKitFirstConnector.h>
#include <SoftwareSerial.h>

//#define DEBUG_MODE

HaLakeKitFirstConnector kitConnector(&Serial1);
SoftwareSerial someSerial1(6,7);
SoftwareSerial someSerial2(8,9);

String kitStr;
String strToSend;

void setup() {
  kitConnector.begin();
#ifdef DEBUG_MODE
  while (!Serial);
  Serial.begin(115200);
#endif
}

void loop() {
  kitStr = kitConnector.waitLine();

  if (kitStr.length() > 0) {
    strToSend = kitStr + "\n";
    someSerial1.print(strToSend);
    someSerial2.print(strToSend);
#ifdef DEBUG_MODE
    Serial.print(strToSend);
#endif
  }
  delay(10);
}


