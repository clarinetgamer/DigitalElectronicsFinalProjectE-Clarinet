int buttonPins[24] = { 23, 22, 20, 21, 19, 18, 17, 40, 39, 38, 33, 34, 36, 35, 37, 41, 32, 31, 30, 29, 28, 27, 25, 26 };
int concertVsBbSwitch = 13;
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

void setup() {
  for (int i = 0; i < 24; i++) {
    pinMode(buttonPins[i], INPUT);
  }
  pinMode(concertVsBbSwitch, INPUT);
  Serial.begin(9600);
}

void loop() {
  createFingerArray();
  getBreathVal();
  Serial.println(getNote());
  playNote();
  controlCC();
}

void getBreathVal() {
  breathVal = map(analogRead(A2), 0, 1023, 0, 127);
}

void controlCC() {
  usbMIDI.sendControlChange(7, breathVal, 1);   //Volume
  usbMIDI.sendControlChange(2, breathVal, 1);   //Breath
  usbMIDI.sendControlChange(11, breathVal, 1);  //Expression
}

void playNote() {
  prevNote = currentNote;
  if (digitalRead(concertVsBbSwitch) == HIGH) {
    currentNote = getNote();  //concert
  } else {
    currentNote = getNote() - 2;  //Bb
  }
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
        return notes[i];
      }
    }
  }
  return 67;  //open G if fingering doesn't exist
}
