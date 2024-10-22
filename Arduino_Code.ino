#include <DHT.h>
#include <BH1750.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// #include "dht.h"
// #define dht_apin A1// Analog Pin sensor is connected to
// #define dht_apin 12
#define DHTPIN 12
#define DHTTYPE DHT11 
 

//tds
#include <EEPROM.h>
#include "GravityTDS.h"
 
#define TdsSensorPin A2
//
DHT dht(DHTPIN, DHTTYPE);
BH1750 lightMeter;

LiquidCrystal_I2C lcd(0x27,16,2);

const int sensor_pin = A0;
const int relayPin = 7; /* Soil moisture sensor O/P pin */

//solar
int solar_cell = 0;




//Water Flow sensor
int X;
int Y;
float TIME = 0;
float FREQUENCY = 0;
float WATER = 0;
float TOTAL = 0;
float LS = 0;
const int input = 5;
//
//tds
  GravityTDS gravityTds;
 float temperature = 25,tdsValue = 0;

//

void setup() {
  Serial.begin(9600); 
  dht.begin();
  Wire.begin();      //LIGHT
  lightMeter.begin(); //LIGHT
  pinMode (1 , INPUT);
  pinMode(input,INPUT);
  pinMode(3, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(A1, INPUT); //Solar
  pinMode(relayPin, OUTPUT);
  lcd.init();
  lcd.clear();
  lcd.backlight();
  pinMode(8, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);/* Define baud rate for serial communication */
  //tds
  gravityTds.setPin(TdsSensorPin);
    gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
    gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
    gravityTds.begin();  //initialization

  //


}

void loop() {
  //  DHT.read11(dht_apin);
  // dht.read(DHTPIN);
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  float moisture_percentage;
  int sensor_analog;
//RAINDROP

  int value = analogRead(A3);
  int digital = digitalRead(1);

//

//LIGHT INTENSITY
  float lux = lightMeter.readLightLevel();

//

//tds
    gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
    gravityTds.update();  //sample and calculate
    tdsValue = gravityTds.getTdsValue();  // then get the value
    // Serial.print(tdsValue,0);
    // Serial.println("ppm");
    // delay(1000);
//
//solar
solar_cell = (analogRead(A1) * (5.001 / 1023.001));
  // Serial.println(solar_cell);
  // Serial.setCursor(0, 0);
  // Serial.print("\nSolar Cell Volt");
  // Serial.setCursor(0, 1);
  // Serial.print("\nValue = ");
//  Serial.setCursor(10, 1);
  // Serial.print(solar_cell);
  // delay(1000);
   if(solar_cell >= 3){
    digitalWrite(13, HIGH);
  };

  



  //water flow code
    X = pulseIn(input, HIGH);
    Y = pulseIn(input, LOW);
    TIME = X + Y;
    FREQUENCY = 1000000/TIME;
    WATER = FREQUENCY/7.5;
    LS = WATER/60;
   

  //
 
  // Wait for 5 seconds
  // Wait for another 5 seconds
  
  sensor_analog = analogRead(sensor_pin);
  moisture_percentage = ( 100 - ( (sensor_analog/1023.00) * 100 ) );



   // Serial.print(moisture_percentage);
  if (moisture_percentage >= 50.00) {
    digitalWrite(8, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(relayPin, HIGH); // Turn on the relay module and pump
    
  } else {
    digitalWrite(8, LOW);
    digitalWrite(4, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(relayPin, LOW);
    // delay(1000); // Turn off the relay module and pump
   
  }
  // delay(1000);
  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.print(t);
  delay(1000);
  



 
  //tds
   lcd.setCursor(0,0);
  lcd.print("t:");
  lcd.print(tdsValue);


  //
  lcd.setCursor(0,1);
  lcd.print("H:");
  lcd.print(h);
  // delay(1000);

  lcd.setCursor(9,0);
  lcd.print("M:");
  lcd.print(moisture_percentage);
  delay(1000);

  lcd.setCursor(9,1);
  lcd.print("F:");
  lcd.print(FREQUENCY);
  delay(1000);
  //INTENSITY

  lcd.setCursor(9,1);
  lcd.print("L:");
  lcd.print(lux);



  //
  //solar

  lcd.setCursor(0,1);
  lcd.print("Vt:");
  lcd.print(float(solar_cell));
  //
  
  //RAINDROP
  
  lcd.setCursor(9,0);
  lcd.print("RD:");
  lcd.print(value);
  



  //
  

  // Serial.print("\n\n");
  


  if(t > 31)
    {
      // digitalWrite(13, HIGH);
      digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
      // delay(1000);                       // wait for a second
    }
    else
    {
      //  digitalWrite(13, LOW); 
       digitalWrite(2, LOW);   // turn the LED on (HIGH is the voltage level)
      // delay(1000);                       // wait for a second
    }

  Serial.print(t);
  Serial.print(",");
  Serial.print(h);
  Serial.print(",");
  Serial.print(moisture_percentage);
  Serial.print(",");
  Serial.print(lux);
  Serial.print(",");
  Serial.print(value);
  Serial.print(",");
  Serial.print(solar_cell);
  Serial.print(",");
  Serial.print(tdsValue);
  Serial.print(",");
  Serial.println(FREQUENCY);
  



}
    // delay(1000);//Wait 5 seconds before accessing sensor again.

  



