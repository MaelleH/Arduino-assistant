
char c;
String s;


void setup() {
  //setupBluetooth();
  Serial.begin(9600);
  Serial1.begin(9600); 
  Serial2.begin(38400); 
}

void loop() {
    //loopBluetooth(); // On récupère les communications de l'utilisateurs
          
      if(Serial.available()){
        Serial.println("YO LE RAP");
        while(Serial.available()){
            c=Serial.read();
            Serial2.println(c);
            Serial1.println(c);
            Serial.println(c);
            s+=c;
        }
        Serial.println(s);
        s="";
      }

      if(Serial1.available()){
        Serial.println("COMMENT VA");
        while(Serial1.available()){
            s=Serial1.readString();
            Serial.println(s);
        }
        s="";
      }
      
      if(Serial2.available()){
        Serial.println("COMMENT VA 2");
        while(Serial2.available()){
            s=Serial2.readString();
            Serial.println(s);
        }
        s="";
      }

      
  /*if(Serial.available()){
    Serial.println("YO LE RAP");
    while(Serial.available()){
        c=Serial.read();
        Serial.println(c);
        s+=c;
    }
    Serial.println(s);
  }
  
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
