#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;
#define greenLEDPin 2
#define redLEDPin 3
const int mq3AnalogPin = A0;
const int button = A1;
bool button_status = false;
char messagePrincipal[37] = "Appuyez sur le bouton pour commencer.";

// TODO make program that will tell person to press button to start the program
// which will tell person to blow when the light is red until the light is green (until value is stable maybe?)
// then give advices on what to do, drink more or stay


void setup() 
{
    // set up the LCD's number of columns and rows:
    lcd.begin(37, 2);
    pinMode(greenLEDPin, OUTPUT);
    pinMode(redLEDPin, OUTPUT);
    Serial.begin(9600); // open serial at 9600 bps
    
    lcd.setRGB(colorR, colorG, colorB);
    
    // Print a message to the LCD.

    delay(1000);
}

void loop() 
{
      button_status = false;
      digitalWrite(greenLEDPin, LOW);
      lcd.setCursor(0, 0);
      lcd.print(messagePrincipal);

      

      while (!button_status) {
        button_status = digitalRead(button);
        lcd.scrollDisplayLeft();
        delay(200);
      }
      lcd.clear();
      
      
      
      int j;
      for (j=5; j>0; j--){
        lcd.setCursor(0, 0);
        lcd.print("Soufflez dans :");
        delay(250);
        lcd.setCursor(0,1);
        lcd.print(j);
        delay(750);
        lcd.clear();
      }
      lcd.print("Soufflez !");
      delay(250);
      digitalWrite(redLEDPin, HIGH);
      int avAlcValue1 = 0;
      int temp;
      int i= 0;
      int mq3ValueTot = 0;
      
      for (i=0; i<300; i++) {
          mq3ValueTot = mq3ValueTot + analogRead(mq3AnalogPin);
          delay(10);
        
       }
       lcd.clear();
       digitalWrite(redLEDPin, LOW);
       lcd.print("C'est bon !");
       delay(1000);
       lcd.clear();
       lcd.print("La valeur est :");
       avAlcValue1 = mq3ValueTot / 300;
       lcd.setCursor(0,1);
       lcd.print(avAlcValue1);
       delay(3000);
       lcd.clear();
    
}
