#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

// HT16K33 4桁7セグのオブジェクト
Adafruit_7segment display = Adafruit_7segment();

// VCC -> Arduino 5V
// GND -> Arduino GND
// SDA -> Arduino A4
// SCL -> Arduino A5

void setup() {
  display.begin(0x70);       // デフォルトI2Cアドレスは 0x70
  display.setBrightness(15); // 輝度 (0〜15)
}

void loop() {
  static int counter = 0;

  // 数字を表示
  display.print(counter);
  display.writeDisplay();

  delay(1000); // 1秒ごとにカウントアップ

  counter++;
  if (counter > 9999) {
    counter = 0;
  }
}
