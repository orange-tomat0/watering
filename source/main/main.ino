#include <M5CoreS3.h>

#define INPUT_PIN G1
#define PUMP_PIN  G2

bool flag = true;
int rawADC;

void setup()
{
    M5.begin();
    Serial.begin(9600);
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setTextDatum(TC_DATUM);
    M5.Lcd.drawString("Watering TEST", 160, 20, 1);
    M5.Lcd.drawString("ON/OFF PUMP", 160, 200, 1);
    pinMode(INPUT_PIN, INPUT);
    pinMode(PUMP_PIN, OUTPUT);
}

void loop()
{
    M5.update();
    rawADC = analogRead(INPUT_PIN);
    M5.Lcd.fillRect(80, 100, 240, 50, BLACK);
    M5.Lcd.setCursor(80, 100);
    M5.Lcd.print("ADC: " + String(rawADC));
    Serial.print("Watering ADC value: ");
    Serial.println(rawADC);
    if (M5.BtnB.wasPressed()) {
        digitalWrite(PUMP_PIN, flag);
        flag = !flag;
    }
    delay(100);
}