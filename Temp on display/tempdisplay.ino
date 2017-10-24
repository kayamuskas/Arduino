/* YourDuino.com Example Software Sketch
   DHT11 Humidity and Temperature Sensor test
   Displayed on I2C LCD Display
   Credits: Rob Tillaart
   http://arduino-info.wikispaces.com/PROJECT-Temp-Humidity-Display
   terry@yourduino.com */
   
/*-----( Import needed libraries )-----*/
#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

/*-----( Declare objects )-----*/
// set the LCD address to 0x27 for a 20 chars 4 line display
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

/*-----( Declare Constants, Pin Numbers )-----*/

#define DHTPIN 2 
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600); //(Remove all 'Serial' commands if not needed)
  lcd.begin(20,4);         // initialize the lcd for 20 chars 4 lines, turn on backlight
  lcd.backlight();
  // Print a message to the LCD.
  //lcd.setCursor(0, 1);
  lcd.print("DHT22 Temp/Humid");

}/*--(end setup )---*/

void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{


  int chk = dht.read(DHT22PIN);

  Serial.print("Read sensor: ");
  switch (chk)
  {
    case 0: Serial.println("OK"); break;
    case -1: Serial.println("Checksum error"); break;
    case -2: Serial.println("Time out error"); break;
    default: Serial.println("Unknown error"); break;
  }
  lcd.setCursor(0, 1);

  lcd.print("C=");
  lcd.print((float)dht.readTemperature, 0);
  Serial.print("Temperature (oC): ");
  Serial.println((float)dht.readTemperature, 2);

  lcd.print(" F=");
  lcd.print(Fahrenheit(dht.readTemperature), 0);
  Serial.print("Temperature (oF): ");
  Serial.println(Fahrenheit(dht.readTemperature), 2);
  
  lcd.print("  H=");
  lcd.print((float)dht.readHumidity, 0);
  lcd.print("%");
  Serial.print("Humidity (%): ");
  //Serial.println((float)dht.readHumidity, 2);

  delay(2000);
}/* --(end main loop )-- */

/*-----( Declare User-written Functions )-----*/
//
//Celsius to Fahrenheit conversion
double Fahrenheit(double celsius)
{
        return 1.8 * celsius + 32;
}

//Celsius to Kelvin conversion
double Kelvin(double celsius)
{
        return celsius + 273.15;
}

// dewPoint function NOAA
// reference: http://wahiduddin.net/calc/density_algorithms.htm 
double dewPoint(double celsius, double readhumidity)
{
        double A0= 373.15/(273.15 + celsius);
        double SUM = -7.90298 * (A0-1);
        SUM += 5.02808 * log10(A0);
        SUM += -1.3816e-7 * (pow(10, (11.344*(1-1/A0)))-1) ;
        SUM += 8.1328e-3 * (pow(10,(-3.49149*(A0-1)))-1) ;
        SUM += log10(1013.246);
        double VP = pow(10, SUM-3) * readhumidity;
        double T = log(VP/0.61078);   // temp var
        return (241.88 * T) / (17.558-T);
}

// delta max = 0.6544 wrt dewPoint()
// 5x faster than dewPoint()
// reference: http://en.wikipedia.org/wiki/Dew_point
double dewPointFast(double celsius, double readhumidity)
{
        double a = 17.271;
        double b = 237.7;
        double temp = (a * celsius) / (b + celsius) + log(readhumidity/100);
        double Td = (b * temp) / (a - temp);
        return Td;
}

/* ( THE END ) */