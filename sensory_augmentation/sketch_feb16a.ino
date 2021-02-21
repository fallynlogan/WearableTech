#include <SPI.h>
#include <SdFat.h>
#include <FreeStack.h>
#include <SFEMP3Shield.h>

SdFat sd;
SFEMP3Shield MP3player;

const int trigPin1 = A2;
const int echoPin1 = A3;

const int trigPin2 = A4;
const int echoPin2 = A5;

const float yourWarm = 35.00;
const float yourHot = 25.00;
const float onFire = 15.00;
const float burningUp = 5.00;

float distance1 = 0;
float distance2 = 0;

void setup() {
  uint8_t result; 
  Serial.begin(115200);
  if(!sd.begin(SD_SEL, SPI_FULL_SPEED)) sd.initErrorHalt();
  if(!sd.chdir("/")) sd.errorHalt("sd.chdir");
  result = MP3player.begin();
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT); 
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
}

void loop() {
  playSongs();
  delay(1000);
}

void playSongs() {
  uint8_t result;
  //Tracks on SD card: Bad Moon Rising, Hotel California, Just Got Paid Today, I'm on Fire   
  int tracks[] = {2,4,6,8};
  int trackLengths[] = {138, 277, 267, 162}; 
  for(int i = 0; i <= 3; i++) {
     result = MP3player.playTrack(tracks[i]);
     Serial.print("i: ");
     Serial.println(i);
     //make this i for the length of the track
     for (int j = 0; j<=trackLengths[i]; j++){
      Serial.print("j: ");
      Serial.println(j);
      distance1 = getDistance1();
      distance2 = getDistance2();
      Serial.print("distance1: ");
      Serial.println(distance1);
      Serial.print("distance2: ");
      Serial.println(distance2);

      if(distance1 <= yourWarm) {
        MP3player.SendSingleMIDInote();
        MP3player.SendSingleMIDInote();
        delay(1000);
      }

      if(distance2 <= yourWarm) {
        MP3player.SendSingleMIDInote();
        delay(1000);
      }
      
      if(distance1 <= yourWarm  && distance1 > yourHot || distance2 <= yourWarm && distance2 > yourHot) {
        MP3player.pauseMusic();
        beep1();
      } 
      else if (distance1 <= yourHot  && distance1 > onFire || distance2 <= yourHot && distance2 > onFire) {
        MP3player.pauseMusic();
        beep2();
      } 
      else if (distance1 <= onFire  && distance1 > burningUp || distance2 <= onFire && distance2 > burningUp) {
        MP3player.pauseMusic();
        beep3();
      }
      else if (distance1 <= burningUp || distance2 <= burningUp) {
        MP3player.pauseMusic();
        beep4();
      } else {
        MP3player.resumeMusic();
      }
      delay(1000);
     }
  }
}

void beep1(){
  MP3player.SendSingleMIDInote();
  delay(1000);
  MP3player.SendSingleMIDInote();
  delay(1000);
  MP3player.SendSingleMIDInote();
  delay(1000);
  MP3player.SendSingleMIDInote();
}

void beep2() {
  MP3player.SendSingleMIDInote();
  delay(500);
  MP3player.SendSingleMIDInote();
  delay(500);
  MP3player.SendSingleMIDInote();
  delay(500);
  MP3player.SendSingleMIDInote();
}

void beep3() {
  MP3player.SendSingleMIDInote();
  delay(100);
  MP3player.SendSingleMIDInote();
  delay(100);
  MP3player.SendSingleMIDInote();
  delay(100);
  MP3player.SendSingleMIDInote();
}

void beep4() {
  MP3player.SendSingleMIDInote();
  delay(25);
  MP3player.SendSingleMIDInote();
  delay(25);
  MP3player.SendSingleMIDInote();
  delay(25);
  MP3player.SendSingleMIDInote();
}

float getDistance1()
{
  float echoTime;
  float calculatedDistance;
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  echoTime = pulseIn(echoPin1, HIGH);
  calculatedDistance = echoTime / 148.0; 
  return calculatedDistance;
}

float getDistance2()
{
  float echoTime;
  float calculatedDistance;
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  echoTime = pulseIn(echoPin2, HIGH);
  calculatedDistance = echoTime / 148.0; 
  return calculatedDistance;
}
