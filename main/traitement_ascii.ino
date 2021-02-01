//Fonction qui permet de traiter le caractère reçu depuis le téléphone
/*void ReceptionBluetoothAscii(char c){
    switch (c) { // UNe fois en jeu, selon le caractère reçu
      case 'Q':
        Serial.println("left"); // aller à gauche
        Serial1.println("go");
        break;
      case 'D':
        Serial.println("right"); // aller à droite
        break;
      case 'Z':
        Serial.println("jump"); // sauter
        break;
      case 'M':
        Serial.println("fire"); // tirer
        break;
      default:
        Serial1.println("nothing");
        break;
    }
}*/

void ReceptionBluetoothAsciiString(String c){
  if(strstr(c,"allume")){
    
  }else if(strstr(c,"éteind") || strstr(c,"eteind")){
    
  }else if(strstr(c,"monte")){
    
  }else if(strstr(c,"baisse")){
    
  }
  
    switch (c) { // UNe fois en jeu, selon le caractère reçu
      case strstr(c,"allume"):
        Serial.println("left"); // aller à gauche
        Serial1.println("go");
        break;
      case 'D':
        Serial.println("right"); // aller à droite
        break;
      case 'Z':
        Serial.println("jump"); // sauter
        break;
      case 'M':
        Serial.println("fire"); // tirer
        break;
      default:
        Serial1.println("nothing");
        break;
    }
}
/*
// Fonction permettant l'affichage des règles
void printRules(){
  emissionVersTel("\n");
  emissionVersTel("RUno - Help\n");
  emissionVersTel("P = Bouton start/stop\n");
  emissionVersTel("Q = Bouton deplacement vers la gauche\n");
  emissionVersTel("D = Bouton deplacement vers la droite\n");
  emissionVersTel("Z = Bouton effectuer un saut\n");
  emissionVersTel("M = Bouton envoi d'un missile\n");
}

// Fonction affichant le game over
void printLoser() {
  emissionVersTel("\n---------------\n");
  emissionVersTel("PERDU\n");
  emissionVersTel(String(getScore()));
  emissionVersTel("\n---------------\n");
}

// Fonction permettant à l'utilisateur de saisir son pseudo
void setUsername(char pseudo) {
  if (pseudo == '.') { // Si il a fini de saisir et qu'il fait .
    stateUsername = 2;
    setupGame();
  } else {
    if (username == "Player") { // SI l'username est celui d'origine
      username = pseudo;
    } else {
      username += pseudo;
    }
  }
}

// Affichage du score
void printScore() {
  emissionVersTel("\n---------------------");
  emissionVersTel(getUsername());
  emissionVersTel("\n---------------------");
  emissionVersTel("\nLife = "+ String(getLifePoints()));
  emissionVersTel("\nScore = " + String(getScore()));
  emissionVersTel("\nLevel = " + String(getLevel()));
  emissionVersTel("\n---------------------\n");
}*/
