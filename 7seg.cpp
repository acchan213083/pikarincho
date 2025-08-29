#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

Adafruit_7segment display = Adafruit_7segment();
#define BUTTON_PIN 2  // 1つのボタン

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  display.begin(0x70);
  display.setBrightness(15);
}

void loop() {
  static int leftCounter = 0;        // 左側 00スタート
  static int rightCounter = 50;      // 右側 50秒
  static bool rightCountingDown = false;
  static int lastButtonState = HIGH;
  static unsigned long lastMillis = 0;

  unsigned long currentMillis = millis();
  int buttonState = digitalRead(BUTTON_PIN);

  // ボタンが押された瞬間の処理
  if (lastButtonState == HIGH && buttonState == LOW) {
    leftCounter++;
    if (leftCounter > 99) leftCounter = 0;

    rightCounter = 50;         // ボタンで右側カウントリセット
    rightCountingDown = true;

    delay(150); // チャタリング防止
  }
  lastButtonState = buttonState;

  // 右側カウンター処理
  if (currentMillis - lastMillis >= 1000) {
    lastMillis = currentMillis;

    if (rightCountingDown) {
      rightCounter--;
      if (rightCounter <= 0) {
        rightCounter = 0;
        rightCountingDown = false; // カウントアップに切替
      }
    } else {
      if (rightCounter < 99) rightCounter++; // 上限99
    }
  }

  // 左右2桁結合して4桁表示
  int displayValue = leftCounter * 100 + rightCounter;
  display.print(displayValue, DEC);
  display.writeDisplay();
}
