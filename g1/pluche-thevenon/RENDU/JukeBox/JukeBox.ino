#include <Wire.h>
#include "rgb_lcd.h"
#include "pitches.h"
rgb_lcd lcd;

//fonction qui permet de choisir au hasard une led
int hasard(){
  int res;
  res = random(2,5);
  return res;
}

//fonction qui permet de créer le premier son
//on commente chaque ligne que pour ce son sachant que les autres correspondent à la meme méthode
void son1() {
  int melody[] = { NOTE_C3, 0, NOTE_G3, 0,NOTE_G3, NOTE_F3, NOTE_G3, 0, NOTE_F3, NOTE_DS3, NOTE_F3, 0, NOTE_F3, NOTE_DS3, NOTE_D3, NOTE_DS3 };     //tableau contenant toutes les notes
 
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("Detente");
  
  int thisNote = 0;
  bool res= true;
  int noteDuration = 1000/4; 
  int pauseBetweenNotes = noteDuration * 1.30;  //pour distinguer les notes on laisse une pause entre elles

  while (thisNote < 16 && res==true) {                 //tant que la mélodie n'est pas finie ou que le booléan est vrai (si l'utilisateur n'a pas appuyé sur le bouton du milieu)
    int num = hasard();                           //on prend au hasard une des leds                      
 
    if(thisNote%2==0){                           //toutes les deux notes on allume une led
        digitalWrite(num,HIGH);
    }
      tone(8, melody[thisNote],noteDuration);  //On joue la note sur la broche 8 pendant la duréé voulue
      delay(pauseBetweenNotes); // delai entre les notes
      noTone(8); //on arrete la musique sur la broche 8

       if(thisNote%2==0){                //toutes les deux notes on eteint une led
          digitalWrite(num,LOW);
       }
      if (digitalRead(6)==HIGH){        //Si l'utilisateur appuye sur le bouton du milieu res = false du coup la musique s'arrete
        res=false;
      }
      thisNote=thisNote+1;
   }
}

//fonction qui permet de créer le deuxième son 
void son2(){
  int melody_2[] = { NOTE_AS3, NOTE_C4, NOTE_CS4,0, NOTE_C4, NOTE_AS3, NOTE_C4, NOTE_CS4, NOTE_DS4, NOTE_C4, NOTE_CS4, NOTE_C4, NOTE_AS3,0,0,0, NOTE_CS4, NOTE_DS4, NOTE_F4,0, NOTE_DS4, NOTE_CS4, NOTE_DS4, NOTE_F4, NOTE_FS4, NOTE_F4,0,0,0,0,0,0,NOTE_F4 ,NOTE_GS4, NOTE_AS4,0, NOTE_GS4, NOTE_FS4, NOTE_F4, NOTE_DS4, NOTE_F4, NOTE_FS4, NOTE_GS4,0, NOTE_CS4,0, NOTE_AS3,0, NOTE_AS3, NOTE_C4, NOTE_CS4,0, NOTE_C4, NOTE_AS3, NOTE_DS4, NOTE_CS4, NOTE_C4, NOTE_AS3 };

  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("Calme");
  
  int thisNote = 0;
  bool res = true;
  int noteDuration = 1000/4;
  int pauseBetweenNotes = noteDuration * 1.15;
  
  while(thisNote < 58 && res==true) { 
     int num = hasard();
     
     if(thisNote%2==0){
         digitalWrite(num,HIGH);
     }

      tone(8, melody_2[thisNote],noteDuration);
      delay(pauseBetweenNotes); 
      noTone(8);
      
      if(thisNote%2==0){
          digitalWrite(num,LOW);
       }
      if(digitalRead(6)==HIGH){
        res = false;
      }
      thisNote=thisNote+1;    
  }
}

//fonction qui permet de créer le troisième son
void son3(){
  int melody_3[] = { NOTE_F4, NOTE_F4, NOTE_F4,0, NOTE_AS4, NOTE_AS4,0,0,0,0,0,0,0,0,0,0, NOTE_F4, NOTE_F4, NOTE_F4,0, NOTE_C5, NOTE_C5,0,0,0,0,0,0,0,0,0,0, NOTE_C5,0, NOTE_CS5,0, NOTE_AS4,0,0,0,0,0,0,0,0,0,0,0 ,NOTE_C5,0,NOTE_CS5,0 ,NOTE_AS4,0,0,0,0,0,0,0,NOTE_A4 };

  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("Repos");
  
  int thisNote = 0;
  bool res = true;
  int noteDuration = 1000/8;
  int pauseBetweenNotes = noteDuration * 0.90;

  while (thisNote < 61 && res==true) { 
    int num = hasard();
       
    if(thisNote%2==0){
       digitalWrite(num,HIGH);
    }
    
      tone(8, melody_3[thisNote],noteDuration);
      delay(pauseBetweenNotes); 
      noTone(8);
      
      if(thisNote%2==0){
          digitalWrite(num,LOW);
      }
      if(digitalRead(6)==HIGH){
        res = false;
      }
      thisNote=thisNote+1;
  }
}

