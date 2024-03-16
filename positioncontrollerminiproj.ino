#define CW 0
#define CCW 1

#define STEPS_PER_REV 2038

int pinA = 11;
int pinB = 10;
int pinC = 9;
int pinD = 8;

int waitms = 10;


void setup() {
  // put your setup code here, to run once:
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);

  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
}

void loop() {
  //rotateRPM(15, CW, 3);
  //rotateRPM(5, CCW, 2);
  rotatePosition(CW, 90);
  rotatePosition(CCW, 180);
}

void fullStep(bool dir){

  static int step = 0;

  switch(step){

      case 0:
      //Step 1
        digitalWrite(pinA, HIGH);
        digitalWrite(pinB, LOW);
        digitalWrite(pinC, LOW);
        digitalWrite(pinD, LOW);
        break;
      case 1:
      //Step 2
        digitalWrite(pinA, LOW);
        digitalWrite(pinB, HIGH);
        digitalWrite(pinC, LOW);
        digitalWrite(pinD, LOW);
        break;
      case 2:
      //Step 3
        digitalWrite(pinA, LOW);
        digitalWrite(pinB, LOW);
        digitalWrite(pinC, HIGH);
        digitalWrite(pinD, LOW);
        break;
      case 3:
      //Step 4
        digitalWrite(pinA, LOW);
        digitalWrite(pinB, LOW);
        digitalWrite(pinC, LOW);
        digitalWrite(pinD, HIGH);
        break;
      default:
        digitalWrite(pinA, LOW);
        digitalWrite(pinB, LOW);
        digitalWrite(pinC, LOW);
        digitalWrite(pinD, LOW);
    }
      if (dir == CW){
      step ++;
      step %= 4;
    }
      else //For CCW direction
    {
      if (step==0){
        step = 3;
      }
      else
      {
        step--;
      }
    }
}

void rotateRPM(int rpm, bool dir, int numRotate){
  uint32_t period = 60000000 / rpm; // in microseconds
  uint32_t delayTime = period / STEPS_PER_REV; // in microseconds


  for(uint32_t i = 0; i < numRotate; i++)
  {
    for(uint32_t ii = 0; ii< STEPS_PER_REV; ii++){
      fullStep(dir);
      delayMicroseconds(delayTime);
    }
  }
}

void rotatePosition(bool dir, uint32_t angle)
{
  uint32_t numSteps = (angle * STEPS_PER_REV) / 360;

  for (uint32_t i = 0; i < numSteps; i++)
  {
    fullStep(dir);
    delay(2);
  }
}