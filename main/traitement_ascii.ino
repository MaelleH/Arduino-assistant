//Fonction qui permet de traiter le caractère reçu depuis le téléphone
char actions[5][10] ={"allume", "eteins", "monte", "baisse", "info"};
char modules[4][20] ={"musique", "lumiere", "chauffage", "temperature"};

void ReceptionBluetoothAscii(char* c){
  String actionPourArduino = " ";
  String answer;
  
  Serial.println(c);
  Serial.println("choix de l'action");
  
  if(strstr(c,"allume") != NULL){
    if(strstr(c, "musique") != NULL){ //allume la musique
      printOkToClient("D'accord, j'allume la musique");
      actionPourArduino = "m";
    }else if(strstr(c, "lumiere") != NULL){ //allume la lumière
      actionPourArduino = "a";
      printOkToClient("D'accord, j'allume la lumiere");
    }else if(strstr(c, "chauffage") != NULL){ //allume le chauffage
      actionPourArduino = "c";     
      printOkToClient("D'accord, j'allume le chauffage");  
    }else{
      BTSerie2.println("Que voulez vous allumer?");
    }
  }else if(strstr(c, "eteins") != NULL){ //eteint la musique
    if(strstr(c, "musique") != NULL){
      printOkToClient("D'accord, j'eteins la musique");
      actionPourArduino = "i";
    }else if(strstr(c, "lumiere") != NULL){ //éteint la lumière
      printOkToClient("D'accord, j'eteins la lumiere");
      actionPourArduino = "e";
    }else if(strstr(c, "chauffage") != NULL){ //éteint le chauffage
      printOkToClient("D'accord, j'eteins le chauffage");
      actionPourArduino = "s";      
    }else{
      BTSerie2.println("Que voulez vous éteindre?");
    }
  }else if(strstr(c, "monte") != NULL){ // monte la lumière
    if(strstr(c, "lumiere")){
      printOkToClient("D'accord, j'monte la lumiere");
    }else if(strstr(c, "temperature") != NULL){ //monte la température
      printOkToClient("D'accord, j'monte la temperature");
    }else {
      BTSerie2.print("Que voulez vous monter?");
    }
  }else if(strstr(c, "baisse") != NULL){ //baisse la lumière
     if(strstr(c, "lumiere")){
      printOkToClient("D'accord, j'baisse la lumiere");
    }else if(strstr(c, "temperature") != NULL){ //baisse la température
      printOkToClient("D'accord, j'baisse la temperature");
    }else {
      BTSerie2.print("Que voulez vous baisser?");
    }
  }else if(strstr(c, "info") != NULL){ //infos
    printInfos();
  }

  
  Serial.println(actionPourArduino);
  if(actionPourArduino != " "){
    Serial.println(actionPourArduino[0]);
    answer = handleAskArduino(actionPourArduino);
    Serial.println(answer);
  }else{
    printOkToClient("Je n'ai pas compris");
  }
}

void printOkToClient(String message){
  BTSerie2.println(message);
  delay(10);
}

void printInfos(){
    BTSerie2.println("Voici les infos :");
    BTSerie2.println("   - Il fait x degres et le chauffage est eteint/allume");
    BTSerie2.println("   - La lumiere est eteinte/allumee a la puissance 1/2/3");
    BTSerie2.println("   - La musique est eteinte/allumee et joue la chanson x \n");
}


void printHelp(){
    BTSerie2.println("Bonjour, je suis blup votre assistant domotique. Vous pouvez me demander plusieurs choses comme par exemple :");
    BTSerie2.println("   - Eteindre/Allumer la lumiere, le chauffage ou la musique : Blup, allume la lumiere");
    BTSerie2.println("   - Monter/Baisser la temperature ou l'intensite de la lumiere : Blup, baisse la temperature");
    BTSerie2.println("   - Afficher les informations de la maison : Blup, quelles sont les infos?");
}
