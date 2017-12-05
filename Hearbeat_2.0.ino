#include <MotorDriver.h>
#include <seeed_pwm.h>
#include <FastLED.h>

#define NUM_LEDS 56
#define DATA_PIN 7

CRGB leds[NUM_LEDS];


int hrPin = A0;
int potPin = A1;
const int enPin = 6;
int ledPin = 13;
volatile int bpm = 0;
int bright = 0;
int hue = 25;
int saturation = 255;
//int x = 2;
int accel = 0;
int buttonState = 0;

MotorDriver motor;

void setup()
{
  Serial.begin(9600);
  // initialize
  motor.begin();
  pinMode(hrPin, INPUT);
  pinMode(potPin, INPUT);
  pinMode(enPin, INPUT);
  pinMode(ledPin, OUTPUT);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  for (int i = 0; i < NUM_LEDS; i = i + 1){
    leds[i] = CRGB(255,0,0); 
    FastLED.show();
    delay(50);
  }
  
    
}

void loop()
{
  bpm = 65;
  /*//bpm = analogRead(hrPin);
  bpm = map(analogRead(hrPin), 0, 627, 30, 100);
  //bpm = map(analogRead(potPin), 0, 1023, 30, 100);
  bright = map(analogRead(potPin), 0, 1023, 0, 255);
 
  
  FastLED.showColor(CHSV(15, 255, bright)); 
  //Serial.println(hue);
  
 
  /*Serial.print("brightness: ");
  Serial.println(bright);
  Serial.print("Button: ");
  Serial.println(buttonState);
  Serial.println(analogRead(hrPin));*/
  
  buttonState = digitalRead(enPin);
  
  motor.speed(0, bpm);
  FastLED.showColor(CHSV(hue, saturation, 50));
  
  
  while (buttonState == HIGH){
    Serial.println(bpm);
    if (bpm == 65){
      bpm = map(analogRead(hrPin), 0, 627, 65, 100);
      //bpm = map(analogRead(potPin), 0, 1023, 65, 100);
      bright = map(bpm, 0, 100, 50, 150);
      //bright = map(analogRead(potPin), 0, 1023, 0, 255);

      for (int i = 65; i < bpm; i = i + 1){
        motor.speed(0, i);
        bright = map(i, 65, bpm, 50, 150);
        FastLED.showColor(CHSV(hue, saturation, bright));
        Serial.println(i);
        delay(200);
       
      }
    } 
    /*Serial.print("brightness");
    Serial.println(bright);
    /*Serial.print("BPM:");   
    Serial.print(bpm);
    Serial.print(' ');
    Serial.print("Button: ");
    Serial.println(buttonState);*/
    delay(500);
    buttonState = digitalRead(enPin);
    if (buttonState == LOW){
      for (int i = bpm; i > 65; i = i - 1){
        motor.speed(0, i);
        bright = map(i, 65, bpm, 50, 150);
        FastLED.showColor(CHSV(hue, saturation, bright));
        Serial.println(i);
        delay(200);
      }
    }
  }

  delay(100);
  
    
}
// END FILE


