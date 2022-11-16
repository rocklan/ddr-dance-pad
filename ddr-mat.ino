#include "Keyboard.h"

// the number of the onboard LED pin
const int ledPin = 13;    

// these are the inputs on the arduino that we expect the pads to be wired into
int buttonPin[6]        = {2, 4, 6, 8, 10, 12};

// current button states
int buttonState[6]      = {1, 1, 1, 1, 1, 1};

// previous button states
int prevButtonState[6]  = {1, 1, 1, 1, 1, 1};

// these are the keys that are simulated by the keypad
int keyboardButtons[6]  = {KEY_RIGHT_ARROW, KEY_DOWN_ARROW, KEY_UP_ARROW, KEY_PAGE_DOWN, KEY_PAGE_UP, KEY_LEFT_ARROW};

// flag indicating that at least one button is pressed, if true, we light up the onboard LED
bool buttonPressed;

void setup() {

  // initialize the onboard LED pin as an output  
  pinMode(ledPin, OUTPUT);                  
  
  // initialize the 6 inputs as pullup inputs
  for (int i=0;i<6;i++) {
    pinMode(buttonPin[i], INPUT_PULLUP); 
  }

  // Initialise keyboard
  Keyboard.begin();
}

void loop() {

  buttonPressed = false;

  // read the state of the input buttons
  for (int i=0;i<6;i++) {

    buttonState[i] = digitalRead(buttonPin[i]);

    if (buttonState[i] == LOW)
    {
      digitalWrite(ledPin, HIGH);  // turn led on
      buttonPressed = true;
    }

    // If a button has changed state and it's pressed
    if (buttonState[i] != prevButtonState[i] && buttonState[i] == LOW)
    {
        Keyboard.press(keyboardButtons[i]);
        prevButtonState[i] = buttonState[i];
    }

    // If a button has changed state and it's released
    if (buttonState[i] != prevButtonState[i] && buttonState[i] == HIGH)
    {
        Keyboard.release(keyboardButtons[i]);
        prevButtonState[i] = buttonState[i];
    }
  }

  // If none of the buttons are pressed, turn off the LED
  if (!buttonPressed)
  {
    digitalWrite(ledPin, LOW);
  }
}