//fonction qui permet de créer le quatrième son
void son4() {
  int melody_4[] = { NOTE_E4, 0,0, NOTE_E3,0,0, NOTE_A3,0,0,0,0,0,0,0, NOTE_A3, NOTE_B3, NOTE_C3, 0,0,0,0,0,0,0,0,0,0,0, NOTE_E4, 0,0,NOTE_D4,0, NOTE_C4, NOTE_E4 };
  
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("Loisir"); 
  
  int thisNote = 0;
  bool res = true;
  int noteDuration = 1000/4;
  int pauseBetweenNotes = noteDuration * 0.7;

  while (thisNote < 35 && res==true) { 
    int num = hasard();

    if(thisNote%2==0){
        digitalWrite(num,HIGH);
     }

      tone(8, melody_4[thisNote],noteDuration);
      delay(pauseBetweenNotes); 
      noTone(8);
      
      if(thisNote%2==0){
          digitalWrite(num,LOW);
       }
      if (digitalRead(6)==HIGH){
        res = false;
      }
      thisNote=thisNote+1;
   }
}

//fonction qui permet de créer le cinquième son
void son5() {
  int melody_5[] = { NOTE_GS4, NOTE_GS4, NOTE_GS4, 0, NOTE_B3, 0, NOTE_GS4, 0, NOTE_FS4, 0,0,0,0,0,0, NOTE_FS4, NOTE_FS4, NOTE_A4, 0, NOTE_GS4, 0, NOTE_FS4, 0, NOTE_E4, 0,0,0,0,0,0,0, NOTE_E4, NOTE_E4, NOTE_E4, 0, NOTE_B3, 0, NOTE_FS4, 0, NOTE_E4,0,0,0,0,0,0,0, NOTE_E4, NOTE_E4, NOTE_E4, 0, NOTE_B3, 0, NOTE_DS4, 0, NOTE_E4 };

  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("Evasion"); 
  
  int thisNote = 0;
  bool res = true;
  int noteDuration = 1000/4;
  int pauseBetweenNotes = noteDuration * 0.5;
 
  while (thisNote < 56 && res==true) { 
    int num = hasard();
    if(thisNote%2==0){
       digitalWrite(num,HIGH);
    }
    
    tone(8, melody_5[thisNote],noteDuration);
    delay(pauseBetweenNotes); 
    noTone(8);
      
    if(thisNote%2==0){
        digitalWrite(num,LOW);
    }   
    if(digitalRead(6)==HIGH){
        res = false;
    }
    thisNote=thisNote+1;
  }
}


//fonction qui permet de lancer le son qui correspond au numero donné en paramètre
void son(int i){
  //on utilise donc switch
  switch(i){
    case 1:
      son1();
      break;
    case 2:
      son2();
      break;
    case 3:
      son3();
      break;
    case 4:
      son4();
      break;
     case 5:
       son5();
       break;
  }
}

  //on initialise les couleurs pour l'ecran lcd
  const int colorR = 140;
  const int colorG = 140;
  const int colorB = 255;

  //on déclare la variable i correspondant au numero de la musique
  int i = 0;

  const String nomMusique[] = { "appuyer sur un bouton", "Dr. Dre - The Next Episode", "Kids United - On Ecrits Sur Les Murs", "Vaudeville Smash - Zinedine Zidane", "Mannequin challenge", "Vald - Selfie" };

//fonction qui déclare et initialise le programme
void setup() {
  //on déclare tous les Pins    (2,3,4 correspondent aux leds, 5,6,7 aux boutons, 8 au buzzer)
  Serial.begin(9600);
  pinMode(2,OUTPUT);   
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,INPUT);
  pinMode(6,INPUT);
  pinMode(7,INPUT);
  pinMode(8,OUTPUT);

 //allume et initialise notre JukeBeatBox
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);
  digitalWrite(4,HIGH);
  lcd.setCursor(6,0);
  lcd.print(".");
  delay(1000);
  digitalWrite(4,LOW);
  digitalWrite(3,HIGH);
  lcd.print(".");
  delay(1000);
  digitalWrite(3,LOW);
  digitalWrite(2,HIGH);
  lcd.print(".");
  delay(1000);
  digitalWrite(4,HIGH);
  digitalWrite(3,HIGH);
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("Bonjour");
  delay(4000);
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  lcd.clear();
}

//fonction principale
void loop() {

  lcd.clear();
  lcd.print(nomMusique[i]);
  delay(1000);
  
  int x = 0;
  bool res = true;

 //on ecrit le nom de la musique
  while(x<20 && res == true) 
  {
    lcd.scrollDisplayLeft(); 
    delay(250);
    if(digitalRead(5)==HIGH or digitalRead(6)==HIGH or digitalRead(7)==HIGH){
         res = false;
    }
  }

//Si le bouton droit est appuyé on change de musique de façon croissante
  if (digitalRead(5)==HIGH)
  {
    i=i+1;
    if (i>5)
    {
      i=1;
    }
    delay(250);
  }
//Si le bouton gauche est appuyé on change de musique de façon décroissante
  else if (digitalRead(7)==HIGH)
  {
    i=i-1;
    if (i<1)
    {
      i=5;
    }
    delay(250);
  }
//Si le bouton du milieu est appuyé, on lance la musique
  else if (digitalRead(6)==HIGH)
  {
    delay(100);
    son(i);
    delay(50);
  
  }
}

