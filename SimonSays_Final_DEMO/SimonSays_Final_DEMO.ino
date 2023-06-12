// Riley Fitzsimonds
// ENGR 103 Final
// Memory Counter Game

#include <Adafruit_CircuitPlayground.h>

bool switchState = 0;
bool switchFlag = 0;
bool rightB = false;
bool leftB = false;
int score;
float level;
int sequence[100];
int sequenceLength = 0;
int currentButtonIndex = 0; //ignore

void setup()
{
  CircuitPlayground.begin();
  CircuitPlayground.clearPixels(); // Clear pixels on startup

  randomSeed(analogRead(0));

  switchState = digitalRead(7);

  Serial.begin(9600);
}

void loop()
{
  if (digitalRead(7) != switchState)
  {
    switchState = !switchState;
    if (switchState == HIGH)
    {
      switchFlag = true;
    }
  }

  if (CircuitPlayground.leftButton())
  {
    leftB = true;
    CircuitPlayground.clearPixels(); // Clear the pixels immediately
    delay(100);                     // Delay to provide some feedback to the player
  }

  if (CircuitPlayground.rightButton())
  {
    rightB = true;
  }

  if (switchFlag)
  {
    switchFlag = false;
    rightB = false;
    leftB = false;
    score = 1;
    simonGame();
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
      delay(500);
      CircuitPlayground.clearPixels();
      delay(200);
      break;
    case 1:
      CircuitPlayground.setPixelColor(6, 0x808000);
      CircuitPlayground.setPixelColor(7, 0x00FF00);
      CircuitPlayground.setPixelColor(8, 0x008080);
      CircuitPlayground.setPixelColor(9, 0x0000FF);
      delay(500);
      CircuitPlayground.clearPixels();
      delay(200);
      break;
    }
    delay(300);
    CircuitPlayground.clearPixels(); // Clear the displayed button
    delay(100);                     // Delay between button display and player input

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
  int nextButton = random(2);
  sequence[sequenceLength] = nextButton;
  sequenceLength++;
}
