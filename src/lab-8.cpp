/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/home/ianp/Documents/iot2021/labs/lab-8/src/lab-8.ino"
#include <Wire.h>
#include <SparkFun_VCNL4040_Arduino_Library.h>
#include <oled-wing-adafruit.h>

void setup();
void loop();
#line 5 "/home/ianp/Documents/iot2021/labs/lab-8/src/lab-8.ino"
SYSTEM_THREAD(ENABLED);

VCNL4040 vcnl;
OledWingAdafruit display;

const uint16_t blue = D6;
const uint16_t green = D7;
const uint16_t orange = D8;

void setup()
{
  Wire.begin(); //Join i2c bus

  vcnl.begin();          // start monitoring prox. + lux
  vcnl.powerOnAmbient(); // Power up the ambient sensor

  display.setup(); // starts the display
  display.clearDisplay();
  display.display();

  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(orange, OUTPUT);
}

void loop()
{
  // this chunk inits display
  display.loop();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);

  uint proxValue = vcnl.getProximity();

  if (proxValue > 4000) // detect if somethings REALLY close
  {
    digitalWrite(blue, LOW);
    digitalWrite(green, LOW);
    digitalWrite(orange, HIGH);
  }
  else if (proxValue > 100) // detect if somethings close-ish
  {
    digitalWrite(blue, LOW);
    digitalWrite(green, HIGH);
    digitalWrite(orange, LOW);
  }
  else // default to detect nothing
  {
    digitalWrite(blue, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(orange, LOW);
  }

  if (display.pressedA())
  {
    display.printlnf("Proximity: %d", proxValue);
    display.display();
  }
  if (display.pressedB())
  {
    display.printlnf("Ambient Light: %d", vcnl.getAmbient());
    display.display();
  }
  if (display.pressedC())
  {
    display.println("I2C address of the VCNL4040: 0x60");
    display.display();
  }
}