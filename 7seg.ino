#include <TM1637.h>

#define CLK 2
#define DIO 3

TM1637 display(CLK, DIO);

void setup() {
  display.init();
  display.set(7); // 明るさ最大（0〜7）
}

void showTimeAndCycle(int seconds, int cycle) {
  display.display(0, seconds / 10);   // 十の位（秒）
  display.display(1, seconds % 10);   // 一の位（秒）
  display.display(2, cycle / 10);     // 十の位（サイクル）
  display.display(3, cycle % 10);     // 一の位（サイクル）
}

void loop() {
  int cycle = 0;

  for (int i = 0; i < 10; i++) {
    // インターバル中（サイクル番号は0）
    for (int t = 5; t >= 0; t--) {
      showTimeAndCycle(t, cycle);
      delay(1000);
    }

    // サイクル番号を増やすタイミング
    cycle++;

    // 45秒カウントダウン（サイクル番号は1〜10）
    for (int t = 45; t >= 0; t--) {
      showTimeAndCycle(t, cycle);
      delay(1000);
    }
  }

  // 最後に "FIN " 表示（F=15, I=1, N=14, 空白=16）
  display.display(0, 15); // F
  display.display(1, 1);  // I
  display.display(2, 14); // N
  display.display(3, 16); // 空白
  while (true);
}
