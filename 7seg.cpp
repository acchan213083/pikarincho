#include <TM1637Display.h>

// TM1637接続ピン
#define CLK 2
#define DIO 3

TM1637Display display(CLK, DIO);

void setup() {
  // 最大輝度
  display.setBrightness(0x0f); 
}

void loop() {
  static int counter = 0; // カウンター

  // 右詰め4桁で表示
  display.showNumberDec(counter, true);

  delay(1000); // 1秒ごとにカウントアップ

  counter++;
  if (counter > 9999) counter = 0; // 9999でリセット
}
