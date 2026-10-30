// Test 2: does the amplifier + speaker work?
// Expect: a soft beep-beep every 2 seconds. Press the button for a short tune.
#include "ESP_I2S.h"
#define PIN_AMP_BCLK 26
#define PIN_AMP_LRC 27
#define PIN_AMP_DIN 22
#define PIN_BUTTON 13
#define RATE 16000
#define LEVEL 0.25f  // 25% loudness: safe for a 0.5 W speaker

I2SClass amp;

void playTone(float hz, int ms) {
  static int16_t buf[256 * 2];
  int total = RATE * ms / 1000;
  float phase = 0, step = 2 * PI * hz / RATE;
  for (int done = 0; done < total;) {
    int k = min(256, total - done);
    for (int i = 0; i < k; i++) {
      int16_t v = hz > 0 ? (int16_t)(sinf(phase) * 32767 * LEVEL) : 0;
      buf[2 * i] = v;      // left
      buf[2 * i + 1] = v;  // right
      phase += step;
    }
    amp.write((uint8_t *)buf, k * 4);
    done += k;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  amp.setPins(PIN_AMP_BCLK, PIN_AMP_LRC, PIN_AMP_DIN);
  if (!amp.begin(I2S_MODE_STD, RATE, I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_STEREO)) {
    Serial.println("I2S start failed. Check the board is 'ESP32 Dev Module' and core 3.x.");
    while (true) delay(1000);
  }
  Serial.println("Test 2 running: you should hear beeps");
}

void loop() {
  if (digitalRead(PIN_BUTTON) == LOW) {
    float notes[] = {523, 659, 784, 1047};
    for (float n : notes) playTone(n, 150);
  } else {
    playTone(880, 120);
    playTone(0, 120);
    playTone(880, 120);
  }
  playTone(0, 1500);  // silence
}
