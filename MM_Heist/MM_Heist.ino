#include <stdio.h>

// variable declarations and initialisations
const float pi = 3.14159;

float timestep = 1; // microseconds

float rangeDAC = 4095;
int settingDAC =0;

float inputTimeSine = 0.0;
float outputTimeSine = 0.0;

float inputFreqSine = 0.0;
float outputFreqSine = 0.0;
float frequencyFreqSine = 2;
float minFreqSine = 25;
float maxFreqSine = 500;

///////////////////////////////////////////////////////////////////////

// the setup function runs once when you press reset or power the board
void setup() {
  // maximise resolution of the DACs
  analogWriteResolution(12);
  // enable serial communications for console
  Serial.begin(9600); // open the serial port at 9600 bps
}

// the loop function runs over and over again forever
void loop() {
  inputFreqSine += (2*pi*frequencyFreqSine*timestep/1000.0);
  outputFreqSine = (0.5*(sin(inputFreqSine)+1.0))*(maxFreqSine-minFreqSine) + minFreqSine;
  
  inputTimeSine += (2*pi*outputFreqSine*timestep/1000.0);
  outputTimeSine = 0.5*(sin(inputTimeSine)+1.0);
  settingDAC = outputTimeSine*rangeDAC;
  delay(timestep);
  
  analogWrite(DAC0, settingDAC); 

//Serial.print(settingDAC);
//Serial.print("\n\r");

}

