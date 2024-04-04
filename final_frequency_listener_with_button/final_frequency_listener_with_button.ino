#include "arduinoFFT.h"

#define SAMPLES 128
#define SAMPLING_FREQUENCY 2048

arduinoFFT FFT = arduinoFFT();

unsigned int samplingPeriod;
unsigned long microSeconds;

double vReal[SAMPLES];
double vImg[SAMPLES];

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 11;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// default of the password will be -2...
int buttonPassword[4] = {-2, -2, -2, -2};

double button0Frequency = 1300;
double button1Frequency = 1000;
double button2Frequency = 500;
double button3Frequency = 600;
double button4Frequency = 900;
double button5Frequency = 1100;
double button6Frequency = 700;
double button7Frequency = 800;
double button8Frequency = 1200;
double button9Frequency = 1400;

int mapNoiseToButton(double noise, double treshold=30)
{
  
  if ((noise < (button0Frequency + treshold)) && (noise > (button0Frequency - treshold))) { return 0; }
  if ((noise < (button1Frequency + treshold)) && (noise > (button1Frequency - treshold))) { return 1; }
  if ((noise < (button2Frequency + treshold)) && (noise > (button2Frequency - treshold))) { return 2; }
  if ((noise < (button3Frequency + treshold)) && (noise > (button3Frequency - treshold))) { return 3; }
  if ((noise < (button4Frequency + treshold)) && (noise > (button4Frequency - treshold))) { return 4; }
  if ((noise < (button5Frequency + treshold)) && (noise > (button5Frequency - treshold))) { return 5; }
  if ((noise < (button6Frequency + treshold)) && (noise > (button6Frequency - treshold))) { return 6; }
  if ((noise < (button7Frequency + treshold)) && (noise > (button7Frequency - treshold))) { return 7; }
  if ((noise < (button8Frequency + treshold)) && (noise > (button8Frequency - treshold))) { return 8; }
  if ((noise < (button9Frequency + treshold)) && (noise > (button9Frequency - treshold))) { return 9; }

  return -1;
}


// variables will change:
int currButtonState, prevButtonState = LOW;         // variable for reading the pushbutton status
int ledState = LOW;

void setup()
{
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  
  Serial.begin(115200);
  // samplingPeriod = round(1000000 *(1.0/SAMPLING_FREQUENCY)); 
  samplingPeriod = round(489);  
}

void loop()
{

  int indexOfPassword = 0;
  for(int i=0; i < 5; i++)
  {

    // read the state of the pushbutton value:
    currButtonState = digitalRead(buttonPin);
    if (prevButtonState == LOW && currButtonState == HIGH)
    {
      ledState = !ledState;
      // turn LED on:
      digitalWrite(ledPin, ledState);
      delay(200);
    

    
      double noiseFrequency = 0;
      for(int j=0; j<2; j++)
      {
        noiseFrequency += listenToFrequency();
        Serial.println("the 1//2 frequency is:");
        Serial.println(noiseFrequency);
      }
      Serial.println("the total frequency is:");
      double finalNoiseFrequency = noiseFrequency/2;
      Serial.println(finalNoiseFrequency);
      int currentButtonOfNoise = mapNoiseToButton(finalNoiseFrequency);
      if (currentButtonOfNoise != -1)
      {
         buttonPassword[indexOfPassword] = currentButtonOfNoise;
         indexOfPassword += 1;
         Serial.println("got a button!!! waiting a 2 second to the next one...\n");
         delay(1500);
         Serial.println("starting the next one");
         delay(500);
      }
      if (indexOfPassword >= 4)
      { // end of the length of the password - find all the buttons...
        break;
      }
    }
    else
    {
      i -= 1;
    }
  }
  Serial.println("progress done!!!\n\n");
  for(int i=0; i<4; i++)
  {
    Serial.println(buttonPassword[i]);
  }

  for(int i = 1; i < 5; i++)
  {
    if (buttonPassword[i - 1] != i)
    {
      Serial.println("Wrong password.");
      break;
    }

    else if (i == 4)
    {
      Serial.println("Correct password! the password is 1, 2, 3, 4");
    }
  }

  while(1);
}

double listenToFrequency()
{
  for(int i = 0; i< SAMPLES; i++)
  {
    microSeconds = micros();
    
    vReal[i] = analogRead(0);
    vImg[i] = 0;
    
    
    while(micros() < (microSeconds + samplingPeriod))
    {
      // do nothing     
    }   
  }
  
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImg, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImg, SAMPLES);
  
  
  double peak  = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
  Serial.println(peak);
  
//  while (1);
  Serial.println("Done.\n");
  delay(1000);
  Serial.println("starting more one...");
  
  if (peak < 485 || peak > 1425)
  {
    Serial.println("below 485, or above 1425...");
    Serial.println(peak);
    Serial.println("\n");
    return listenToFrequency();
  }
  return peak;
}
