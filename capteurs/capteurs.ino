#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

//--------------------DECLARATIONS DE VARIABLES---------------------------

#define RxD 10    //Pin RX donc vers TxD de la carte Bluetooth
#define TxD 11   //Pin TX donc vers RxD de la carte Bluetooth
#define ledChauffage 2  //Pin de la led representant le chauffage

//Definition des structures de donnees pour les differents module
SoftwareSerial BTSerie(RxD,TxD); //Module bluetooth 1
LiquidCrystal_I2C lcd(0x27, 16, 2);

float volt; //Voltage du capteur de temperature
float temperature; //Temperature du salon

//Variables pour comparer le temps qui passe
unsigned long startMillis;
unsigned long currentMillis;

int photores; //Variable de stockage de la valeur de la photoresistance
int tempMax = 28; //Temperature maximum
int tempMin = 20; //Temperature minimum

//Booleens de test des differents etats
bool chauffageAllume;
bool asktemp;
bool chauffageAuto;
String msg;


//-------------------------------------------------------------------------



//-------------------Initialisation de la carte et des differents modules------------------
void setup() {

  InitCommunicationSerie() ; //Initialisation de la carte
  Serial.println("Initialisation carte : Ok");
  lcd.init();
  Serial.println("Initialisation lcd : Ok");

  asktemp = false;
  chauffageAuto = true;
  chauffageAllume = false;

  // Configuration des Pins du bluetooth 1 et 2
  pinMode(RxD, INPUT);  
  pinMode(TxD, OUTPUT);  

  //Initialisation des modules bluetooth
  InitCommunicationBluetoothSerie();
  
  startMillis = millis(); //initialisation du temps

  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Bonjour vous :)");
}

//----------------------------------------------------------------------------------


//---------------------Boucle principale-----------------------------------
void loop() {
  
  //Initialisation des variables
  char input;
  String test;
  
  currentMillis = millis();  //Reccuperation du temps actuel
   readSerialPort();
   if(msg!=""){
     Serial.print(msg);
     //Traitement en fonction des messages
     if(msg[0] == 't'){ //Reccuperation de la temperature
        asktemp = true;
        temperature = getTemp();
        Serial.println(temperature);
        affichageLCD(temperature, chauffageAllume);
     } else if(msg[0] == 'a') { //Allumage de la lumiere
        chauffageAllume = true;
        digitalWrite(ledChauffage, HIGH); //Allume la led       
     } else if(msg[0] == 'e') { //Extinction de la lumiere
        chauffageAllume = false;
        digitalWrite(ledChauffage, LOW); //Eteint la led
     } else if(msg[0] == 'c' && !chauffageAllume) { //Allumage du chauffage
        asktemp = true;
        temperature = getTemp();
        chauffageAllume = true;
        affichageLCD(temperature, chauffageAllume);
     } else if(msg[0] == 's' && chauffageAllume){ //Extinction du chauffage
        asktemp = true;
        temperature = getTemp();
        chauffageAllume = false;
        affichageLCD(temperature, chauffageAllume);
     }
     msg=""; 
   }

  //Si la temperature du salon est demandee ou qu'il s'est passe environs 5 min
   if(asktemp == true || currentMillis - startMillis >= 180000) {
    asktemp = false;
    temperature = getTemp();
    BTSerie.println(temperature); //On affiche la temperature sur le potable
    photoresCatch(); //Met a jour le min et le max en fonction de la luminosite

    //Verification du depassement des temperatures max et min et si le chauffage est deja en cours d'utilisation ou non
    if(temperature >= tempMax && chauffageAllume) {
          //Si la temperature max est depasse on eteint le chauffage
          BTSerie.println("La temperature max est depassee dans le salon, le chauffage va s'eteindre");
          chauffageAllume = false;
          affichageLCD(temperature, chauffageAllume);
    } else if (temperature <= tempMin && !chauffageAllume) {
          //Si la temperature min est depassee on allume le chauffage
          BTSerie.println("La temperature minimal est depassee dans le salon, le chauffage va s'allumer");
          chauffageAllume = true;
          affichageLCD(temperature, chauffageAllume);
    }
    
    startMillis = currentMillis;  //Mise a jour du timer
  }
  if (Serial.available()) {
      msg = Serial.read();
      BTSerie.print(msg);
  }
}

//------------------------------------------------------------

//--------------------Fonctions utilitaires--------------------------

//Fonction permettant de reccuperer la temperature
float getTemp(){
   //Reccuperation de la temperature
    volt = analogRead(0); //On lit les données du capteur
    volt = 5*volt/1023; //On calcule le voltage
    return volt/0.01; //Calcule de la temperature en fonction du voltage
}

//Fonction permettant de reccuperer la luminosite et d'adapter la temperature max et min
void photoresCatch() {  
  photores = analogRead(A1); //Reccuperation du retour de la photoresistance
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

//Fonction permettant la reccuperation des donnes bluetooths
void readSerialPort(){
 while (BTSerie.available()) {
   delay(10); 
   if (BTSerie.available() >0) {
     char c = BTSerie.read();  //gets one byte from serial buffer
     msg += c; //makes the string readString
   }
 }
 BTSerie.flush(); //Nettoyage du buffer
}

//Fonction permettant l'affichage sur l'ecran lcd
void affichageLCD(int temp, bool chauffage) {
   const char * degree = "\337C"; // °C
  
   lcd.begin(16,2); //Definit la taille de l'ecran
   lcd.setCursor(0,0); //Place le curseur sur la premiere ligne
   //Affichage de l'etat du chauffage
   if(chauffage){
       lcd.print("Chauffage allume");
   } else {
       lcd.print("Chauffage eteint");
   }
   //Affichage de la temperature
   lcd.setCursor(0,10); //Place le curseur sur la seconde ligne
   lcd.print("Temp : ");
   lcd.print(temp); 
   lcd.print(degree);

   delay(2000); //Donne un delay de mise a jour
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
  BTSerie.begin(9600);  //9600 den mode normal / 38400 en mode commande
  while (!BTSerie) {
      Serial.println("Attente reponse bluetooth");
  }
  Serial.println("Demarrage connexion bluetooth serie : Ok");
}
