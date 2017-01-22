/******** Code arduino *********/

// Numero de port de sortie
int pinLED = 4;
// CodePorte
int salle = 1;
// Code : bit de debut, numero de porte sur 4 bits, bit de fin
bool* code;
// Delai entre deux emissions de code en ms
int delai = 300;
// Duree d'une emission d'un bit en ms
int duree_bit = 30;

void setup() {
  // put your setup code here, to run once:
  
  // Initialisation du port et de la LED
  pinMode(pinLED,OUTPUT);
  digitalWrite(pinLED,LOW);
  
  // Le code est sur 6 bits
  code = new bool[6];
  
  // Bits de debut et de fin
  code[0] = true;
  code[5] = true;
  
  int decomposition = salle;
  for(int i=4;i>=1;i--)
  {
    if(decomposition>=pow(2,i-1))
    {
      code[i]=true;
      decomposition-=pow(2,i-1);
    }
    else
      code[i]=false;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  
  for(int i=0;i<=5;i++)
  {
    digitalWrite(pinLED,code[i]);
    delay(duree_bit);
  }
  digitalWrite(pinLED,LOW);
  delay(delai);
}
