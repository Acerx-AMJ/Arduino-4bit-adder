bool onRead = false;
bool offRead = false;
bool sendRead = false;

constexpr int size = 4;
int index = 0;

bool pins[size] = {0, 0, 0, 0};
bool previousPins[size] = {0, 0, 0, 0};

// Functions

void setup() {
  for (int i = 0; i < size + size; i++) {
    pinMode(i, OUTPUT);
  }

  for (int i = PIN_A0; i <= PIN_A3; i++) {
    pinMode(i, INPUT);
  }
}

void loop() {
  bool onOn = digitalRead(PIN_A1);
  bool offOn = digitalRead(PIN_A2);
  bool sendOn = digitalRead(PIN_A0);
  
  if (onOn && !onRead) {
    pins[index] = 1;
    index = (index + 1) % size;
  }

  if (offOn && !offRead) {
    pins[index] = 0;
    index = (index + 1) % size;
  }

  if (sendOn && !sendRead) {
    bool carry = false;
    for (int i = 0; i < size; i++) {
      int value = previousPins[i] + pins[i] + carry;
      previousPins[i] = (value == 1 || value == 3);
      carry = value - previousPins[i];
      pins[i] = 0;
    }
    index = 0;
  }

  if (digitalRead(PIN_A3)) {
    for (int i = 0; i < size; i++) {
      previousPins[i] = pins[i] = 0;
    }
    index = 0;
  }

  onRead = onOn;
  offRead = offOn;
  sendRead = sendOn;
  
  for (int i = 0; i < size; i++) {
    digitalWrite(i, pins[i]);
    digitalWrite(i + size, previousPins[i]);
  }
  delay(50);
}
