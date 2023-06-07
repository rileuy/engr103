//Riley Fitzsimonds
//ENGR 103 Final
//Simon Says - Memory Game

#include <Adafruit_CircuitPlayground.h>

volatile bool switchState = 0;
volatile bool switchFlag = 0;
volatile bool startB = false;
volatile bool resetB = false;
int score;
float level;
int sequence[100];
int sequenceLength = 0;

void setup() {
  CircuitPlayground.begin();
  CircuitPlayground.clearPixels(); // Clear pixels on startup

  pinMode(4, INPUT_PULLUP);   // start button = 4
  pinMode(5, INPUT_PULLUP);   // reset game button = 5
  pinMode(7, INPUT_PULLUP);   // Display current or highest score in LED form. Will choose one.

  attachInterrupt(digitalPinToInterrupt(4), start, RISING);
  attachInterrupt(digitalPinToInterrupt(5), reset, RISING);
  attachInterrupt(digitalPinToInterrupt(7), showScore, CHANGE);

  randomSeed(analogRead(0));

  switchState = digitalRead(7);

  Serial.begin(9600); 
  Serial.print("Score: "); // print score
  Serial.println(score);
}

void loop() {
  if (startB) {
    startB = false;
    resetB = false;
    score = 1;
    simonGame();
  }
  
  if (resetB) {
    resetB = false;
    sequenceLength = 0;
    score = 0;
  }
}

void simonGame() {
  if (sequenceLength == 0) {
    addToSequence();
  }

  for (int i = 0; i < sequenceLength; i++) {
    int button = sequence[i];
    switch (startB) {
      case 0:
        CircuitPlayground.setPixelColor(0, 255, 0, 0);  // Red
        delay(500);
        CircuitPlayground.clearPixels();
        delay(200);
        break;
      case 1:
        CircuitPlayground.setPixelColor(1, 0, 0, 255);  // Blue
        delay(500);
        CircuitPlayground.clearPixels();
        delay(200);
        break;
      case 2:
        CircuitPlayground.setPixelColor(2, 0, 255, 0);  // Green
        delay(500);
        CircuitPlayground.clearPixels();
        delay(200);
        break;
      case 3:
        CircuitPlayground.setPixelColor(3, 255, 255, 0);  // Yellow
        delay(500);
        CircuitPlayground.clearPixels();
        delay(200);
        break;
    }
    delay(300);
  }

  addToSequence();
}

void addToSequence() {
  int nextButton = random(4);
  sequence[sequenceLength] = nextButton;
  sequenceLength++;
}

void start() {
  startB = true;
}

void reset() {
  resetB = true;
}

void showScore() {
  delay(50);
  switchFlag = true;   // Show current or highest score using LEDs
}
