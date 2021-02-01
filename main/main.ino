
char c;
String s;
#define rxPin 19 // Broche 11 en tant que RX, à raccorder sur TX du HC-05
#define txPin 18 // Broche 10 en tant que TX, à raccorder sur RX du HC-05

//#define HC05 Serial1

void setup() {
  //Serial.begin(9600);
  //Serial1.begin(9600);
  setupBluetooth();
}

void loop() {
    loopBluetooth(); // On récupère les communications de l'utilisateurs
  /*if(Serial.available()){
    Serial.println("YO LE RAP");
    while(Serial.available()){
        c=Serial.read();
        Serial.println(c);
        s+=c;
    }
    Serial.println(s);
  }
  s="";
  
  if(Serial1.available()){
    Serial.println("COMMENT VA");
    while(Serial1.available()){
        s=Serial1.readString();
        Serial.println(s);
        //s+=c;
    }
    Serial.println(s);
    Serial1.print("coucou");
  }*/
}
