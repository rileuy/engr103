#include <Adafruit_CircuitPlayground.h>

bool switchState;
int rCounter = 0;
int lCounter = 0;
volatile int difficulty = 3;
bool lost = false;
bool buttonPress;
int currNum;

void setup() {
  CircuitPlayground.begin();
  Serial.begin(9600);

  pinMode(7, INPUT_PULLDOWN);

  switchState = CircuitPlayground.slideSwitch();
  delay(1000);
}

void loop() {

  switchState = CircuitPlayground.slideSwitch();
  rCounter = 0;
  lCounter = 0;
  
  if(!lost) 
  {
    int i;
    buttonPress = false;

    for(i=0; i < difficulty; i++)
    {
      currNum = GenState();
      if (currNum == 0){
        rCounter++;
      }
      else {
        lCounter++;
      }

      delay(200);
    }
    Serial.println(lCounter);
    Serial.println(rCounter);

    if(rCounter == lCounter) {
      rCounter++;
    }

    while(!buttonPress)
    {
      if(CircuitPlayground.rightButton() && !buttonPress)
      {
        buttonPress = true;
        if(rCounter > lCounter){
          ++difficulty;
          delay(50);
      }
      else{
        lost = true;
      }
      }
    if(CircuitPlayground.leftButton() && !buttonPress)
    {
      buttonPress = true;
      if(lCounter > rCounter){
        ++difficulty;
        delay(50);
      }
      else{
        lost = true;
      }
    }
    }

  }

}

int GenState() {
  int randNum;
  randNum = random(0,2);

  return randNum;
}
