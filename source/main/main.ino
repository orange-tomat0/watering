#include <M5CoreS3.h>

#define INPUT_PIN G1
#define PUMP_PIN G2

#define OFF 0
#define ON 1

int rawADC;

bool is_starting = OFF;
int min_moisture = 2000;
int max_moisture = 1881;
const float moisture_percentage = 50;

void setup() {
  M5.begin();
  Serial.begin(9600);
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextDatum(TC_DATUM);
  M5.Lcd.drawString("Watering TEST", 160, 20, 1);
  M5.Lcd.drawString("CALIB ON/OFF TBD", 160, 200, 1);
  pinMode(INPUT_PIN, INPUT);
  pinMode(PUMP_PIN, OUTPUT);
}

void loop() {
  if (M5.BtnB.wasPressed()) {
    is_starting = !is_starting;
  }

  M5.update();

  if (M5.BtnA.wasPressed()) {
    calibration();
  }

  rawADC = analogRead(INPUT_PIN);
  M5.Lcd.fillRect(80, 100, 240, 50, BLACK);
  M5.Lcd.setCursor(80, 100);
  M5.Lcd.print("ADC: " + String(rawADC));
  Serial.print("Watering ADC value: ");
  Serial.println(rawADC);
  if (rawADC > calc_moisture(moisture_percentage) and is_starting == ON) {
    digitalWrite(PUMP_PIN, ON);
    delay(20);
    digitalWrite(PUMP_PIN, OFF);
  }
  delay(100);
}

void calibration() {
  long long total = 0;
  int result = 0;
  enum Mode { MAX, MIN };
  Mode mode_flag;

  M5.Lcd.fillScreen(BLACK);

  while (true) {
    M5.update();
    M5.Lcd.drawString("Push <<(MAX) or >>(MIN) to select mode", 160, 20, 1);
    if (M5.BtnA.wasPressed()) {
      mode_flag = MAX;
      break;
    } else if (M5.BtnC.wasPressed()) {
      mode_flag = MIN;
      break;
    }
    delay(100);
  }

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.drawString("calibrating now", 160, 20, 1);

  for (int i = 0; i < 1800; i++) {
    M5.update();
    if (M5.BtnB.wasPressed()) {
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.drawString("Watering TEST", 160, 20, 1);
      M5.Lcd.drawString("CALIB ON/OFF TBD", 160, 200, 1);
      return;
    }
    total += analogRead(INPUT_PIN);
    delay(100);
  }
  result = total / 1800;

  M5.Lcd.setCursor(80, 100);
  M5.Lcd.print(String(result));

  if (mode_flag == MAX) {
    max_moisture = result;
  } else if (mode_flag == MIN) {
    min_moisture = result;
  }

  delay(30000);

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.drawString("Watering TEST", 160, 20, 1);
  M5.Lcd.drawString("CALIB ON/OFF TBD", 160, 200, 1);
}

int calc_moisture(float percentage) {
  return max_moisture + (min_moisture - max_moisture) / 100 * percentage;
}