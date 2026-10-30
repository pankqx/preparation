// Test 4: mic and speaker together, no Wi-Fi needed.
// Hold the button and say something (up to 2 seconds), let go: the necklace plays it back.
// If this works, all the hardware is right. Anything left is Wi-Fi or the hub.
#include "ESP_I2S.h"
#define PIN_MIC_SCK 32
#define PIN_MIC_WS 25
#define PIN_MIC_SD 33
#define PIN_AMP_BCLK 26
#define PIN_AMP_LRC 27
#define PIN_AMP_DIN 22
#define PIN_BUTTON 13
#define PIN_LED 2
#define RATE 16000
#define MIC_CHANNEL 0  // from test 3
#define MIC_SHIFT 14
#define VOLUME 0.5f
#define SECONDS 2

I2SClass mic, amp;
int16_t *rec;
const size_t MAXS = RATE * SECONDS;

void setup() {
  Serial.begin(115200);
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  pinMode(PIN_LED, OUTPUT);
  rec = (int16_t *)malloc(MAXS * 2);
  if (!rec) Serial.println("Not enough memory");
  amp.setPins(PIN_AMP_BCLK, PIN_AMP_LRC, PIN_AMP_DIN);
  amp.begin(I2S_MODE_STD, RATE, I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_STEREO);
  mic.setPins(PIN_MIC_SCK, PIN_MIC_WS, -1, PIN_MIC_SD);
  mic.begin(I2S_MODE_STD, RATE, I2S_DATA_BIT_WIDTH_32BIT, I2S_SLOT_MODE_STEREO);
  Serial.println("Test 4: hold the button and talk");
}

void loop() {
  static int32_t raw[256 * 2];
  static int16_t out[256 * 2];
  if (digitalRead(PIN_BUTTON) == HIGH || !rec) { mic.readBytes((char *)raw, sizeof(raw)); return; }

  digitalWrite(PIN_LED, HIGH);
  size_t n = 0;
  float prevIn = 0, prevOut = 0;
  while (digitalRead(PIN_BUTTON) == LOW && n < MAXS) {
    size_t frames = mic.readBytes((char *)raw, sizeof(raw)) / 8;
    for (size_t i = 0; i < frames && n < MAXS; i++) {
      float x = raw[2 * i + MIC_CHANNEL] >> MIC_SHIFT;
      float y = x - prevIn + 0.995f * prevOut;
      prevIn = x; prevOut = y;
      rec[n++] = (int16_t)constrain(y, -32768.0f, 32767.0f);
    }
  }
  digitalWrite(PIN_LED, LOW);
  Serial.printf("Recorded %.1f s, playing back\n", n / (float)RATE);

  for (size_t i = 0; i < n; i += 256) {
    size_t k = min((size_t)256, n - i);
    for (size_t j = 0; j < k; j++) out[2 * j] = out[2 * j + 1] = (int16_t)(rec[i + j] * VOLUME);
    amp.write((uint8_t *)out, k * 4);
  }
  memset(out, 0, sizeof(out));
  for (int i = 0; i < 10; i++) amp.write((uint8_t *)out, sizeof(out));  // trailing silence
  while (digitalRead(PIN_BUTTON) == LOW) delay(10);
}
