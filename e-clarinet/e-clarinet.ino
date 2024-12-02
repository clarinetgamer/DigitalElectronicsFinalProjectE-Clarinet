#include <Wire.h>
#include "Adafruit_MPRLS.h"

// You dont *need* a reset and EOC pin for most uses, so we set to -1 and don't connect
#define RESET_PIN -1  // set to any GPIO pin # to hard-reset on begin()
#define EOC_PIN -1    // set to any GPIO pin to read end-of-conversion by pin
Adafruit_MPRLS mpr = Adafruit_MPRLS(RESET_PIN, EOC_PIN);

int buttonPins[24] = { 23, 22, 20, 21, 16, 15, 14, 40, 39, 38, 33, 34, 36, 35, 37, 41, 32, 31, 30, 29, 28, 27, 25, 26 };
bool activeFingering[24] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
//temp input velocity is A2
//{registerKey,thumbKey,leftSideKey,aKey,oneKey,twoKey,bananaTopKey,threeKey,cSharpKey,leftPinkyExt1,leftPinkyExt2,leftPinkyExt3,sideKey1,sideKey2,sideKey3,sideKey4,fourKey,fiveKey,bananaLowKey,sixKey,ebKey,rightPinky1,rightPinky2,rightPinky3}
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
int notes[74] = { 64, 64, 64, 65, 65, 66, 66, 66, 67, 68, 69, 70, 71, 71, 72, 73, 74, 75, 75, 75, 76, 77, 78, 78, 79, 80, 81, 82, 82, 83, 83, 83, 84, 84, 85, 85, 85, 86, 87, 88, 89, 90, 90, 91, 92, 93, 94, 94, 94, 94, 95, 96, 97, 98, 99, 99, 99, 100, 101, 101, 102, 102, 103, 103, 103, 103, 104, 104, 105, 105, 106, 106, 107, 108 };
int currentNote = 67;
int prevNote = 67;
int breathVal = 0;
float firstBreath;
float pressureMax;

void setup() {
  for (int i = 0; i < 24; i++) {
    pinMode(buttonPins[i], INPUT);
  }
  Serial.begin(9600);
  if (!mpr.begin()) {
    Serial.println("Failed to communicate with MPRLS sensor, check wiring?");
    while (1) {
      delay(10);
    }
  }
  delay(1000);
  firstBreath = mpr.readPressure();
  pressureMax = firstBreath + 22;
}

void loop() {
  createFingerArray();
  playNote();
  Serial.println(getNote());
  getBreathVal();
  if (millis() % 50 == 0) {
    controlCC();
  }
}

void getBreathVal() {
  float pressure = mpr.readPressure();

  int total = 0;
  int breath;
  for (int i = 0; i < 1000; i++) {
    breath = map(pressure, firstBreath, pressureMax, 0, 127);
    total += constrain(breath, 0, 127);
  }
  breathVal = total / 1000;
}

void controlCC() {
  usbMIDI.sendControlChange(7, breathVal, 1);  //Volume
}

void playNote() {
  prevNote = currentNote;
  currentNote = getNote();
  if (currentNote != prevNote) {
    usbMIDI.sendNoteOff(prevNote, 127, 1);
    usbMIDI.sendNoteOn(currentNote, 127, 1);
  }
}

void createFingerArray() {
  for (int i = 0; i < 24; i++) {
    activeFingering[i] = digitalRead(buttonPins[i]);
  }
  delay(5);
}

int getNote() {
  for (int i = 0; i < 74; i++) {
    bool boolean = true;
    for (int j = 0; j < 24; j++) {
      if (activeFingering[j] != fingering[i][j]) {
        boolean = false;
        continue;
      }
      if (j == 23 and boolean == true) {
        return notes[i]-2;
      }
    }
  }
  return 77;  //open G if fingering doesn't exist
}
