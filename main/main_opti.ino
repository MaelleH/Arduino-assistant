#include <SoftwareSerial.h>
#include <SD.h>
#include <TMRpcm.h>
//--------------------DECLARATIONS DE VARIABLES---------------------------

#define RxD 4    //Pin RX donc vers TxD de la carte Bluetooth1
#define TxD 5   //Pin TX donc vers RxD de la carte Bluetooth1
#define RxD2 6    //Pin RX donc vers TxD de la carte Bluetooth2
#define TxD2 7   //Pin TX donc vers RxD de la carte Bluetooth2

//Definition des structures de donnees pour les differents module
SoftwareSerial BTSerie(RxD,TxD); //Module bluetooth 1
SoftwareSerial BTSerie2(RxD2,TxD2); //Module bluetooth 2
TMRpcm tmrpcm; //Module son

//Variables
String msg; 
String answer;
unsigned long previousTime=0;
unsigned long interval=1000;

//-------------------Initialisation de la carte et des differents modules------------------
void setup() {
  msg = "";
  InitCommunicationSerie() ; //Initialisation de la carte
  //Serial.println("Initialisation carte : Ok");
  pinMode(10, OUTPUT);

  // Configuration des Pins du bluetooth 1 et 2
  pinMode(RxD, INPUT);  
  pinMode(TxD, OUTPUT);  
  pinMode(RxD2, INPUT);  
  pinMode(TxD2, OUTPUT);

  //Initialisation des modules bluetooth
  InitCommunicationBluetoothSerie2();
  InitCommunicationBluetoothSerie();
  BTSerie2.listen(); //Mise en ecoute

  //Initialisation du speaker
  setupSpeaker();
  delay(1000);
  
  //Affichage du message a l'utilisateur
  BTSerie2.println("Bonjour, je suis blup votre assistant domotique\nTapez le numero pour faire votre demande :\n 1  - Allumer le chauffage\n 2  - Eteindre le chauffage\n 3  - Reccuperer la temperature\n 4  - Allumer la lumiere\n 5  - Eteindre la lumiere\n 6  - Allumer la musique\n 7  - Eteindre la musique\n");
}

//------------------------------------------------------------------------------


//---------------------Boucle principale-----------------------------------
void loop() {
  //Si le module bluetooth 2 est a l'ecoute
  if(BTSerie2.isListening()) {
    //Tant qu'il est en reception
     while (BTSerie2.available() > 0) { 
        msg = BTSerie2.readString(); //Reccuperation de l'entree
        Serial.println(msg); //Afficage du message
        BTSerie.listen(); //Met le premier module bluetooth en ecoute
     }
  }

  //Traitement du message
  if(msg!=""){
    Serial.println(msg);
    if(msg[0] == '1'){//allume le chauffage
      //BTSerie2.println("D'accord j'allume le chauffage");
      BTSerie.println("c");
    }
     else if(msg[0] == '2'){//éteint le chauffage
      //BTSerie2.println("D'accord, j'eteint le chauffage"); 
      BTSerie.println("s"); 
    }
    else if(msg[0] == '3'){//regarde la température
       BTSerie.println("t");
       msg = "t";
    }
    else if(msg[0] == '4'){//allume la lumière
      //BTSerie2.println("D'accord, j'allume la lumiere");
      BTSerie.println("a");
    }
    else if(msg[0] == '5'){ //éteint la lumière
      //BTSerie2.println("D'accord, j'eteint la lumiere");
      BTSerie.println("e");
    }
    else if(msg[0] == '6'){//allume la musique
      //BTSerie2.println("D'accord j'allume la musique");
      tmrpcm.play("mahalia.wav");
      //while(tmrpcm.isPlaying()){}//wait until file is played
    }
    else if(msg[0] == '7'){//eteint la musique
      //BTSerie2.println("D'accord, j'eteint la musique");
      tmrpcm.pause();
    }
    else{
      BTSerie2.print("Je n'ai pas compris");
    }
  }
  delay(1000);
  
  //Ecoute de la reponse du capteur
  if(BTSerie.isListening()) {
   while (BTSerie.available() > 0) {
      //Si on a demande la temperature
      if(msg[0] == 't'){
        answer = BTSerie.readString(); //Reccuperation de la tempe
        BTSerie2.println("Temperature : "+answer); //Afficage de la temperature sur le premier portable
      }
    }
  }
  Serial.flush();
  msg = "";
  BTSerie2.listen(); //Met le second module bluetooth en ecoute
 }



//------------------------------------------------------------

//--------------------Initialisation de la communication serie avec l'ordinateur--------------------------

void InitCommunicationSerie() {
  Serial.begin(9600);    
  while (!Serial) {
  }
  //Serial.println("Demarrage connexion serie : Ok");
}


void InitCommunicationBluetoothSerie() {
  BTSerie.begin(9600);  //9600 den mode normal / 38400 en mode commande
  while (!BTSerie) {
      Serial.println("Attente reponse bluetooth");
  }
  //Serial.println("Demarrage connexion bluetooth serie : Ok");
}


void InitCommunicationBluetoothSerie2() {
  BTSerie2.begin(9600);  //9600 den mode normal / 38400 en mode commande
  while (!BTSerie2) {
      Serial.println("Attente reponse bluetooth 2");
  }
  //Serial.println("Demarrage connexion bluetooth serie 2 : Ok");
}

void setupSpeaker(){
  //Init sd shield
  if (!SD.begin(10)) {Serial.println("SD fail"); return; }

  //Init speaker
  tmrpcm.speakerPin = 9;
  tmrpcm.setVolume(5);
}
