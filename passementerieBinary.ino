//Passementerie Binary
//
//A rough sketch for reading data from an e-textile sensor structured like a 
//binary number, and lighting up a Neopixel LED strip to match the binary number.
//
//Uses bits of example code from the Neopixel library written by Adafruit, plus some of my own work
//
//Jessica Stanley (jstan.co) 2025

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

//set up binary input pins
const int bitPins[] = {A4, A3, A2, A1, A0}; //declare pins used to read bit values
int bitLength = sizeof(bitPins) / sizeof(bitPins[0]);

//set up neopixels
// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        6 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 5 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);

  for (int i=0; i<bitLength; i++){
    pinMode(bitPins[i], INPUT_PULLUP);
  }

  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {
  pixels.clear();

for (int i=0; i<bitLength; i++){
 // Serial.print(!digitalRead(bitPins[i]));
 // Serial.print('\t');

   // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    if(digitalRead(bitPins[i])==HIGH){ //if the circuit is open, make the LED purple
      pixels.setPixelColor(i, pixels.Color(0, 70, 150));
    }
    else{
      pixels.setPixelColor(i, pixels.Color(150, 0, 60)); //if the circuit is closed, make the LED blue
    }
    pixels.show();   // Send the updated pixel colors to the hardware.
 
}
    //Serial.println();
  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(500);
}
