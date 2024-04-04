#define BUFFER_LENGTH   32

void setup() {
  Serial.begin(115200);
  delay(1000);
   /*print welcome message*/
  Serial.println("Welcme to our CTF, let's start the chalenge\n");
  delay(100);
}

void loop() {
  delay(5000);
  char buff[BUFFER_LENGTH] = {0};
  uint8_t unlocked_flags[64] = {0};
  int start = millis();
  int index = 0;
  Serial.println("Enter your password");
  while((millis() - start) < 5000)
  {
    if(Serial.available())
    {
      buff[index++] = Serial.read();
    }
  }
  
  if(strcmp("super_secret", buff) == 0)
  {
    Serial.println("Password correct!");
    unlocked_flags[0] = 1;
  }
  

  if(unlocked_flags[0])
  {
    Serial.println("UNLOCKED!!!!");
    delay(500);
    Serial.println("Let's keep on to next 1eve1");
    delay(500);
    Serial.print("Your key is: ");
    Serial.println((uint32_t) unlocked_flags);
    delay(5000);
    Serial.println("Save him, you will need him on the next level");
    delay(500000);

    
  }
  else
  {
    Serial.println("Still locked...");
  }

}
