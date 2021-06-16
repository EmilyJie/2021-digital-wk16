#define NOTE_C3 131
#define NOTE_D3 147
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_G3 196
#define NOTE_A3 220
#define NOTE_B3 247
#define NOTE_C4 262

const int buttonPin = 2;
const int musicButtonPin = 3;
int buttonState = 0;
int latchPin = 8;
int clockPin = 12;
int dataPin = 11;

byte colDataMatrix[8] = {
  B11111110,
  B11111101,
  B11111011,
  B11110111,
  B11101111,
  B11011111,
  B10111111,
  B01111111
};

byte smileRowDataMatrix[8] = {
  B00111100,
  B01000010,
  B10100101,
  B10100101,
  B10000001,
  B10100101,
  B01011010,
  B00111100
};

byte loveRowDataMatrix[8] = {
  B00000000,
  B00100100,
  B01111110,
  B01111110,
  B01111110,
  B00111100,
  B00011000,
  B00000000
};

int melody[] = {
  NOTE_G3, 
  NOTE_E3, 
  NOTE_E3, 
  0, 
  NOTE_F3, 
  NOTE_D3, 
  NOTE_D3, 
  0, 
  NOTE_C3, 
  NOTE_D3, 
  NOTE_E3, 
  NOTE_F3, 
  NOTE_G3, 
  NOTE_G3, 
  NOTE_G3
};

int testMelody[] = {
  NOTE_C3,
  NOTE_C3,
  NOTE_C3,
  NOTE_E3,
  NOTE_G3,
  NOTE_G3,
  NOTE_G3,
  NOTE_G3,
  NOTE_A3,
  NOTE_A3,
  NOTE_A3,
  NOTE_C4,
  NOTE_G3,
};

int noteDurations[] = {
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8
};

int testDurations[] = {
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8
};

int thisNote = -1 , noteDuration = 0;

long previousTime = 0,
     presentTime = 0,
   pauseBetweenNotes = 0;

void checkToPlay() {
  buttonState = digitalRead(musicButtonPin);
  presentTime = millis();
  if(buttonState == HIGH){
    if(presentTime - previousTime >= pauseBetweenNotes){
      thisNote += 1;
      if(thisNote >= 13) {
        thisNote = -1;
        pauseBetweenNotes = 100;
        previousTime = millis();
      } else {
        noteDuration = 500 / testDurations[thisNote];
        tone(9, testMelody[thisNote], noteDuration);
        pauseBetweenNotes = noteDuration * 1.2;
        previousTime = millis();
      }
    }
  } else {
    if(presentTime - previousTime >= pauseBetweenNotes){
      thisNote += 1;
      if(thisNote >= 15) {
        thisNote = -1;
        pauseBetweenNotes = 100;
        previousTime = millis();
      } else {
        noteDuration = 500 / noteDurations[thisNote];
        tone(9, melody[thisNote], noteDuration);
        pauseBetweenNotes = noteDuration * 1.2;
        previousTime = millis();
      }
    }
  }
}

void setup(){
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  digitalWrite(buttonPin,HIGH);
  pinMode(musicButtonPin, INPUT_PULLUP);
  digitalWrite(musicButtonPin,HIGH);
}

void loop(){
  checkToPlay();
  buttonState = digitalRead(buttonPin);
  if(buttonState == HIGH){
    for(int i = 0; i < 8; i++){
      digitalWrite(latchPin,LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);
      shiftOut(dataPin, clockPin, MSBFIRST, smileRowDataMatrix[i]);
      digitalWrite(latchPin,HIGH);
      delay(1);
    }
  } else {
    for(int i = 0; i < 8; i++){  
      digitalWrite(latchPin,LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);
      shiftOut(dataPin, clockPin, MSBFIRST, loveRowDataMatrix[i]);
      digitalWrite(latchPin,HIGH);
      delay(1);
    }
  }
}
