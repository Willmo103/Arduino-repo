#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <FastLED.h>

FASTLED_USING_NAMESPACE
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define FASTLED_ALLOW_INTERRUPTS 0
#define DATA_PIN 3
#define NUM_LEDS 77
#define CYCLE_BRIGHTNESS A3
#define LATCH_COLOR A2

unsigned long lastButtonPressBrightness = 0;
CRGB leds[NUM_LEDS];
int brightIndex = 2;
int brightModes[6] = {42, 85, 128, 170, 212, 255};
int hue;
int sat;
int val;
int lastHue = 0;
int lastSat = 0;

void setup()
{
    delay(3000);
    FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
    lcd.init();
    lcd.backlight();
    lcd.setBacklight(50);
    lcd.setContrast(255);
    pinMode(CYCLE_BRIGHTNESS, INPUT);
    pinMode(LATCH_COLOR, INPUT);
    delay(1);
}

void loop()
{
    int brightBtnState = analogRead(CYCLE_BRIGHTNESS); // Read the analog value instead
    delay(5);
    if (brightBtnState > 500 && millis() - lastButtonPressBrightness > 100) // Adjust the threshold according to your specific hardware
    {
        brightIndex++;
        lastButtonPressBrightness = millis();

        if (brightIndex >= sizeof(brightModes) / sizeof(brightModes[0]))
        {
            brightIndex = 0;
        }
    }

    int readToggle = analogRead(LATCH_COLOR);
    if (readToggle > 500)
    {

        hue = 82;
        sat = 170;
        val = brightModes[brightIndex];

        printLCD();

        for (int i = 0; i < NUM_LEDS; i++)
        {
            leds[i] = CHSV(hue, sat, val);
        }
        FastLED.show();
        delay(1);
    }
    else
    {

        int readHueRaw = analogRead(A0);
        int readSatRaw = analogRead(A1);

        if (readHueRaw > (hue + 10) || readHueRaw < (hue - 10))
        {
            hue = map(readHueRaw, 0, 1023, 0, 255);
            // hue = int(readHueRaw * (255 / 1023));
            lastHue = hue;
        }
        else
        {
            hue = lastHue;
        }

        if (readSatRaw > (sat + 10) || readSatRaw < (sat - 10))
        {
            sat = map(readSatRaw, 0, 1023, 0, 255);
            // sat = int(readSatRaw * (225 / 1023));
            lastSat = sat;
        }
        else
        {
            sat = lastSat;
        }
        val = brightModes[brightIndex];

        printLCD();

        for (int i = 0; i < NUM_LEDS; i++)
        {
            leds[i] = CHSV(hue, sat, val);
        }
        FastLED.show();
        delay(1);
    }
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
    lcd.print(brightModes[brightIndex]);
}
