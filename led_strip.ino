#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <FastLED.h>

FASTLED_USING_NAMESPACE
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pinout = GND, V+, SDA A4, SCL A5
#define FASTLED_ALLOW_INTERRUPTS 0
#define DATA_PIN 3
#define NUM_LEDS 77
#define SW_TOGGLE_COLOR 4
#define CYCLE_BRIGHTNESS 5

unsigned long lastButtonPressColor = 0;
unsigned long lastButtonPressBrightness = 0;
int btnVal;
int hue = 0;
int sat = 255;
int val = 128;
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
    int colorBtnState = digitalRead(SW);
    delay(5);
    if (colorBtnState == LOW && millis() - lastButtonPressBrightness > 100)
    {
        currentIdx = (currentIdx < 2) ? currentIdx + 1 : 0;
        lastButtonPress = millis();
    }

    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i] = CHSV(hue, sat, val);
    }
    FastLED.show();
    delay(1);
}
