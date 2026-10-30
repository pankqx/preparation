// Test 3: does the INMP441 microphone work, and on which side (0 or 1)?
// Open Tools > Serial Plotter (115200). Talk or clap near the mic.
// One line (side0 or side1) jumps when you make noise: put that number in config.h as MIC_CHANNEL.
// If both stay flat at 0: check wiring, and that L/R is connected to GND.
#include "ESP_I2S.h"
#define PIN_MIC_SCK 32
#define PIN_MIC_WS 25
#define PIN_MIC_SD 33
#define RATE 16000

I2SClass mic;
int32_t raw[512 * 2];

void setup() {
  Serial.begin(115200);
  mic.setPins(PIN_MIC_SCK, PIN_MIC_WS, -1, PIN_MIC_SD);
  if (!mic.begin(I2S_MODE_STD, RATE, I2S_DATA_BIT_WIDTH_32BIT, I2S_SLOT_MODE_STEREO)) {
    Serial.println("I2S start failed");
    while (true) delay(1000);
  }
}

void loop() {
  size_t got = mic.readBytes((char *)raw, sizeof(raw));
  size_t frames = got / 8;
  if (!frames) return;
  // average loudness of each side, after removing the DC offset
  double mean[2] = {0, 0}, level[2] = {0, 0};
  for (size_t i = 0; i < frames; i++)
    for (int s = 0; s < 2; s++) mean[s] += (raw[2 * i + s] >> 14);
  for (int s = 0; s < 2; s++) mean[s] /= frames;
  for (size_t i = 0; i < frames; i++)
    for (int s = 0; s < 2; s++) level[s] += fabs((raw[2 * i + s] >> 14) - mean[s]);
  Serial.printf("side0:%d side1:%d\n", (int)(level[0] / frames), (int)(level[1] / frames));
}
