#include <Adafruit_NeoPixel.h>

// Pin number to control WS2812 light strip
#define LED_PIN     9
#define NUMPIXELS   1
#define BUTTON_PIN  3

Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

boolean oldState = HIGH;
int     mode     = 0;    //currently active rgb mode 0-n
int     PotPin      = A0;   //analog pin of potentiometer
int     PotVal;
int     OutVal;

int previousAnalog = 0;
const int threshold = 5; // Change must be greater than 5 to trigger code

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
//  pinMode(PotPin, INPUT);
  pixels.begin();
  colorWipe(pixels.Color( 240, 230, 70), 50); //startup color
  Serial.begin(9066);
}

void loop() {
  PotVal = analogRead(PotPin);

  // Check if the absolute difference exceeds the threshold
  if(abs(PotVal - previousAnalog) > threshold) {
    if(PotVal >=10) {
      OutVal = map(PotVal, 0, 1023, 0, 255);
      pixels.setBrightness(OutVal);
      pixels.show();
      Serial.print("PotVal: ");
      Serial.println(PotVal);
    }
    if(PotVal <10) { //set lower threshhold so LEDs always illuminate
      OutVal = 10;
      pixels.setBrightness(OutVal);
      pixels.show();
      Serial.print("PotVal at lower threshhold.");
    }
    // ---------------------------
    previousAnalog = PotVal; // Update stored value
  }
  delay(20); // stability
    
  boolean newState = digitalRead(BUTTON_PIN);

  //check if button state changed from high to low
  if((newState ==LOW) && (oldState == HIGH)) {
    //short delay to debounce button
    delay(20);
    //check if button is still low
    newState = digitalRead(BUTTON_PIN);
    if(newState == LOW) {   //yes, still low
      if(++mode > 5) mode = 0; //advance to next mode, wrap after max
      switch(mode) {
        case 0:
          colorWipe(pixels.Color( 240, 230, 70), 50); //warm white-ish
          break;
        case 1:
          colorWipe(pixels.Color( 30, 255, 100), 50); //teal/custom
          break;
        case 2:
          colorWipe(pixels.Color( 255, 0, 0), 50); //red
          break;
        case 3:
          colorWipe(pixels.Color( 55, 55, 55), 50); //white-ish
          break;
        case 4:
          colorWipe(pixels.Color( 0, 0, 255), 50); //blue
          break;
        case 5:
          colorWipe(pixels.Color( 0, 0, 0), 50); //off
          break;
      }
    }
  }

  //set the last-read button state to the old state
  oldState = newState;
}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<pixels.numPixels(); i++ ) { // for each pixel
    pixels.setPixelColor(i, color);        // set pixel color (in RAM)
    pixels.show();
    delay(wait);
  }
}
