//All the necessary things to import from breath sensor demo code
#include <Wire.h>
#include "Adafruit_MPRLS.h"

#define RESET_PIN -1  
#define EOC_PIN -1    
Adafruit_MPRLS mpr = Adafruit_MPRLS(RESET_PIN, EOC_PIN);
//The following array is the key on the clarinet represented by each button pin:
//{registerKey,thumbKey,leftSideKey,aKey,oneKey,twoKey,bananaTopKey,threeKey,cSharpKey,leftPinkyExt1,leftPinkyExt2,leftPinkyExt3,sideKey1,sideKey2,sideKey3,sideKey4,fourKey,fiveKey,bananaLowKey,sixKey,ebKey,rightPinky1,rightPinky2,rightPinky3}
int buttonPins[24] = { 23, 22, 20, 21, 16, 15, 14, 40, 39, 38, 33, 34, 36, 35, 37, 41, 32, 31, 30, 29, 28, 27, 25, 26 };

//This array holds the data of which keys are actively being pressed
bool activeFingering[24] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };

//Holds every possible fingering - the indexes of the arrays correlate to the notes array that hold the notes for each fingering
bool fingering[74][24] = { { false, true, false, false, true, true, false, true, false, true, false, false, false, false, false, false, true, true, false, true, false, false, false, true },
                           { false, true, false, false, true, true, false, true, false, true, false, false, false, false, false, false, true, true, false, true, false, false, false, false },
                           { false, true, false, false, true, true, false, true, false, false, false, false, false, false, false, false, true, true, false, true, false, false, true, false },
                           { false, true, false, false, true, true, false, true, false, false, false, false, false, false, false, false, true, true, false, true, false, false, false, true },
                           { false, true, false, false, true, true, false, true, false, false, true, false, false, false, false, false, true, true, false, true, false, false, false, false },
                           { false, true, false, false, true, true, false, true, false, false, false, true, false, false, false, false, true, true, false, true, false, false, false, true },
                           { false, true, false, false, true, true, false, true, false, false, false, true, false, false, false, false, true, true, false, true, false, false, false, false },
                           { false, true, false, false, true, true, false, true, false, false, false, false, false, false, false, false, true, true, false, true, false, true, false, false },
                           { false, true, false, false, true, true, false, true, false, false, false, false, false, false, false, false, true, true, false, true, false, false, false, false },
                           { false, true, false, false, true, true, false, true, false, false, false, false, false, false, false, false, true, true, false, true, true, false, false, false },
                           { false, true, false, false, true, true, false, true, false, false, false, false, false, false, false, false, true, true, false, false, false, false, false, false },
                           { false, true, false, false, true, true, false, true, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false, false },
                           { false, true, false, false, true, true, false, true, false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false },
                           { false, true, false, false, true, true, false, true, false, false, false, false, false, false, false, false, false, false, true, false, false, false, false, false },
                           { false, true, false, false, true, true, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false },
                           { false, true, false, false, true, true, false, true, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false },
                           { false, true, false, false, true, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false },
                           { false, true, false, false, true, true, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false },
                           { false, true, false, false, true, true, false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false, false, false },
                           { false, true, false, false, true, false, false, false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false, false },
                           { false, true, false, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false },
                           { false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false },
                           { false, false, false, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false },
                           { false, true, false, false, false, false, false, false, false, false, false, false, false, false, true, true, false, false, false, false, false, false, false, false },
                           { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false },
                           { false, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false },
                           { false, false, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false },
                           { true, false, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false },
                           { false, false, false, true, false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false, false, false, false, false },
                           { true, true, false, false, true, true, false, true, false, true, false, false, false, false, false, false, true, true, false, true, false, false, false, true },
                           { true, true, false, false, true, true, false, true, false, true, false, false, false, false, false, false, true, true, false, true, false, false, false, false },
                           { true, true, false, false, true, true, false, true, false, false, false, false, false, false, false, false, true, true, false, true, false, false, true, false },
                           { true, true, false, false, true, true, false, true, false, false, false, false, false, false, false, false, true, true, false, true, false, false, false, true },
                           { true, true, false, false, true, true, false, true, false, false, true, false, false, false, false, false, true, true, false, true, false, false, false, false },
                           { true, true, false, false, true, true, false, true, false, false, false, true, false, false, false, false, true, true, false, true, false, false, false, false },
                           { true, true, false, false, true, true, false, true, false, false, false, true, false, false, false, false, true, true, false, true, false, false, false, true },
                           { true, true, false, false, true, true, false, true, false, false, false, false, false, false, false, false, true, true, false, true, false, true, false, false },
                           { true, true, false, false, true, true, false, true, false, false, false, false, false, false, false, false, true, true, false, true, false, false, false, false },
                           { true, true, false, false, true, true, false, true, false, false, false, false, false, false, false, false, true, true, false, true, true, false, false, false },
                           { true, true, false, false, true, true, false, true, false, false, false, false, false, false, false, false, true, true, false, false, false, false, false, false },
                           { true, true, false, false, true, true, false, true, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false, false },
                           { true, true, false, false, true, true, false, true, false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false },
                           { true, true, false, false, true, true, false, true, false, false, false, false, false, false, false, false, true, false, true, false, false, false, false, false },
                           { true, true, false, false, true, true, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false },
                           { true, true, false, false, true, true, false, true, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false },
                           { true, true, false, false, true, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false },
                           { true, true, false, false, true, true, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false },
                           { true, true, false, false, true, true, false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false, false, false },
                           { true, true, false, false, true, false, false, false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false, false },
                           { true, true, false, false, true, false, false, false, false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false },
                           { true, true, false, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false },
                           { true, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false },
                           { true, true, false, false, false, true, false, true, false, false, false, false, false, false, false, false, true, true, false, false, false, false, false, false },
                           { true, true, false, false, false, true, false, true, false, false, false, false, false, false, false, false, true, false, false, false, true, false, false, false },
                           { true, true, false, false, false, true, false, true, false, false, false, false, false, false, false, false, true, false, true, false, true, false, false, false },
                           { true, true, false, false, false, true, false, true, false, false, false, false, false, false, false, false, false, true, false, false, true, false, false, false },
                           { true, true, false, false, false, true, false, true, false, false, false, false, false, false, false, false, false, false, false, true, true, false, false, false },
                           { true, true, false, false, false, true, false, true, false, false, false, false, false, false, false, false, false, false, false, false, true, false, false, false },
                           { true, true, false, false, false, true, false, true, true, false, false, false, false, false, false, false, false, false, false, false, true, false, false, false },
                           { true, true, false, false, true, true, false, true, true, false, false, false, false, false, false, false, true, true, false, true, false, false, false, false },
                           { true, true, false, false, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, false, false, false },
                           { true, true, false, false, true, true, false, false, false, false, false, false, false, false, false, false, true, true, false, true, true, false, false, false },
                           { true, true, false, false, false, true, false, false, false, false, false, false, false, false, false, false, true, true, false, false, true, false, false, false },
                           { true, true, false, false, true, false, false, false, false, false, false, false, false, false, false, false, true, true, false, false, true, false, false, false },
                           { true, true, false, false, true, false, false, true, false, false, false, false, false, false, false, false, true, false, false, true, true, false, false, false },
                           { true, true, false, false, false, true, false, true, true, false, false, false, false, false, false, false, true, true, false, false, true, false, false, false },
                           { true, true, false, false, false, true, false, false, false, false, false, false, false, false, false, false, false, true, false, false, true, false, false, false },
                           { true, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, false, false, false, false, true, false, false },
                           { true, true, false, false, false, true, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, true, false, false },
                           { true, true, false, false, false, true, false, true, false, false, false, false, false, false, false, false, false, false, false, false, true, false, false, false },
                           { true, true, true, false, true, true, false, true, true, false, false, false, false, false, false, false, true, true, false, true, false, false, false, true },
                           { true, true, true, false, false, true, false, true, true, false, false, false, false, false, false, false, false, false, false, false, false, true, false, false },
                           { true, true, true, false, true, true, false, false, false, false, false, false, false, false, false, false, true, true, false, false, false, true, false, false },
                           { true, true, true, false, true, false, false, false, false, false, false, false, false, false, false, false, true, false, false, false, false, true, false, false } };

