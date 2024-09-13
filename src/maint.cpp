#include <Arduino.h>
#include <HX711.h>
#include <LiquidCrystal.h>

// HX711 circuit wiring
const int DOUT_PIN = 6;  // digital out pin from the hx711
const int CLOCK_PIN = 7; // clock pin from the hx711
HX711 scale;
// Initialize the LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(57600);
    scale.begin(DOUT_PIN, CLOCK_PIN, 32); // initialize the scale
    scale.set_scale(500.0F);              // this value is obtained by calibrating the scale with known weights; see the bogde/hx711 libray README for details
    scale.tare();                         // i have not yet tared the device, this might no longer be possible
}

float calculateFlowRate(float pressure)
{
    float betaRatio = 0.5;
    float diameter = 0.0254; // in
    float area = PI * diameter * diameter / 4;
    float density = 998;                // density of water in kg/m^3
    float dischargeCoefficient = 0.939; // discharge coefficient for the venturi tube

    // Calculate the discharge coefficient using the corrected formula
    float volumetricFlowRate = (1 / (sqrt(1 - betaRatio))) * area * (sqrt(2 * pressure / density));

    return volumetricFlowRate;
}

void loop()
{
    Serial.println("Hi");
    if (scale.is_ready())
    {
        scale.set_scale(500.0F); // this value is obtained by calibrating the scale with known weights;
        long reading = scale.get_units(10);
        Serial.print("reading: ");
        Serial.print(reading);
        Serial.println(" Pa");
        float flowRate = calculateFlowRate(reading);

        // Display the flow rate on the LCD
        lcd.begin(16, 2);
        lcd.setCursor(0, 0);
        lcd.print("Flow Rate:");
        lcd.setCursor(0, 1);
        lcd.print(flowRate); // please add the units. I'm not certain if string formatting will work on the lcd
        delay(1000);
    }
}
