#include <SoftwareSerial.h>

//--------------------DECLARATIONS DE VARIABLES---------------------------

#define RxD 10    //Pin RX donc vers TxD de la carte Bluetooth1
#define TxD 11   //Pin TX donc vers RxD de la carte Bluetooth1
#define RxD2 6    //Pin RX donc vers TxD de la carte Bluetooth2
#define TxD2 7   //Pin TX donc vers RxD de la carte Bluetooth2

//Definition des structures de donnees pour les differents module
SoftwareSerial BTSerie(RxD,TxD); //Module bluetooth 1
SoftwareSerial BTSerie2(RxD2,TxD2); //Module bluetooth 2

String msg;
String answer;
String portable;

//-------------------Initialisation de la carte et des differents modules------------------
void setup() {
  
  InitCommunicationSerie() ; //Initialisation de la carte
  Serial.println("Initialisation carte : Ok");


  // Configuration des Pins du bluetooth 1 et 2
  pinMode(RxD, INPUT);  
  pinMode(TxD, OUTPUT);  
  pinMode(RxD2, INPUT);  
  pinMode(TxD2, OUTPUT);

  //Initialisation des modules bluetooth
  InitCommunicationBluetoothSerie2();
  InitCommunicationBluetoothSerie();
  BTSerie2.listen();

  setupSpeaker();
}

//------------------------------------------------------------------------------


//---------------------Boucle principale-----------------------------------
void loop() {
  //Si le module bluetooth 2 est a l'ecoute
  if(BTSerie2.isListening()) {
    //Tant qu'il est en reception
     while (BTSerie2.available() > 0) { 
        msg = BTSerie2.readString(); //Reccuperation de l'entree
        Serial.println(msg); //Afficage de la temperature sur le premier portable
        BTSerie.listen(); //Met le premier module bluetooth en ecoute
     }
  }
  
  //readSerialPort();
  if(BTSerie.isListening()) {
    //Read answer from slave
     while (BTSerie.available()) {
     delay(10);  
     if (BTSerie.available() >0) {
       char c = BTSerie.read();  //gets one byte from serial buffer
       answer += c; //makes the string readString
     }
   }
    //Send data to slave
    if(msg!=""){
      String act = ReceptionBluetoothAscii(msg);
      Serial.print("Master sent : ");
      if(act != NULL){
        Serial.println(act);
        BTSerie.print(act);
      }
      msg="";
    }
    //Send answer to monitor
    if(answer!=""){
      Serial.print("Slave recieved : ");
      Serial.println(answer);
      answer="";
    }
    BTSerie2.listen(); //Met le premier module bluetooth en ecoute
  }
  
}

void readSerialPort(){
 while (Serial.available()) {
   delay(10);  
   if (Serial.available() >0) {
     char c = Serial.read();  //gets one byte from serial buffer
     msg += c; //makes the string readString
   }
 }
 Serial.flush();
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


void InitCommunicationBluetoothSerie2() {
  BTSerie2.begin(9600);  //9600 den mode normal / 38400 en mode commande
  while (!BTSerie2) {
      Serial.println("Attente reponse bluetooth 2");
  }
  Serial.println("Demarrage connexion bluetooth serie 2 : Ok");
}