//Holds the MIDI note values correlating with each array index in fingering[][]
int notes[74] = { 64, 64, 64, 65, 65, 66, 66, 66, 67, 68, 69, 70, 71, 71, 72, 73, 74, 75, 75, 75, 76, 77, 78, 78, 79, 80, 81, 82, 82, 83, 83, 83, 84, 84, 85, 85, 85, 86, 87, 88, 89, 90, 90, 91, 92, 93, 94, 94, 94, 94, 95, 96, 97, 98, 99, 99, 99, 100, 101, 101, 102, 102, 103, 103, 103, 103, 104, 104, 105, 105, 106, 106, 107, 108 };

int currentNote = 77; //Open G for init
int prevNote = 77; //Open G for init
int breathVal = 0;
float firstBreath;
float pressureMax;

void setup() {
  //Setup Buttons
  for (int i = 0; i < 24; i++) {
    pinMode(buttonPins[i], INPUT);
  }
  if (!mpr.begin()) { //Breath Sensor Setup
    Serial.println("Failed to communicate with MPRLS sensor, check wiring?");
    while (1) {
      delay(10);
    }
  }
  delay(1000);

  //Sets a starting pressure value so that room pressure doesn't effect numbers
  firstBreath = mpr.readPressure();
  pressureMax = firstBreath + 22;
}

