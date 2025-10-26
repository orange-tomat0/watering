
#include <M5CoreS3.h>

void setup() {
  // CoreS3 の初期化
  M5.begin();

  // 画面を黒でクリア
  M5.Lcd.fillScreen(BLACK);

  // 文字色とサイズを設定
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(3);

  // 文字表示
  M5.Lcd.setCursor(20, 50);
  M5.Lcd.println("Hello CoreS3!");
}

void loop() {
  // 画面表示だけなのでループ内は何もしない
}