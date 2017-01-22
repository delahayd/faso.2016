#include <SoftwareSerial.h>
#define RxD 11      //reception bluetooth
#define TxD 10      //transmission bluetooth
#define trigPin 13  //sortie Ultrasons
#define echoPin 12  //entree Ultrasons 
SoftwareSerial BTSerie(RxD,TxD);

//pins branchements des vannes
int vanne1=3;
int vanne2=4;
int vanne3=5;
int vanne4=6;
//Variables recuperant les qantitees demandees
int qte1;
int qte2;
int qte3;
int qte4;
//triger permettant de regarder si une commande a ete recu
int triger=0;
//pins des leds
int Lverte=8;
int Lrouge=9;

void setup() {
  //vitesse de communication 
  Serial.begin(9600);
  BTSerie.begin(9600);
  // definition des variables en entree/sortie
  pinMode(RxD,INPUT);
  pinMode(TxD,OUTPUT);
  pinMode(vanne1,OUTPUT);
  pinMode(vanne2,OUTPUT);
  pinMode(vanne3,OUTPUT);
  pinMode(vanne4,OUTPUT); 
  pinMode(trigPin, OUTPUT);  
  pinMode(echoPin, INPUT);   
  pinMode(Lverte, OUTPUT);
  pinMode(Lrouge, OUTPUT);
}

void loop() {
  //temps d'une dose 5 seconde
  int temps=5000;
  // variable permettant de recuperer la presence d'un verre
  float duree, distance;
 
 // ---------------do while permettant de verifié la presence d'un verre----------------
 // envoi d'une fonction creneau
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  //recuperation de la duree entre l'emission et la reception du signal
  duree = pulseIn(echoPin, HIGH);
  // Calcul de la distance en cm
  distance = duree*340/(2*10000);
  Serial.println(distance);
  // tant que la distance mesure est superieu a 10 cm aucun verre n'est present
  while (distance > 10) {
    Serial.println("trop loin");
    Serial.println(distance);
    digitalWrite(trigPin, LOW);  
    delayMicroseconds(2); 
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); 
    digitalWrite(trigPin, LOW);
    duree = pulseIn(echoPin, HIGH);
     // Distance proportionnelle à la durée de sortie
    distance = duree*340/(2*10000);
    delay(2000);
  }
  
  Serial.println("un verre");
  //allume la led verte pour dire que la machine est prete pour un cocktail
  digitalWrite(Lverte, HIGH);
  // tant qu'on a pas recupere 4 caracteres
  while (triger==0){
    char recvChar;
    if(BTSerie.available()){
      recvChar=BTSerie.read();
      qte1=(int)recvChar-48;
      Serial.println(qte1);
      
      if(BTSerie.available()){
        recvChar=BTSerie.read();
        qte2=(int)recvChar-48;
        Serial.println(qte2);
        
        if(BTSerie.available()){
          recvChar=BTSerie.read();
          qte3=int(recvChar)-48;
          Serial.println(qte3);
          
          if(BTSerie.available()){
            recvChar=BTSerie.read();
            qte4=(int)recvChar-48;
            Serial.println(qte4);
            Serial.println(triger);
            triger=1;
            // les quatres caracteres ont ete recu on passe le trigger a 1
          }
        }
      }
    }
  }

  
 Serial.println("commande recu");
 // on allume chaque electrovanne de maniere proportionnelle a la valeur recupere
 if(triger==1){
  Serial.println("commande en cours");
  // allume la led en rouge pour montrer qu'un cocktail est en preparation
  digitalWrite(Lverte, LOW);
  digitalWrite(Lrouge, HIGH);
  //gestion de depassement de capacite 
  if(qte1>6){
     digitalWrite(vanne1, HIGH);
     delay(6*temps);
    digitalWrite(vanne1, LOW);
    qte1=qte1-6;
  }
  digitalWrite(vanne1, HIGH);
  delay(qte1*temps);
  digitalWrite(vanne1, LOW);

  if(qte2>6){
    digitalWrite(vanne2, HIGH);
    delay(6*temps); 
    digitalWrite(vanne2, LOW);
    qte2=qte2-6;
  }
  digitalWrite(vanne2, HIGH);
  delay(qte2*temps); 
  digitalWrite(vanne2, LOW);
  
   if(qte3>6){
    digitalWrite(vanne3, HIGH);
    delay(6*temps); 
    digitalWrite(vanne3, LOW);
    qte3=qte3-6;
  }
  digitalWrite(vanne3, HIGH);
  delay(qte3*temps); 
  digitalWrite(vanne3, LOW);


   if(qte4>6){
    digitalWrite(vanne4, HIGH);
    delay(6*temps); 
    digitalWrite(vanne4, LOW);
    qte4=qte4-6;
  }
  digitalWrite(vanne4, HIGH);
  delay(qte4*temps);
  digitalWrite(vanne4, LOW);
  triger=0;
 }
 //on eteint la led rouge et on allume la led verte pour montrer que le cocktail est pret
  Serial.println("commande finit");
  digitalWrite(Lrouge, LOW);
  digitalWrite(Lverte, HIGH);
  //----- do while permettant de verifier que le verre avec la commande prete a ete enleve----
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duree = pulseIn(echoPin, HIGH);
  distance = duree*340/(2*10000);
  Serial.println(distance);
  
  // gestion d un bug du capteur renvoyant des valeur superieu a 2000 cm de maniere aleatoire
  while (distance < 30 || distance >2000) {
    digitalWrite(trigPin, LOW);  
    delayMicroseconds(2); 
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); 
    digitalWrite(trigPin, LOW);
    duree = pulseIn(echoPin, HIGH);
    distance = duree*340/(2*10000);
    Serial.println(distance);
    delay(2000);
  }
  //on eteint la led verte et la machine est prete pour un nouveau cocktail
  Serial.println("verre retire");
  digitalWrite(Lverte, LOW);
}
// le programme est executé en boucle grace au loop de l'arduino


