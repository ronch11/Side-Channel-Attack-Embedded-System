// Include the Keypad library
#include <Keypad.h>

// Declare the PWM pin for the buzzer
const int buzzerPin = 12;

// Constants for row and column sizes
const byte ROWS = 4;
const byte COLS = 4;

// Array to represent keys on keypad
char hexaKeys[ROWS][COLS] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Connections to Arduino
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

// Create keypad object
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// Setup function for the Arduino
void setup()
{
  // Setup serial monitor
  Serial.begin(9600);  
}

// Main loop function
void loop()
{
  // Get key value if pressed
  char customKey = customKeypad.getKey();

  // If a key is pressed
  if (customKey) {
    
    // Print key value to serial monitor
    Serial.println(customKey);

    // Make a sound corresponding to the key
    makeButtonSound(customKey);
  }
}

// Function to make a sound corresponding to the button pressed
void makeButtonSound(char button)
{
  // Each button corresponds to a different frequency
  if (button == '1') { return makeSound(1000); }
  if (button == '2') { return makeSound(500); }
  if (button == '3') { return makeSound(600); }
  if (button == '4') { return makeSound(900); }
  if (button == '5') { return makeSound(1100); }
  if (button == '6') { return makeSound(700); }
  if (button == '7') { return makeSound(800); }
  if (button == '8') { return makeSound(1200); }
  if (button == '9') { return makeSound(1400); }
  if (button == '0') { return makeSound(1300); }
  if (button == 'C') { return makeSound(29); }
  if (button == 'D') { 
    // For button 'D', make a sequence of sounds
    for (int i=20; i<30; i++){
      makeSound(i);
      delay(80);
    }
  }
}

// Function to make a sound at a given frequency
void makeSound(int indexOfBeep)
{
  // Start the tone
  tone(buzzerPin, indexOfBeep);
  // Wait for a while
  delay(750);
  // Stop the tone
  noTone(buzzerPin);
  // Wait for a while
  delay(100);
}
