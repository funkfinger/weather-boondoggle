#include "Arduino.h"


#include <DHT.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET);

#define DHTPIN 2
#define DHTTYPE DHT22
#define LED_PIN 0


DHT dht(DHTPIN, DHTTYPE);

float f;
float h;

void setupDht();
void setupDisplay();
void updateDisplay();
void readTemp();
String convertFloatToString(float n);

void setup(void) {
  delay(100);
  setupDht();
  setupDisplay();
  updateDisplay();
  delay(100);
  ESP.deepSleep(5 * 1000000);
}

void loop(void) {
//  updateDisplay();
//  delay(1000);
}

void updateDisplay(void) {
  readTemp();
  display.clearDisplay();
  display.setCursor(0,0);
  if (!isnan(f)) {
    display.println("T: " + convertFloatToString(f) + " F");
    display.println("H: " + convertFloatToString(h) + " %");
  } else {
    display.println("Doh! Read error! " + convertFloatToString(f));
  }
  display.display();
}

void setupDisplay(void) {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
}

void readTemp(void) {
  dht.begin();
  //delay(500);
  f = dht.readTemperature(true);
  h = dht.readHumidity();
}

void setupDht(void) {
  dht.begin();
}

String convertFloatToString(float n) {
  char buf2[16];
  return dtostrf(n, 5, 2, buf2);
}

