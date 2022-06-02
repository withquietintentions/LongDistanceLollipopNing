#include <SPI.h>
#include <SD.h>
#include <Adafruit_VS1053.h>

// the VS1053 chip and SD card are both SPI devices.
// Set their respective pins:
#define VS1053_RESET    6     // VS1053 reset pin
#define VS1053_CS       7     // VS1053 chip select pin 
#define VS1053_DCS      4     // VS1053 Data/command select pin 
#define CARDCS          3     // SD card chip select pin
#define VS1053_DREQ     5     // VS1053 Data request

const int buttonPin = 1;      // pin for the pushbutton
int lastButtonState = HIGH;   // previous state of the pushbutton
int counterF = 0;
int counterM = 0;
// make an instance of the MP3 player library:
Adafruit_VS1053_FilePlayer mp3Player =
  Adafruit_VS1053_FilePlayer(VS1053_RESET, VS1053_CS, VS1053_DCS, VS1053_DREQ, CARDCS);

// sound file name must be 8 chars .3 chars:
//scenario 1
const char mSound1[] = "SOUND001.MP3";
const char mSound2[] = "SOUND002.MP3";
const char mSound3[] = "SOUND003.MP3";
//scenario 2
const char mSound4[] = "SOUND004.MP3";
const char mSound5[] = "SOUND005.MP3";
const char mSound6[] = "SOUND006.MP3";
//scenario 3
const char mSound7[] = "SOUND007.MP3";
const char mSound8[] = "SOUND008.MP3";
const char mSound9[] = "SOUND009.MP3";
//for button
boolean oldState = HIGH;
//MALE LOLLIPOP
const int yMPin = A4; //y yellow
const int xMPin = A5; //x brown
int     mode  = 1;
//FEMALE
const int yFPin = A0; //y
const int xFPin = A1; //x
//const int btPin = 11; //Bt attach to digital 7

int xM;
int yM;
int xF;
int yF;
bool change = true;
int countM = 0;
int countF = 0;

void setup() {
  Serial.begin(9600);
  //pinMode(btPin, INPUT); //set btpin as INPUT
  // digitalWrite(btPin, HIGH); //and HIGH
  // set the pushbutton pin as an input, using internal pullups:
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  // reset the VS1053 by taking reset low, then high:
  pinMode(VS1053_RESET, OUTPUT);
  digitalWrite(VS1053_RESET, LOW);
  delay(10);
  digitalWrite(VS1053_RESET, HIGH);
  counterF = 0;
  counterM = 0;
  // initialize the MP3 player:
  if (!mp3Player.begin()) {
    Serial.println("VS1053 not responding. Check to see if the pin numbers are correct.");
    while (true); // stop
  }

  // initialize the SD card on the module:
  if (!SD.begin(CARDCS)) {
    Serial.println("SD failed, or not present");
    while (true);  // stop
  }

  // Set volume for left and right channels.
  // 0 = loudest, 100 = silent:
  mp3Player.setVolume(10, 10);

  // use the VS1053 interrrupt pin so it can
  // let you know when it's ready for commands.
  mp3Player.useInterrupt(VS1053_FILEPLAYER_PIN_INT);

  // play file:
  // mp3Player.playFullFile(mSound1);
  // Serial.println("playing");
}


void loop() {
  boolean newState = digitalRead(buttonPin);

  if ((newState == LOW) && (oldState == HIGH)) {
    // Short delay to debounce button.
    delay(100);
    // Check if button is still low after debounce.
    newState = digitalRead(buttonPin);
    if (newState == LOW) {
      if (++mode > 4) mode = 1; // Advance to next mode, wrap around after #8
      switch (mode) {
        case 0:
          scenario1();
          break;
        case 1:
          scenario2();
          break;
        case 2:
          scenario3();
          break;
      }
    }
  }
  xM = analogRead(xMPin);
  yM = analogRead(yMPin);
  xF = analogRead(xFPin);
  yF = analogRead(yFPin);
  // Serial.print("xM: ");//print “x: “
  //Serial.println(analogRead(xMPin)); //read the value of A0 and print it in decimal
  Serial.print("  yM: "); //print “y: “
  Serial.print(analogRead(yMPin)); //read the value of A1 and print
  //Serial.print("xF: ");//print “x: “
  //Serial.println(analogRead(xFPin)); //read the value of A0 and print it in decimal
  //Serial.print("yF: "); //print “y: “
  // Serial.println(analogRead(yFPin)); //read the value of A1 and print
  Serial.print("  counterM: ");
  Serial.print(counterM);
  Serial.print("  change:  ");
  Serial.print(change);
   Serial.print(" mode:  ");
  Serial.println(mode);

  // read a potentiometer (0-1023 readings) and
  // map to a range from 100 to 0:
  //int loudness = 100;
  // set the volume:
  //mp3Player.setVolume(loudness, loudness);
  if (change == true && yM > 900) {
    change = false;
    // mp3Player.stopped();
    counterM = counterM + 1;
    
    if(mode==1){
        scenario1();
      
    }
    else if (mode ==2){
        scenario2();
    }
    else if (mode==3){
     scenario3();
  }
 
}

 if (change == false && yM < 850) {
    change = true;
  }
}


void scenario1() {
  Serial.println("scenario 1");
  if (counterM>3){
    counterM=0;
    }
  if (counterM == 0) {
    mp3Player.playFullFile(mSound1);
    
  }
  else if (counterM == 1) {

    mp3Player.playFullFile(mSound2);
    
  }
   else if (counterM == 2) {

    mp3Player.playFullFile(mSound3);
    
  }
  

}
void scenario2() {
  Serial.println("scenario 2");
  if (counterM>3){
    counterM=0;
    }
  if (counterM == 0) {
    mp3Player.playFullFile(mSound4);
    
  }
  else if (counterM == 1) {

    mp3Player.playFullFile(mSound5);
    
  }
   else if (counterM == 2) {

    mp3Player.playFullFile(mSound6);
    
  }
}

void scenario3() {
  Serial.println("scenario 3");

  if (counterM>3){
    counterM=0;
    }
  if (counterM == 0) {
    mp3Player.playFullFile(mSound7);
    
  }
  else if (counterM == 1) {

    mp3Player.playFullFile(mSound8);
    
  }
  else if (counterM == 2) {

    mp3Player.playFullFile(mSound9);
    
  }
}
