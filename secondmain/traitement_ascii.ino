//Fonction qui permet de traiter le caractère reçu depuis le téléphone
char actions[][10] ={"allume", "eteins", "monte", "baisse", "info"};
char modules[][20] ={"musique", "lumière", "chauffage", "temperature"};

String ReceptionBluetoothAscii(String msg){
  char* c = &msg[0];
  String action;

  if(strstr(c,actions[0])){
    if(strstr(c, modules[0])){//allume la musique
      printOkToClient(0,0,1);
      tmrpcm.play(tab[0]);
    }else if(strstr(c, modules[1])){//allume la lumière
      printOkToClient(0,1,1);
      action = "a";    
    }else if(strstr(c, modules[2])){//allume le chauffage
      printOkToClient(0,2,0);
      action = "c";    
    }else{
      BTSerie2.print("Que voulez vous allumer?");
    }
  }else if(strstr(c, actions[1])){//eteint la musique
    if(strstr(c, modules[0])){
      printOkToClient(1,0,1);
      action = "p";    
    }else if(strstr(c, modules[1])){ //éteint la lumière
      printOkToClient(1,1,1);
      action = "e";    
    }else if(strstr(c, modules[2])){//éteint le chauffage
      printOkToClient(1,2,0);  
      action = "s";
    }else{
      BTSerie2.print("Que voulez vous éteindre?");
    }
  }else if(strstr(c, actions[2])){
    if(strstr(c, modules[0])){// monte la musique
      printOkToClient(2,0,1);
      setVolumeSpeaker(1);
    }else if(strstr(c, modules[3])){//monte la température
      printOkToClient(2,3,1);
    }else {
      BTSerie2.print("Que voulez vous monter?");
    }
  }else if(strstr(c, actions[3])){
     if(strstr(c, modules[0])){//baisse la musique
      printOkToClient(3,0,1);
    }else if(strstr(c, modules[3])){//baisse la température
      printOkToClient(3,3,1);
    }else {
      BTSerie2.print("Que voulez vous baisser?");
    }
  }else if(strstr(c, actions[4])){//infos
    printInfos();
    action = "t";
  }else{
    BTSerie2.print("Je n'ai pas compris");
  }
  return action;
}

void printOkToClient(int action, int module, int feminin){
  BTSerie2.print("D'accord, j'");
  BTSerie2.print(actions[action]);
  if(feminin == 0){
    BTSerie2.print(" le ");
  }else{
    BTSerie2.print(" la ");
  }
  BTSerie2.println(modules[module]);
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
