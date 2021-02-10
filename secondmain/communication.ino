//Libraries 
#include <SD.h>
#include <TMRpcm.h>
 
//Constants 
#define SD_ChipSelectPin 4 
char* message;
const int sizeTab = 3; 
char tab[sizeTab][15] = {"mahalia.wav","mario.wav","shakira.wav"};
int index; 
int newMessage = 0;  
int volumeSpeaker = 3;



//Variables
unsigned long previousTime=0;
unsigned long interval=1000;

//Objects
TMRpcm tmrpcm;

/*******************************************************************
 *                                MAIN
*******************************************************************/
void setupSpeaker(){
/* function setup */
  //Init sd shield
  if (!SD.begin(SD_ChipSelectPin)) {Serial.println("SD fail"); return; }

  //Init speaker
  
  tmrpcm.speakerPin = 9;
  
  tmrpcm.setVolume(volumeSpeaker);

}

/*******************************************************************

 *                               FUNCTIONS

 *******************************************************************/

void activateOutput(){
  if(newMessage == 1) 
  {
    Serial.println("Play sound");

    tmrpcm.play(tab[index]);
    newMessage = 0;
  }
}

void setVolumeSpeaker(int vol){
  if(volumeSpeaker > 0){
    volumeSpeaker = volumeSpeaker + vol;
  }
  tmrpcm.setVolume(volumeSpeaker);
}


void manageMessage(String msg, String act){
  
  if(message == "mahalia"){
    index=0;
  }else if(message == "mario"){
    index=1; 
  }else if(message == "shakira"){
    index=2; 
  }else if(message == "suivant"){
    if(index < sizeTab - 1){
      index = index + 1;
    }
  }else if(message == "precedent"){
    if(index > 0){
      index = index - 1;  
    }else{
      index = sizeTab - 1; 
    }
  }else if(message == "pause" || message == "play"){
    tmrpcm.pause(); 
  }
  
}
