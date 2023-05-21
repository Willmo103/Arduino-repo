#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <FastLED.h>

FASTLED_USING_NAMESPACE
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pinout = GND, V+, SDA A4, SCL A5
#define FASTLED_ALLOW_INTERRUPTS 0
#define DATA_PIN 3
#define NUM_LEDS 77
// #define SW_TOGGLE_COLOR 4
#define CYCLE_BRIGHTNESS 5

// unsigned long lastButtonPressColor = 0;
unsigned long lastButtonPressBrightness = 0;
CRGB leds[NUM_LEDS];
brightnesses int[6] = {42, 85, 128, 170, 212, 255};
int brightnessIndex = 2;

void setup()
{
    delay(3000);
    FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
    lcd.init();
    lcd.backlight();
    lcd.setBacklight(50);
    lcd.setContrast(255);
    pinmode(2, INPUT_PULLUP);
    delay(1);
}

void loop()
{
    // int colorBtnState = digitalRead(SW_TOGGLE_COLOR);
    int brightBtnState = digitalRead(CYCLE_BRIGHTNESS);
    delay(5);
    if (brightBtnState == LOW && millis() - lastButtonPressBrightness > 50)
    {
        brightnessIndex++;
        lastButtonPressBrightness = millis();
    }

    if (brightnessIndex > 5)
    {
        brightnessIndex = 0;
    }

    readHueRaw = analogRead(A0);
    readSatRaw = analogRead(A1);

    hue = map(readHueRaw, 0, 1023, 0, 255);
    sat = map(readSatRaw, 0, 1023, 0, 255);
    val = brightnesses[brightnessIndex];

    printLCD();

    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i] = CHSV(hue, sat, val);
    }
    FastLED.show();
    delay(1);
}

void printLCD()
{
    lcd.setCursor(0, 0);
    lcd.print("Hue: ");
    lcd.print(hue);
    lcd.setCursor(0, 1);
    lcd.print("Sat: ");
    lcd.print(sat);
    lcd.setCursor(8, 0);
    lcd.print("Val: ");
    lcd.print(val);
    lcd.setCursor(8, 1);
    lcd.print("Bri: ");
    lcd.print(brightnesses[brightnessIndex]);
}
