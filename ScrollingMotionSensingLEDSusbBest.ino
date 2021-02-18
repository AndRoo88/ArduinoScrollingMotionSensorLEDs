/*
   T3chFlicks - Motion Sensing Under Bed Lighting
   Free to use and distribute.
   Find the tutorial and parts list at https://t3chflicks.com/shop/kit/motion-sensing-under-bed-lights/
*/

#include "FastLED.h"
#define LED_DATA_PIN 9
#define NUM_LEDS 150
CRGB leds[NUM_LEDS];

int hues = 235; // color number betwen 0 and 255. 235 looks like mellow light
int saturation = 200; // between 0 and 255. 0 is pure white
int numberOfScrolls = 1;
int onTime = 30;  // (20 - (2*numberOfScrolls))*1000;
int scrollSize = 5; // bigger numbers are slower

int motion_sensor_bot = 10;
int motion_sensor_top = 11;
int fadeTimeDiff = 1;
float scrollTime = 1;
int bright = 0;

void setup() {
  FastLED.addLeds<WS2811, LED_DATA_PIN, BRG>(leds, NUM_LEDS);
  pinMode(motion_sensor_bot, INPUT);
  pinMode(motion_sensor_top, INPUT);
  //pinMode(motion_sensor_front, INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println(digitalRead(motion_sensor_bot));
  Serial.println(digitalRead(motion_sensor_top));
  if (digitalRead(motion_sensor_bot) == 1) {// || digitalRead(motion_sensor_right) == 1) || digitalRead(motion_sensor_front) == 1) {
    scrollUp();
    delay(onTime*1000);
    scrollUpOut();
    //fadeOut();
  }
  else if (digitalRead(motion_sensor_top) == 1) {
    scrollDown();
    delay(onTime*1000);
    scrollDownOut();
    //fadeOut();
  }
}

void scrollUp() {
  for (int l = 0; l < numberOfScrolls; l ++) {
    for (int i = 0; i < NUM_LEDS+scrollSize; i ++) {
      delay(float(scrollTime/(NUM_LEDS)));
      for(int j = 0; j < scrollSize; j++) {
        if ((i-j) > 0 && (i-j-1) < NUM_LEDS) {
          bright = (254/scrollSize)*(j+1);
          leds[i-j-1] = CHSV(hues, saturation, bright);
          FastLED.show();
        }
      }
    }
  }
}


void scrollUpOut() {
  for (int i = 0; i < NUM_LEDS; i ++) {
    delay(float(scrollTime*5000/(NUM_LEDS)));
    leds[i] = CHSV(hues, 200, 0);
    FastLED.show();
  }
}

void scrollDown() {
  for (int l = 0; l < numberOfScrolls; l ++) {
    for (int i = 0; i < NUM_LEDS+scrollSize; i ++) {
      delay(float(scrollTime/(NUM_LEDS)));
      for(int j = 0; j < scrollSize; j++) {
        if ((i-j) > 0 && (i-j-1) < NUM_LEDS) {
          bright = (254/scrollSize)*(j+1);
          leds[150-(i-j)] = CHSV(hues, saturation, bright);
          FastLED.show();
        }
      }
    }
  }
}

void scrollDownOut() {
  for (int i = 0; i < NUM_LEDS; i ++) {
    delay(float(scrollTime*5000/(NUM_LEDS)));
    leds[149 - i] = CHSV(hues, 200, 0);
    FastLED.show();
  }
}

void resetLEDs() {
  for (int led = 0; led < NUM_LEDS; led++) {
    leds[led] = CHSV( 255, 200, 0);
  }
}

void fadeOut() {
  Serial.println("fadeout");
  for (int led = 0; led < NUM_LEDS; led++) {
    leds[led] = CHSV( hues, saturation, 0);
  }
  FastLED.show();
  /*
  for (int b = 255; b > 0; b -= 2) {
    leds[b] = CHSV( hues, 200, 255 - b);
    //delay(fadeTimeDiff);
    FastLED.show();
  }*/
}
