// Test 1: is the board alive, and does the button work?
// Expect: blue LED blinks. Hold the button: LED stays on, and Serial Monitor (115200) prints "PRESSED".
#define PIN_BUTTON 13
#define PIN_LED 2

void setup() {
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BUTTON, INPUT_PULLUP);  // button to GND, no resistor needed
  Serial.println("Test 1 running");
}

void loop() {
  if (digitalRead(PIN_BUTTON) == LOW) {
    digitalWrite(PIN_LED, HIGH);
    Serial.println("PRESSED");
    delay(100);
  } else {
    digitalWrite(PIN_LED, millis() / 500 % 2);
  }
}
