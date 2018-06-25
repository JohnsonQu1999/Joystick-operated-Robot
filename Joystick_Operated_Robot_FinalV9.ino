///////////////////////////////////////////
// Program Name: Joystick Operated Robot //
// Name: Johnson Qu                      //
///////////////////////////////////////////

const int numM = 4; //Number of Motor outputs
const int outM[numM] = /*{0, 1, 2, 3};*/ {8, 9, 10, 11}; //Pins of Motor Outputs

const int numSM = 4; //Number of Stepper Motor outputs
const char outSM[numSM] = {A0, A1, A2, A3}; //Pins of Stepper Motor Outputs

const int numJ = 6; //Number of Joystick inputs
int inJHOL[numJ]; //Input Joystick High Or Low (stores state of inputs)
const int inJ[numJ] = {2, 3, 4, 5, 6, 7}; //Pins of Joystick Inputs
//2-5 = joystick; 6 = button 1; 7 = button 2
//inJ[0] = forwards; [1] = right; [2] = back; [3] = left

const int delayTimeAll = 10; //default = 10
const int delayTimeStepper = 50; // default = 50

boolean changed = true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  for (int a = 0; a < numM; a++) {
    pinMode(outM[a], OUTPUT);
  }
  for (int a = 0; a < numSM; a++) {
    pinMode(outSM[a], OUTPUT);
  }
  for (int a = 0; a < numJ; a++) {
    pinMode(inJ[a], OUTPUT);
    inJHOL[a] = 0;

  }

  void loop() {

    if (inJHOL[0] != digitalRead(inJ[0]) || inJHOL[1] != digitalRead(inJ[1]) || inJHOL[2] != digitalRead(inJ[2]) || inJHOL[3] != digitalRead(inJ[3])) {
      changed = true;

      if (debug)
        Serial.println("changed = true");
    }

    if (changed) {
      reset();
      changed = false;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////

    inJHOL[0] = digitalRead(inJ[0]); //forwards
    inJHOL[1] = digitalRead(inJ[1]); //right
    inJHOL[2] = digitalRead(inJ[2]); //back
    inJHOL[3] = digitalRead(inJ[3]); //left
    inJHOL[4] = digitalRead(inJ[4]); //button 1 up
    inJHOL[5] = digitalRead(inJ[5]); //button 2 down

    ///////////////////////////////////////////////////////////////////////////////////////////

    if (inJHOL[0] == 1 && inJHOL[1] == 1 && inJHOL[2] == 1 && inJHOL[3] == 1) {
      Serial.println("ALL INPUTS ARE HIGH. SOMETHING HAS GONE WRONG. STOP TRYING TO BREAK THE PROGRAM.");
      reset();
    }
    else if (inJHOL[0] == 1 && inJHOL[1] == 1) {
      //FORWARDS/RIGHT

      digitalWrite(outM[0], HIGH);
      digitalWrite(outM[1], LOW);
    }
    else if (inJHOL[1] == 1 && inJHOL[2] == 1) {
      //BACKWARDS/RIGHT

      digitalWrite(outM[0], LOW);
      digitalWrite(outM[1], HIGH);
    }
    else if (inJHOL[2] == 1 && inJHOL[3] == 1) {
      //BACKWARDS/LEFT

      digitalWrite(outM[2], LOW);
      digitalWrite(outM[3], HIGH);
    }
    else if (inJHOL[3] == 1 && inJHOL[0] == 1) {
      //FORWARDS/LEFT

      digitalWrite(outM[2], HIGH);
      digitalWrite(outM[3], LOW);
    }
    else if (inJHOL[0] == 1) {
      //FORWARDS

      digitalWrite(outM[0], HIGH);
      digitalWrite(outM[2], HIGH);
    }
    else if (inJHOL[1] == 1) {
      //RIGHT

      digitalWrite(outM[0], HIGH);
      digitalWrite(outM[3], HIGH);
    }
    else if (inJHOL[2] == 1) {
      //BACK

      digitalWrite(outM[1], HIGH);
      digitalWrite(outM[3], HIGH);
    }
    else if (inJHOL[3] == 1) {
      //LEFT

      digitalWrite(outM[1], HIGH);
      digitalWrite(outM[2], HIGH);
    }

    ///////////////////////////////////////////////////////////////////////////////////////////

    if (inJHOL[4] == 1) {
      //step 0
      Serial.println("step 0");
      digitalWrite(outSM[0], HIGH);
      digitalWrite(outSM[1], LOW);
      digitalWrite(outSM[2], HIGH);
      digitalWrite(outSM[3], LOW);
      delay(delayTimeStepper);
      //step 1
      Serial.println("step 1");
      digitalWrite(outSM[0], LOW);
      digitalWrite(outSM[1], HIGH);
      digitalWrite(outSM[2], HIGH);
      digitalWrite(outSM[3], LOW);
      delay(delayTimeStepper);
      //step 2
      Serial.println("step 2");
      digitalWrite(outSM[0], LOW);
      digitalWrite(outSM[1], HIGH);
      digitalWrite(outSM[2], LOW);
      digitalWrite(outSM[3], HIGH);
      delay(delayTimeStepper);
      //step 3
      Serial.println("step 3");
      digitalWrite(outSM[0], HIGH);
      digitalWrite(outSM[1], LOW);
      digitalWrite(outSM[2], LOW);
      digitalWrite(outSM[3], HIGH);
      delay(delayTimeStepper);
    }
    else if (inJHOL[5] == 1) {
      //step 3
      Serial.println("step 3");
      digitalWrite(outSM[0], HIGH);
      digitalWrite(outSM[1], LOW);
      digitalWrite(outSM[2], LOW);
      digitalWrite(outSM[3], HIGH);
      delay(delayTimeStepper);
      //step 2
      Serial.println("step 2");
      digitalWrite(outSM[0], LOW);
      digitalWrite(outSM[1], HIGH);
      digitalWrite(outSM[2], LOW);
      digitalWrite(outSM[3], HIGH);
      delay(delayTimeStepper);
      //step 1
      Serial.println("step 1");
      digitalWrite(outSM[0], LOW);
      digitalWrite(outSM[1], HIGH);
      digitalWrite(outSM[2], HIGH);
      digitalWrite(outSM[3], LOW);
      delay(delayTimeStepper);
      //step 0
      Serial.println("step 0");
      digitalWrite(outSM[0], HIGH);
      digitalWrite(outSM[1], LOW);
      digitalWrite(outSM[2], HIGH);
      digitalWrite(outSM[3], LOW);
      delay(delayTimeStepper);
    }
    else {
      digitalWrite(outSM[0], LOW);
      digitalWrite(outSM[1], LOW);
      digitalWrite(outSM[2], LOW);
      digitalWrite(outSM[3], LOW);
    }

    ///////////////////////////////////////////////////////////////////////////////////////////

    delay(delayTimeAll);
  }

  void reset() {
    digitalWrite(outM[0], LOW);
    digitalWrite(outM[1], LOW);
    digitalWrite(outM[2], LOW);
    digitalWrite(outM[3], LOW);
  }
