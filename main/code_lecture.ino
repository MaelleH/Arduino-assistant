//Libraries 
#include <SD.h>
#include <TMRpcm.h>
 
//Constants 
#define SD_ChipSelectPin 11//4 
const int speakerPin=9;
char* message;
const int sizeTab = 3; 
char tab[sizeTab][15] = {"mahalia.wav","mario.wav","shakira.wav"};
int index; 
char* lecture = "play";
int newMessage = 0;  



//Variables
unsigned long previousTime=0;
unsigned long interval=1000;

//Objects
TMRpcm tmrpcm;

/*******************************************************************
 *                                MAIN
*******************************************************************/
//void setup(){
/* function setup */
 Serial.begin(9600);
  //Init sd shield
  if (!SD.begin(SD_ChipSelectPin)) {Serial.println("SD fail"); return; }

  //Init speaker
  
  tmrpcm.speakerPin = speakerPin;
  
  tmrpcm.setVolume(3);

}


void loop(){


manageMessage();

if(millis()-previousTime>interval){

activateOutput();

previousTime=millis();

}

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


void manageMessage(){

  if(message == "mahalia")
  {
    index=0;
  }
  if(message == "mario")
  {
    index=1; 
  }
  if(message == "shakira")
  {
    index=2; 
  }
  if(message == "suivant")
  {
    if(index < sizeTab - 1)
    {
      index = index + 1;
    }
  }
  if(message == "precedent")
  
  {
    if(index > 0)
    {
      index = index - 1;  
    }
    else
    {
      index = sizeTab - 1; 
    }
  }
  if(message == "pause" || message == "play")
  {
    tmrpcm.pause(); 
  }
  
}
