#include <SoftwareSerial.h>

//--------------------DECLARATIONS DE VARIABLES---------------------------

#define RxD 10    //Pin RX donc vers TxD de la carte Bluetooth
#define TxD 11   //Pin TX donc vers RxD de la carte Bluetooth
#define ledChauffage 2  //Pin de la led representant le chauffage

//Definition des structures de donnees pour les differents module
SoftwareSerial BTSerie(RxD,TxD); //Module bluetooth 1

float volt; //Voltage du capteur de temperature
float temperature; //Temperature du salon

//Variables pour comparer le temps qui passe
unsigned long startMillis;
unsigned long currentMillis;

int photores; //Variable de stockage de la valeur de la photoresistance
int tempMax; //Temperature maximum
int tempMin; //Temperature minimum

//Booleens de test des differents etats
bool chauffageAllumer;
bool chauffageCouper;


//-------------------------------------------------------------------------



//-------------------Initialisation de la carte et des differents modules------------------
void setup() {

  InitCommunicationSerie() ; //Initialisation de la carte
  Serial.println("Initialisation carte : Ok");

  chauffageAllumer = false;
  chauffageCouper = false;


  // Configuration des Pins du bluetooth 1 et 2
  pinMode(RxD, INPUT);  
  pinMode(TxD, OUTPUT);  

  //Initialisation des modules bluetooth
  InitCommunicationBluetoothSerie();
  
  startMillis = millis(); //initialisation du temps
}

//----------------------------------------------------------------------------------


//---------------------Boucle principale-----------------------------------
void loop() {
  
  //Initialisation des variables
  char input;
  String test;
  char message;
  

  currentMillis = millis();  //Reccuperation du temps actuel
  if (BTSerie.available()) {
       message = BTSerie.read();
       Serial.print(message);
       if(message == 't'){
          temperature = getTemp();
          Serial.print(temperature);
          BTSerie.println(temperature);
       } else if(message == 'a') {
          digitalWrite(ledChauffage, HIGH); //Allume la led
       } else if(message == 'e') {
          digitalWrite(ledChauffage, LOW); //Eteint la led
       } else if(message == 'm') {
          photoresCatch(); //Met a jour la temperature max et min en fonction de la luminosite
          Serial.print(tempMax);
       }
   }
  if (Serial.available()) {
      message = Serial.read();
      BTSerie.print(message);
  }
}

//------------------------------------------------------------

//--------------------Fonctions utilitaires--------------------------

float getTemp(){
   //Reccuperation de la temperature
    volt = analogRead(0); //On lit les données du capteur
    volt = 5*volt/1023; //On calcule le voltage
    return volt/0.01; //Calcule de la temperature en fonction du voltage
}

void photoresCatch() {
  
  photores = analogRead(A1); //Reccuperation du retour de la photoresistance
  Serial.print(photores);
  //Si il y a beaucoup de luminosite (on estime qu'il fait jour)
  if(photores >= 930) {
    //On augmente les temperatures max et min
    tempMax = 28;
    tempMin = 20;
  }
  //Si il y a peu de luminosite (on estime qu'il fait nuit)
  else if(photores <= 930) {
    //On diminue les temperatures max et min
    tempMax = 25;
    tempMin = 15;
  }
}

//------------------------------------------------------------

//--------------------Initialisation de la communication serie avec l'ordinateur--------------------------

void InitCommunicationSerie() {
  Serial.begin(9600);    
  while (!Serial) {
  }
  Serial.println("Demarrage connexion serie : Ok");
}


void InitCommunicationBluetoothSerie() {
  BTSerie.begin(38400);  //9600 den mode normal / 38400 en mode commande
  while (!BTSerie) {
      Serial.println("Attente reponse bluetooth");
  }
  Serial.println("Demarrage connexion bluetooth serie : Ok");
}
