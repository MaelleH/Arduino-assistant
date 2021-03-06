#include <SoftwareSerial.h>

//--------------------DECLARATIONS DE VARIABLES---------------------------

#define RxD 10    //Pin RX donc vers TxD de la carte Bluetooth1
#define TxD 11   //Pin TX donc vers RxD de la carte Bluetooth1 
#define RxD2 6    //Pin RX donc vers TxD de la carte Bluetooth2
#define TxD2 7   //Pin TX donc vers RxD de la carte Bluetooth2

//Definition des structures de donnees pour les differents module
SoftwareSerial BTSerie(RxD,TxD); //Module bluetooth 1 => ARDUINO
SoftwareSerial BTSerie2(RxD2,TxD2); //Module bluetooth 2 => TELEPHONE

String msg;
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

  delay(1000);
}

//------------------------------------------------------------------------------


//---------------------Boucle principale-----------------------------------
void loop() {
  BTSerie2.listen();
  //Si le module bluetooth 2 est a l'ecoute
  if(BTSerie2.isListening()) {
    if(BTSerie2.available()){
     char* s;
    //Tant qu'il est en reception
     while (BTSerie2.available()) { 
        msg = BTSerie2.readString(); //Reccuperation de l'entree
        strcat(s,&msg[0]);
     }
     Serial.println("s = ");
     Serial.println(s);
     if(s != NULL){
       ReceptionBluetoothAscii(s);
     }
    }
  }
}


String handleAskArduino(String c){
  Serial.println("handle arduino");
  sendMessageArduino(c);
  return waitForArduinoMessage();
}

void sendMessageArduino(String c){
  delay(1000);

  BTSerie.listen();
  BTSerie.print(c);
  Serial.print("message envoye a l'arduino");
}


String waitForArduinoMessage(){
    int reponse = 0;
    String answer;
    
    BTSerie.listen();
    Serial.print("dans l'attente d'une reponse");
     //Met le premier module bluetooth en ecoute
    
    while(reponse == 0){
      if(BTSerie.isListening()) {
        //Read answer from slave
        if(BTSerie.available()){
         while (BTSerie.available()) {
             answer= BTSerie.readString(); //Reccuperation de l'entree
         }
         BTSerie2.listen(); //Met le premier module bluetooth en ecoute
         Serial.print("réponse reçue" + answer);
         reponse = 1;
       }
     }
    return answer;
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
  BTSerie.begin(9600);  //9600 den mode normal / 38400 en mode commande
  while (!BTSerie) {
      Serial.println("Attente reponse bluetooth");
  }
  Serial.println("Demarrage connexion bluetooth serie : Ok");
}


void InitCommunicationBluetoothSerie2() {
  BTSerie2.begin(38400);  //9600 den mode normal / 38400 en mode commande
  while (!BTSerie2) {
      Serial.println("Attente reponse bluetooth 2");
  }
  Serial.println("Demarrage connexion bluetooth serie 2 : Ok");
}
