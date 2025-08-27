from pyfirmata import Arduino, util
import time

# Arduinoボードのポートを指定 (例: Windows="COM3", Mac/Linux="/dev/ttyUSB0")
board = Arduino("COM3")

# 7セグメントLEDのピン割り当て (a,b,c,d,e,f,g の順)
# 例としてArduinoの2〜8番ピンに接続した場合
segments = [2, 3, 4, 5, 6, 7, 8]

# 各数字のセグメントON/OFFパターン
# 1なら点灯、0なら消灯
numbers = {
    0: [1,1,1,1,1,1,0],
    1: [0,1,1,0,0,0,0],
    2: [1,1,0,1,1,0,1],
    3: [1,1,1,1,0,0,1],
    4: [0,1,1,0,0,1,1],
    5: [1,0,1,1,0,1,1],
    6: [1,0,1,1,1,1,1],
    7: [1,1,1,0,0,0,0],
    8: [1,1,1,1,1,1,1],
    9: [1,1,1,1,0,1,1]
}

# 数字を7セグに表示する関数
def display_digit(digit):
    pattern = numbers[digit]
    for pin, val in zip(segments, pattern):
        board.digital[pin].write(val)

# メインループ
try:
    while True:
        for i in range(10):
            display_digit(i)
            time.sleep(1)  # 1秒ごとにカウントアップ
except KeyboardInterrupt:
    board.exit()
    print("終了しました。")
