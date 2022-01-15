// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        6 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 256 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int DELAYVAL = 1;// Time (in milliseconds) to pause between pixels
   int acumulado = NUMPIXELS;
void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.
  Serial.begin(9600);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
 
}

void loop() {
  //pixels.clear(); // Set all pixel colors to 'off'


  
      
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
  
    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:


    for(int j = acumulado; j< NUMPIXELS; j++){
        pixels.setPixelColor(j, pixels.Color(70, 0, 30));
      }

    pixels.setPixelColor(i, pixels.Color(70, 0, 30));
    
    pixels.setPixelColor((i-2), pixels.Color(0, 0, 0));




    pixels.show();   // Send the updated pixel colors to the hardware.


    if(i == (NUMPIXELS -1)){
      acumulado--;
     Serial.println(acumulado);
      }
    
 
  }

  if(acumulado == 0){acumulado = NUMPIXELS;}
}
