#include <MotorDriver.h>
#include <seeed_pwm.h>
#include <FastLED.h>

#define NUM_LEDS 56 // Number of LEDs in the strip
#define DATA_PIN 7  // LED strip control pin

CRGB leds[NUM_LEDS]; // 


// Control Pin Variables
const int hrPin = A0; // Heart rate sensor pin: Analog Input
const int potPin = A1; // Potentiometer pin: Analog Output
const int enPin = 6; // Button pin: Digital Input

// Initialise variables
volatile int bpm = 0; // PWM duty cycle
int bright = 0; // LED strip brightness
int hue = 25; // LED strip hue
int saturation = 255; // LED strip saturation
int buttonState = 0; // Button state

MotorDriver motor; // Initalise object using library

void setup()
{
  Serial.begin(9600); 

  
  motor.begin(); // Initalise motor
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); // Initialise LED strip

  
  // Initialise control pins
  pinMode(hrPin, INPUT);
  pinMode(potPin, INPUT);
  pinMode(enPin, INPUT);
  

  for (int i = 0; i < NUM_LEDS; i = i + 1){  // Turn on LEDs one by one
    leds[i] = CRGB(255,0,0); 
    FastLED.show();
    delay(50);
  }
  
    
}

void loop()
{
  bpm = 65; // PWM which results in BPM of ~30
  
  buttonState = digitalRead(enPin); // Check button position
  
  motor.speed(0, bpm); // Motor 0 has a PWM = bpm
  FastLED.showColor(CHSV(hue, saturation, 50));
  
  
  while (buttonState == HIGH){ // When button is pressed
    Serial.println(bpm);
    if (bpm == 65){ // If heartbeat has not been measured
      bpm = map(analogRead(hrPin), 0, 627, 65, 100); // Read value from heart rate sensor and map the values to effective PWM range
      bright = map(bpm, 0, 100, 50, 150); // Map the PWM values to LED brightness

      for (int i = 65; i < bpm; i = i + 1){  // Gradually increase Motor PWM and LED brightness from inital values to values from heart rate sensor
        motor.speed(0, i);
        bright = map(i, 65, bpm, 50, 150);
        FastLED.showColor(CHSV(hue, saturation, bright));
        Serial.println(i);
        delay(200);
       
      }
    } 

    buttonState = digitalRead(enPin); // Check button state
    if (buttonState == LOW){ // If button is released
      for (int i = bpm; i > 65; i = i - 1){ // Gradually reduce motor PWM and brightness back to inital values
        motor.speed(0, i);
        bright = map(i, 65, bpm, 50, 150);
        FastLED.showColor(CHSV(hue, saturation, bright));
        Serial.println(i);
        delay(200);
      }
    }
  }
  
    
}
// END FILE


