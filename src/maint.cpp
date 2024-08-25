#include <Arduino.h>
#include <HX711.h>

// int myFunction(int x, int y);

// HX711 circuit wiring
const int DOUT_PIN = 11;
const int CLOCK_PIN = 6;
HX711 scale;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(57600);
    scale.begin(DOUT_PIN, CLOCK_PIN, 32); // initialize the scale
}

void loop()
{
    Serial.println("Hi");
    if (scale.is_ready())
    {
        // long reading = scale.read();
        // Serial.print("Hx711 reading: ");
        // Serial.println(reading);
        // delay(1000);
        Serial.println("scale is ready"); // print the current reading
        // delay(2000);
        scale.set_scale();
        Serial.println("scale is set to nothing");
        // delay(5000);
        scale.tare();
        Serial.println("scale is tared");
        long reading = scale.get_units(1);
        Serial.print("reading: ");
        Serial.println(reading);
    }
    else
    {
        Serial.println("scale is not ready");
        delay(2000);
    }
    delay(1000);

    // put your main code here, to run repeatedly:
}

// put function definitions here:
// int myFunction(int x, int y)
//   return x + y;
// }