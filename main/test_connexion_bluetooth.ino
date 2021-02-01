
#define rxPin 19 // Broche 11 en tant que RX, à raccorder sur TX du HC-05
#define txPin 18 // Broche 10 en tant que TX, à raccorder sur RX du HC-05
#define HC05 Serial1;

void setupBluetooth() {
  // put your setup code here, to run once:
  InitCommunicationSerie();
  Serial.println("Initialisation carte : Ok");

  InitCommunicationBluetoothSerie();
}

//Initialialise la communication série
void InitCommunicationSerie(){
    Serial.begin(9600);
    while(!Serial){}
    Serial.println("Demarrage connexion serie : Ok");
}

//Initialise la com bluetooth
void InitCommunicationBluetoothSerie(){
    Serial1.begin(38400);
    while(!Serial1){
         Serial.println("Attente bluetooth");
    }
    Serial.println("Demarrage bluetooth connexion serie : Ok");
}

// La loop permet d'être constament dans l'attente d'instruction
void loopBluetooth(){
  // put your main code here, to run repeatedly:
  char c;

  receptionDeTel(c);
  emission(c);

  delay(1000);
}
//Permet d'emettre vers le telephone
void emission(char c) {
  if(Serial.available()){
    Serial.print("Envoie vers Bluetooth : ");
    while (Serial.available()) {
      c = Serial.read();
      Serial.print(c);
      Serial1.print(c);
    }
  }
}

//Permet d'emettre vers le telephone
void emissionVersTel(String c) {
  Serial1.print(c);
}

//Permet de receptionner ce qui provient du telephone
void receptionDeTel(char c) {
  char s[50]; 
  int i = 0;
  
  if(Serial1.available()){
    Serial.print("Reception de : ");
    while (Serial1.available()) {
      c = Serial1.read();
      s[i] = c;
      i+=1;
    }
    
    ReceptionBluetoothAscii(s);
    Serial1.println(strlen(s));
  }
}
