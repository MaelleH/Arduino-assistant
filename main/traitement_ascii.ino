//Fonction qui permet de traiter le caractère reçu depuis le téléphone
char actions[][10] ={"allume", "eteins", "monte", "baisse", "info"};
char modules[][20] ={"musique", "lumière", "chauffage", "temperature"};

void ReceptionBluetoothAscii(char* c){
  if(strstr(c,actions[0])){
    if(strstr(c, modules[0])){
      printOkToClient(0,0,1);
    }else if(strstr(c, modules[1])){
      printOkToClient(0,1,1);
    }else if(strstr(c, modules[2])){
      printOkToClient(0,2,0);       
    }else{
      Serial1.print("Que voulez vous allumer?");
    }
  }else if(strstr(c, actions[1])){
    if(strstr(c, modules[0])){
      printOkToClient(1,0,1);
    }else if(strstr(c, modules[1])){
      printOkToClient(1,1,1);
    }else if(strstr(c, modules[2])){
      printOkToClient(1,2,0);       
    }else{
      Serial1.print("Que voulez vous éteindre?");
    }
  }else if(strstr(c, actions[2])){
    if(strstr(c, modules[1])){
      printOkToClient(2,1,1);
    }else if(strstr(c, modules[3])){
      printOkToClient(2,3,1);
    }else {
      Serial1.print("Que voulez vous monter?");
    }
  }else if(strstr(c, actions[3])){
     if(strstr(c, modules[1])){
      printOkToClient(3,1,1);
    }else if(strstr(c, modules[3])){
      printOkToClient(3,3,1);
    }else {
      Serial1.print("Que voulez vous baisser?");
    }
  }else if(strstr(c, actions[4])){
    printInfos();
  }
  
}

void printOkToClient(int action, int module, int feminin){
  Serial1.print("D'accord, j'");
  Serial1.print(actions[action]);
  if(feminin == 0){
    Serial1.print(" le ");
  }else{
    Serial1.print(" la ");
  }
  Serial1.println(modules[module]);
}

void printInfos(){
    Serial1.println("Voici les infos :");
    Serial1.println("   - Il fait x degres et le chauffage est eteint/allume");
    Serial1.println("   - La lumiere est eteinte/allumee a la puissance 1/2/3");
    Serial1.println("   - La musique est eteinte/allumee et joue la chanson x \n");
}


void printHelp(){
    Serial1.println("Bonjour, je suis blup votre assistant domotique. Vous pouvez me demander plusieurs choses comme par exemple :");
    Serial1.println("   - Eteindre/Allumer la lumiere, le chauffage ou la musique : Blup, allume la lumiere");
    Serial1.println("   - Monter/Baisser la temperature ou l'intensite de la lumiere : Blup, baisse la temperature");
    Serial1.println("   - Afficher les informations de la maison : Blup, quelles sont les infos?");
}
