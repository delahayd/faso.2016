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
      digitalWrite(redLEDPin, HIGH);
      lcd.setCursor(0, 0);
      lcd.println("Soufflez jusqu'a ce que la LED rouge devienne verte.");
      delay(250);
      

      int avAlcValue1 = 0;
      int avAlcValue2= 100;
      int temp;
            
      while(avAlcValue1 + 1 < avAlcValue2 || avAlcValue1 - 1 > avAlcValue2){ 
        lcd.scrollDisplayLeft();
        delay(200); 
        int mq3ValueTot = 0;
        Serial.println("Test");

        int i= 0;
         //count the average value of alcohol
        for (i=0; i<25; i++) {
          mq3ValueTot = mq3ValueTot + analogRead(mq3AnalogPin);
          Serial.println("testMQ3");
          delay(10);
        }
        temp = avAlcValue2;
        avAlcValue2 = mq3ValueTot / 25;
        avAlcValue1 = temp;
      }
    digitalWrite(redLEDPin, LOW);
    digitalWrite(greenLEDPin, HIGH);
    lcd.clear();
    


    
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:

  
  
  // give ample warmup time for readings to stabilize

  lcd.print(avAlcValue2);
  Serial.println("test2");

  delay(1000); //Just here to slow down the output.


}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
