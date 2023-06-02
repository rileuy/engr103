#include <Adafruit_CircuitPlayground.h>

volatile bool switchState = 0;
volatile bool switchFlag = 0;
int score;
float level;


void setup() {

pinmode (4, INPUT_PULLDOWN); //start button = 7
pinmode (5, INPUT_PULLDOWN); // reset game button = 5
pinmode (7, IMPUT_PULLUP); // Display current or highest score in LED form. will choose one. 

attachInterrupt(digitalPinToInterrupt(4), start, RISING);
attachInterrupt(digitalPinToInterrupt(5), reset, RISING);
 attachInterrupt(digitalPinToInterrupt(7), score, CHANGE);

randomSeed(analogRead(0));

  switchState = digitalRead(7);

Serial.print("Score: "); // print score


}

void loop() {
if(score) {


}

}

void buttonsTouched() {
  uint8_t 
}

void simonGame(){
case 1:


}
void currentScore() {

}

void start() {
  buttonA = 1;
}

void reset() {
  buttonB = 1;
}

void score() {
  delay(50); 
    switchFlag = true;
  
}