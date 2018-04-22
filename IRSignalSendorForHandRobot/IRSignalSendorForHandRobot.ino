#define IR_SEND_PIN A0

int signalA[] = {906,442,62,50,62,50,62,50,62,50,62,162,62,50,61,50,62,51,62,162,61,162,62,162,62,162,62,50,61,162,62,161,62,162,62,50,61,50,62,50,61,162,61,162,62,161,62,162,62,162,62,162,62,162,62,161,62,50,62,50,61,50,61,51,61,52,59,3959,908,218,61};
int signalB[] = {908,440,65,47,65,47,65,47,64,47,65,158,64,48,64,47,64,48,64,159,64,159,64,158,64,159,64,48,64,158,64,159,64,160,64,48,64,48,64,48,63,162,61,160,62,160,63,162,60,50,64,159,62,160,63,160,63,52,61,48,64,49,62,49,62,162,60,3959,908,218,61};
int signalC[] = {908,440,62,49,62,50,62,50,62,50,62,162,61,50,62,50,62,51,61,162,61,162,62,161,62,161,62,50,62,162,61,162,61,162,62,50,61,50,62,50,62,162,61,162,62,50,61,161,62,51,62,162,61,162,62,162,62,50,61,50,61,162,61,50,62,160,62,3959,908,218,61};

void setup() {
  Serial.begin(115200);
  pinMode(IR_SEND_PIN, OUTPUT);
}

void loop() {
  delay(2000);
  sendSignal(signalA);
  delay(2000);
  sendSignal(signalB);
  delay(2000);
  sendSignal(signalC);
}

void sendSignal(int signalArray[]) {
  bool currentState = false;
  int i;
  for (i=0; i<(sizeof(signalArray)/sizeof(int)); i++) {
    currentState = !currentState;
    if (currentState) {
      digitalWrite(IR_SEND_PIN, HIGH);
    } else {
      digitalWrite(IR_SEND_PIN, LOW);
    }
    delayMicroseconds(signalArray[i]);
  }
  if (currentState) {
    digitalWrite(IR_SEND_PIN, LOW);
  }
}

