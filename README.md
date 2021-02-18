# ArduinoScrollingMotionSensorLEDs
Requires the FastLED.h library
Turns on a series of WS2812b LED lights in sequential order linearly increasing the brightness of the LEDs from 0 to 255 over a given number of LED. 

Variables that can be adjusted to change the behavior of the LEDs are shown here:
  
hues = 235; // color number betwen 0 and 255. 235 looks like mellow light
saturation = 200; // between 0 and 255. 0 is pure white
numberOfScrolls = 1; // the number of times the lights will "run" up or down the stairs
onTime = 30;  // after scrolling is complete how many seconds will the lights stay on
scrollSize = 5; // Number of Pixels between off and full brightness. bigger numbers are slower
