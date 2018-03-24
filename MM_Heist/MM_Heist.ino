#include <stdio.h>

// variable declarations and initialisations
const float pi = 3.14159;

float timestep = 1.0; // milliseconds

float rangeDAC0 = 4095.0;
int settingDAC0 = 0;
float rangeDAC1 = 3000.0;
int settingDAC1 = 0;

float alarmSecs = 0.0;
float alarmLimitSecs = 10.0;
float inputTimeSine = 0.0;
float outputTimeSine = 0.0;
float inputFreqSine = 0.0;
float outputFreqSine = 0.0;
float frequencyFreqSine = 2.0;
float minFreqSine = 25.0;
float maxFreqSine = 500.0;

float timeSecs = 0.0;
float timeLimitSecs = 60.0;

bool buttonState = 0;

///////////////////////////////////////////////////////////////////////

// the setup function runs once when you press reset or power the board
void setup() {
  // maximise resolution of the DACs (DAC0)
  analogWriteResolution(12);
  // enable serial communications for console
  Serial.begin(9600); // open the serial port at 9600 bps
  // set up button inputs (52,53)
  pinMode(52, INPUT_PULLUP);
  pinMode(53, INPUT_PULLUP);
  attachInterrupt(52, heistReset, FALLING);
  attachInterrupt(53, heistTrigger, FALLING);
  pinMode(24, INPUT_PULLUP);
  pinMode(25, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);
  pinMode(27, INPUT_PULLUP);
  attachInterrupt(24, heistTrigger, FALLING);
  attachInterrupt(25, heistTrigger, FALLING);
  attachInterrupt(26, heistTrigger, FALLING);
  attachInterrupt(27, heistTrigger, FALLING);
  pinMode(LED_BUILTIN, OUTPUT);
  timeSecs = 0.0;
  alarmSecs = 0.0;
}

// the loop function runs over and over again forever
void loop() {

  if (timeSecs < timeLimitSecs) {
    digitalWrite(LED_BUILTIN, LOW);
    timeSecs++;
    settingDAC1 = (timeSecs/timeLimitSecs)*rangeDAC1;
    analogWrite(DAC1, settingDAC1); 
    
    delay(1000);

    Serial.print(settingDAC1);
    Serial.print("\n\r");
  }
  else if ((timeSecs >= timeLimitSecs) & (alarmSecs < alarmLimitSecs)) {
    digitalWrite(LED_BUILTIN, HIGH);
    alarmSecs += timestep/1000.0;
    inputFreqSine += (2*pi*frequencyFreqSine*timestep/1000.0);
    outputFreqSine = (0.5*(sin(inputFreqSine)+1.0))*(maxFreqSine-minFreqSine) + minFreqSine;
    
    inputTimeSine += (2*pi*outputFreqSine*timestep/1000.0);
    outputTimeSine = 0.5*(sin(inputTimeSine)+1.0);
    settingDAC0 = outputTimeSine*rangeDAC0;
    delay(timestep);

    analogWrite(DAC0, settingDAC0);
    settingDAC1 = rangeDAC0;
    analogWrite(DAC1, settingDAC1); 
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
  }

}

void heistReset() {
  timeSecs = 0.0;
  alarmSecs = 0.0;
}

void heistTrigger() {
  timeSecs = timeLimitSecs;
  alarmSecs = 0.0;
}

