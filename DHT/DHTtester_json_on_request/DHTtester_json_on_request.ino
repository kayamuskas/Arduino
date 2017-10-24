// http://arduino-info.wikispaces.com/PROJECT-Temp-Humidity-Display
// Kayama 

#include "DHT.h"

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

#define DHTPIN 2     // what digital pin we're connected to

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.

const int ledPin = 13;

byte inbyte = 0;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
//  Serial.println("DHTxx test!");

  dht.begin();

  lcd.init();                      // initialize the lcd 
 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.print("Loading.........");

}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  if (Serial.available() >0) {
   
    inbyte = Serial.read(); //Read one byte (one character) from serial port.   
    if (inbyte == 'f') {
      Serial.print("{ \"data\": ");
      Serial.print("{ \"Humidity (%)\": ");
      Serial.print(h);
      Serial.print(",");
      Serial.print("\"Temperature\": {\"C\": ");
      Serial.print(t);
      Serial.print(", \"F\": ");
      Serial.print(f);
      Serial.print("}, ");
      Serial.print("\"Heat index\": {\"C\": ");
      Serial.print(hic);
      Serial.print(", \"F\": ");
      Serial.print(hif);
      Serial.print("}");
      Serial.println(" } }");
    }
  }

//  if (Serial.available()) {
//    flash(Serial.read() - '0');
//  }

  lcd.setCursor(0, 0);

  lcd.print("Temperat: ");
  lcd.print(t, 2);
  lcd.print("C");
  
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(h, 2);
  lcd.print("%");
  
//  delay(2000);

}


void flash(int n)
{
  for (int i = 0; i < n; i++)
  {
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(100);
  }
}

