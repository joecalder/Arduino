
#include <IRremote.h>
#include <printf.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//IR stuff
const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;
IRsend irsend;

//screen
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//joystick
#define joyX A0
#define joyY A1

int xPosition = 0;
int yPosition = 0;

//buttons
const int buttonPin = 2;     // the number of the pushbutton pin
int buttonState = 0;         // variable for reading the pushbutton status

void setup()
{
  button1();
  stickup();
  stickdown();
  stickleft();
  stickright();
  receiver();

  //IR receiver
  irrecv.enableIRIn();
  irrecv.blink13(true); //blink the board LED for debugging

  //button
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);  // initialize the pushbutton pin as an input:

  //OLED Display
  Serial.begin(115200);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 20);
  // Display static text @ startup
  display.println("   Welcome to your");
  display.println("");
  display.println("    Bespoke Remote");
  display.display();
}
//60C08F7 menu right  60C08F7

void loop() {
  button1();
  stickup();
  stickdown();
  stickleft();
  stickright();
  receiver();
  xPosition = analogRead(joyX);
  yPosition = analogRead(joyY);
}

void receiver() {
  //receive IR codes
  if (irrecv.decode(&results))
  { display.clearDisplay();
    display.setCursor(0, 30);
    display.println("Received IR"); //why does putting too much text here break this sketch?
    //display.println("    Code");
    display.println(results.value, HEX);
    display.display();
    irrecv.resume();
    } else { //button1();
      }
}

void button1() {
  //buttons
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    // send ir code to monitor
    irsend.sendNEC(0x60C08F7, 32);
    display.clearDisplay();
    display.setCursor(0, 30);
    display.println(" Monitor Menu Right");
    display.display();
    irrecv.enableIRIn();//re-enable the "receive" timer since send and receive use the same timer
  } else {
    stickup();
  }
}

void stickup() {
  //joystick up
  if (xPosition > 1000 and xPosition < 1040
      and yPosition > 510 and yPosition < 530) { //stick up
    display.clearDisplay();
    display.display();
    display.setCursor(0, 30);
    display.println("     Stick UP");
    display.display();
  } else {
    stickdown();
  }
}

void stickdown() {
  //joystick down
  if (xPosition > 0 and xPosition < 20
      and yPosition > 510 and yPosition < 530) { //stick down
    display.clearDisplay();
    display.display();
    display.setCursor(0, 30);
    display.println("     Stick DOWN");
    display.display();
  } else {
    stickleft();
  }
}

void stickleft() {
  //joystick left
  if (xPosition > 490 and xPosition < 510
      and yPosition > 1005 and yPosition < 1035) { //stick left
    display.clearDisplay();
    display.display();
    display.setCursor(0, 30);
    display.println("     Stick LEFT");
    display.display();
  } else {
    stickright();
  }
}

void stickright() {
  //joystick right
  if (xPosition > 490 and xPosition < 520
      and yPosition > 0 and yPosition < 75) { //stick right
    display.clearDisplay();
    display.display();
    display.setCursor(0, 30);
    display.println("     Stick RIGHT");
    display.display();
  } else {  }
}
