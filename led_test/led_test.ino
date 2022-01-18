#include <FastLED.h>

#define NUM_LEDS 300
#define LED_PIN 2

#define BLUE_ALIANCE 1
#define RED_ALIANCE 2
#define NEON_GREEN 3 

CRGB leds[NUM_LEDS] ;

uint8_t currentMode = NEON_GREEN ;

CRGB redAliance = CRGB( 255,0,0) ;
CRGB blueAliance = CRGB( 0,0,255) ;
CRGB neonGreen = CRGB( 0,255,0) ;

uint8_t hue = 0 ;

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS) ;
  FastLED.setBrightness(100) ;
  //FastLED.setCorrection( TypicalLEDStrip) ;
  FastLED.setCorrection( TypicalPixelString) ;

  Serial.begin(9600);   

}

void loop() {

  switch( currentMode) {
    case BLUE_ALIANCE :
      for ( int i = 0; i< NUM_LEDS; i++) {
        leds[i] = blueAliance ;
      }
      break ;
    case RED_ALIANCE :
      for ( int i = 0; i< NUM_LEDS; i++) {
        leds[i] = redAliance ;
      }
      break ;
    case NEON_GREEN :
      for ( int i = 0; i< NUM_LEDS; i++) {
        leds[i] = neonGreen ;
      }
      break ;
    default :
      for ( int i = 0; i< NUM_LEDS; i++) {
        leds[i] = CRGB(255,255,255) ;
      }
  }

  EVERY_N_MILLISECONDS( 50 ) {
      // look for an updated mode from the robot over the serial bus.
      if (Serial.available() > 0) {
        // read the incoming byte:
        uint8_t incomingByte = Serial.read();
        if ( incomingByte >= 1 && incomingByte <= 4 ) {
            currentMode = incomingByte ;
        }
      } 
  }
  
  FastLED.show() ;

}
