// Riley Fitzsimonds
// ENGR 103 Final
// Memory Counter Game

#include <Adafruit_CircuitPlayground.h>

volatile bool switchState = 0;
volatile bool switchFlag = 0;
volatile bool rightB = false;
volatile bool leftB = false;
int score;
float level;
int sequence[100];
int sequenceLength = 0;
int currentButtonIndex = 0; // Track the current button in the sequence

void setup()
{
  CircuitPlayground.begin();
  CircuitPlayground.clearPixels(); // Clear pixels on startup

  pinMode(4, INPUT_PULLUP); // right button = 4
  pinMode(5, INPUT_PULLUP); // left button = 5
  pinMode(7, INPUT_PULLUP); // switch

  attachInterrupt(digitalPinToInterrupt(4), right, RISING);
  attachInterrupt(digitalPinToInterrupt(5), left, RISING);
  attachInterrupt(digitalPinToInterrupt(7), ISR_Switch, CHANGE);

  randomSeed(analogRead(0));

  switchState = digitalRead(7);

  Serial.begin(9600);
}

void loop()
{
  if (switchFlag)
  {
    switchFlag = false;
    rightB = false;
    leftB = false;
    score = 1;
    simonGame();
  }

  if (leftB)
  {
    leftB = false;
    sequenceLength = 0;
    score = 0;
  }
}

void indicateButton(uint8_t b, uint16_t duration)
{
  CircuitPlayground.clearPixels();
  CircuitPlayground.setPixelColor(b, 255, 255, 255); // White
  delay(duration);
  CircuitPlayground.clearPixels();
  delay(200);
}

void simonGame()
{
  if (sequenceLength == 0)
  {
    addToSequence();
  }

  for (int i = 0; i < sequenceLength; i++)
  {
    int button = sequence[i];
    switch (button)
    {
    case 0:
      CircuitPlayground.setPixelColor(0, 255, 0, 0);
      CircuitPlayground.setPixelColor(1, 128, 128, 0);
      CircuitPlayground.setPixelColor(2, 0, 255, 0);
      CircuitPlayground.setPixelColor(3, 0, 128, 128);
      CircuitPlayground.setPixelColor(4, 0, 0, 255);
      if (leftB) // if left button is pressed
      {
        // Next case
        continue;
      }
      else if (rightB) // if right button is pressed
      {
        // Stop and don't do anything
        return;
      }
      break;
    case 1:
      CircuitPlayground.setPixelColor(6, 0x808000);
      CircuitPlayground.setPixelColor(7, 0x00FF00);
      CircuitPlayground.setPixelColor(8, 0x008080);
      CircuitPlayground.setPixelColor(9, 0x0000FF);
      break;
    case 2:
      CircuitPlayground.setPixelColor(0, 255, 0, 0);
      CircuitPlayground.setPixelColor(1, 128, 128, 0);
      CircuitPlayground.setPixelColor(2, 0, 255, 0);
      CircuitPlayground.setPixelColor(3, 0, 128, 128);
      CircuitPlayground.setPixelColor(4, 0, 0, 255);
      break;
    case 3:
      CircuitPlayground.setPixelColor(6, 0x808000);
      CircuitPlayground.setPixelColor(7, 0x00FF00);
      CircuitPlayground.setPixelColor(8, 0x008080);
      CircuitPlayground.setPixelColor(9, 0x0000FF);
      break;
    }
    delay(300);
    CircuitPlayground.clearPixels(); // Clear the displayed button
    delay(100);                     // Delay between button display and player input

    // Check if the left button is pressed during the delay
    if (leftB)
    {
      leftB = false;
      CircuitPlayground.clearPixels(); // Clear the pixels immediately
      delay(100);                     // Delay to provide some feedback to the player
      continue;                       // Skip to the next button in the sequence
    }
  }

  addToSequence();
}

void addToSequence()
{
  int nextButton = random(4);
  sequence[sequenceLength] = nextButton;
  sequenceLength++;
}

void right()
{
  if (digitalRead(4) == HIGH)
  {
    rightB = true;
  }
}

void left()
{
  if (digitalRead(5) == HIGH)
  {
    leftB = true;
  }
}

void ISR_Switch()
{
  delay(50);

  if (digitalRead(7) == HIGH)
  {
    switchFlag = true;
  }
}
