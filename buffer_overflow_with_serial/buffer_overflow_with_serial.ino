// Define the length of the buffer
#define BUFFER_LENGTH   32

// Setup function for the Arduino
void setup() {
  // Begin serial communication at 115200 baud
  Serial.begin(115200);
  // Wait for a second
  delay(1000);
  // Print welcome message
  Serial.println("Welcome to our CTF, let's start the challenge\n");
  // Wait for a short while
  delay(100);
}

// Main loop function
void loop() {
  // Wait for 5 seconds
  delay(5000);
  // Declare the buffer and unlocked_flags arrays
  char buff[BUFFER_LENGTH] = {0};
  uint8_t unlocked_flags[64] = {0};
  // Record the start time
  int start = millis();
  int index = 0;
  // Ask the user to enter the password
  Serial.println("Enter your password");
  // Wait for 5 seconds for the user to enter the password
  while((millis() - start) < 5000)
  {
    // If the user has entered something
    if(Serial.available())
    {
      // Read the entered character into the buffer
      buff[index++] = Serial.read();
    }
  }
  
  // If the entered password matches "super_secret"
  if(strcmp("super_secret", buff) == 0)
  {
    // Print a success message
    Serial.println("Password correct!");
    // Set the first flag as unlocked
    unlocked_flags[0] = 1;
  }
  

  // If the first flag is unlocked
  if(unlocked_flags[0])
  {
    // Print a success message
    Serial.println("UNLOCKED!!!!");
    delay(500);
    // Encourage the user to proceed to the next level
    Serial.println("Let's keep on to next level");
    delay(500);
    // Print the key for the next level
    Serial.print("Your key is: ");
    Serial.println((uint32_t) unlocked_flags);
    delay(5000);
    // Remind the user to save the key for the next level
    Serial.println("Save him, you will need him on the next level");
    // Wait for a long while before repeating the loop
    delay(500000);
  }
  else
  {
    // If the first flag is not unlocked, print a failure message
    Serial.println("Still locked...");
  }
}
