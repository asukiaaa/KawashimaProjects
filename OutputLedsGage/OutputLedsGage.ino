const int LED_PINS[] = {
  4,
  5,
  A1,
  A0,
  6,
  7,
  15,
  14,
  8,
  9,
  16,
  10
};

const int LED_NUM = sizeof(LED_PINS) / sizeof(int);

int i;
int level;

void setup() {
  for (i=0; i<LED_NUM; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], LOW);
  }
}

void loop() {
  level = (int) ((millis() / 1000) % (LED_NUM + 1));

  for (i=0; i<LED_NUM; i++) {
    if (level < i) {
      digitalWrite(LED_PINS[i], HIGH);
    } else {
      digitalWrite(LED_PINS[i], LOW);
    }
  }
}