void loop() {
  createFingerArray(); //This updates the activeFingering[] 
  playNote(); //Plays note based on current fingering
  getBreathVal(); //Reads average value from pressure sensor from 1000 different readings
  if (millis() % 50 == 0) {
    controlCC(); //Sends pressure sensor data to control CC Volume
  }
}

void getBreathVal() { 
  float pressure = mpr.readPressure(); //Get breath data

  //Average and map breath data to MIDI values
  int total = 0;
  int breath;
  for (int i = 0; i < 1000; i++) {
    breath = map(pressure, firstBreath, pressureMax, 0, 127);
    total += constrain(breath, 0, 127);
  }
  breathVal = total / 1000; //Set breathVal variable to be used elsewhere
}

void controlCC() {
  usbMIDI.sendControlChange(7, breathVal, 1);  //Controls MIDI Volume based on breath readings
}

void playNote() { 
  prevNote = currentNote;
  currentNote = getNote(); // Check to see if note has changed
  if (currentNote != prevNote) {   //If note has changed, turn off previous note and start new note. This only sends the MIDI data when there is a change instead of constantly sending data
    usbMIDI.sendNoteOff(prevNote, 127, 1);
    usbMIDI.sendNoteOn(currentNote, 127, 1);
  }
}

void createFingerArray() {
  for (int i = 0; i < 24; i++) {
    activeFingering[i] = digitalRead(buttonPins[i]); //Updates activeFingering[] based on current button readings
  }
  delay(5);
}

int getNote() {
  for (int i = 0; i < 74; i++) { //Checks all 74 fingering arrays to compare
    bool boolean = true;
    for (int j = 0; j < 24; j++) { //Checks every position to see if activeFingering matches that array
      if (activeFingering[j] != fingering[i][j]) {
        boolean = false;
        continue;// If activeFingering isn't the fingering continue
      }
      if (j == 23 and boolean == true) {
        return notes[i]-2; //If fingerings match and a previous button has not been marked a false return the note associated with that array
      }
    }
  }
  return 77;  //open G if fingering doesn't exist
}
