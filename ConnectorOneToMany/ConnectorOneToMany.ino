#include <HaLakeKitFirstConnector.h>
#include <SoftwareSerial.h>

HaLakeKitFirstConnector kitConnector(&Serial1);
SoftwareSerial someSerial1(6,7);
SoftwareSerial someSerial2(8,9);

String kitStr;
String strToSend;

void setup() {
  while (!Serial);
  kitConnector.begin();
}

void loop() {
  kitStr = kitConnector.waitLine();
  if (kitStr.length() > 0) {
    strToSend = kitStr + "\n";
    someSerial1.print(strToSend);
    someSerial2.print(strToSend);
  }
}


