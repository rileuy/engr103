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

  pinMode(7, INPUT_PULLUP);

  switchState = CircuitPlayground.slideSwitch();
  delay(1000);
}

void loop() {
  switchState = CircuitPlayground.slideSwitch();
  rCounter = 0;
  lCounter = 0;

  if (!lost) {
    int i;
    buttonPress = false;

    for (i = 0; i < difficulty; i++) {
      currNum = GenState();
      if (currNum == 0) {
        rCounter++;
        CircuitPlayground.strip.setPixelColor(9, 255, 0, 0); // Turn on the LED on the right side (NeoPixel index 9)
        CircuitPlayground.redLED(true); // Turn on the red LED
        CircuitPlayground.strip.show(); // Update the NeoPixel LEDs
        delay(500); // Adjust the delay as needed
        CircuitPlayground.strip.setPixelColor(9, 0); // Turn off the LED
        CircuitPlayground.redLED(false); // Turn off the red LED
        CircuitPlayground.strip.show(); // Update the NeoPixel LEDs
      } else {
        lCounter++;
        CircuitPlayground.strip.setPixelColor(0, 0, 0, 255); // Turn on the LED on the left side (NeoPixel index 0)
        CircuitPlayground.redLED(true); // Turn on the blue LED
        CircuitPlayground.strip.show(); // Update the NeoPixel LEDs
        delay(500); // Adjust the delay as needed
        CircuitPlayground.strip.setPixelColor(0, 0); // Turn off the LED
        CircuitPlayground.redLED(false); // Turn off the blue LED
        CircuitPlayground.strip.show(); // Update the NeoPixel LEDs
      }
      delay(200);
    }

    Serial.print("Left Counter: ");
    Serial.println(lCounter);
    Serial.print("Right Counter: ");
    Serial.println(rCounter);

    if (rCounter == lCounter) {
      rCounter++;
    }

    while (!buttonPress) {
      if (CircuitPlayground.rightButton() && !buttonPress) {
        buttonPress = true;
        if (rCounter > lCounter) {
          ++difficulty;
          delay(50);
        } else {
          lost = true;
        }
      }
      if (CircuitPlayground.leftButton() && !buttonPress) {
        buttonPress = true;
        if (lCounter > rCounter) {
          ++difficulty;
          delay(50);
        } else {
          lost = true;
        }
      }
    }
  }
}

int GenState() {
  int randNum;
  randNum = random(0, 2);
  return randNum;
}
