#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "ModbusHandler.h"
#include <DHT.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Non-blocking timer variables
unsigned long lastSensorRead = 0;
const long interval = 2000; // Read sensor every 2 seconds
int t = 0;
int h = 0;

void setup() {
  Serial.begin(9600);
  
  setupModbus();
  dht.begin();
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED Failed");
    for(;;);
  }
  
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(30,25);
  display.print("MODBUS SLAVE");
  display.display();
  delay(1000); 
}


void loop() {
  unsigned long currentMillis = millis();

  // 1. SENSOR & DISPLAY UPDATE (Every 2 seconds)
  if (currentMillis - lastSensorRead >= interval) {
    lastSensorRead = currentMillis;

    int new_h = (int)dht.readHumidity();
    int new_t = (int)dht.readTemperature();

    if (!isnan(new_h) && !isnan(new_t)) {
      t = new_t;
      h = new_h;

      // Update OLED Display
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(30, 5);
      display.print("SENSOR DATA");
      
      display.setTextSize(2);
      display.setCursor(0, 25);
      display.print("Temp: "); display.print(t); display.print("C");
      display.setCursor(0, 45);
      display.print("Hum:  "); display.print(h); display.print("%");
      display.display();
    }
  }

  // 2. MODBUS COMMUNICATION (Runs every loop cycle!)
  // This must stay outside the IF statement so it can listen constantly.
  updateModbus(t, h);

}
