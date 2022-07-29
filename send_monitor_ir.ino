
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
const int button1Pin = 2;     // the number of the digital input pin
int button1State = 0;         // variable for reading the pushbutton status
const int button2Pin = 2;     // the number of the digital input pin
int button2State = 0;         // variable for reading the pushbutton status
const int button3Pin = 2;     // the number of the digital input pin
int button3State = 0;         // variable for reading the pushbutton status
const int button4Pin = 2;     // the number of the digital input pin
int button4State = 0;         // variable for reading the pushbutton status
const int button5Pin = 2;     // the number of the digital input pin
int button5State = 0;         // variable for reading the pushbutton status
const int button6Pin = 2;     // the number of the digital input pin
int button6State = 0;         // variable for reading the pushbutton status
const int button7Pin = 2;     // the number of the digital input pin
int button7State = 0;         // variable for reading the pushbutton status
const int button8Pin = 2;     // the number of the digital input pin
int button8State = 0;         // variable for reading the pushbutton status
const int button9Pin = 2;     // the number of the digital input pin
int button9State = 0;         // variable for reading the pushbutton status
const int button10Pin = 2;     // the number of the digital input pin
int button10State = 0;         // variable for reading the pushbutton status

void setup()
{
  button1();
  button2();
  button3();
  button4();
  button5();
  button6();
  button7();
  button8();
  button9();
  button10();
  stickup();
  stickdown();
  stickleft();
  stickright();
  receiver();
  
  //IR receiver
  irrecv.enableIRIn();
  irrecv.blink13(true); //blink the board LED for debugging

  //buttons
  pinMode(button1Pin, INPUT);  // initialize the pushbutton pin as an input:
  pinMode(button2Pin, INPUT);  // initialize the pushbutton pin as an input:
  pinMode(button3Pin, INPUT);  // initialize the pushbutton pin as an input:
  pinMode(button4Pin, INPUT);  // initialize the pushbutton pin as an input:
  pinMode(button5Pin, INPUT);  // initialize the pushbutton pin as an input:
  pinMode(button6Pin, INPUT);  // initialize the pushbutton pin as an input:
  pinMode(button7Pin, INPUT);  // initialize the pushbutton pin as an input:
  pinMode(button8Pin, INPUT);  // initialize the pushbutton pin as an input:
  pinMode(button9Pin, INPUT);  // initialize the pushbutton pin as an input:
  pinMode(button10Pin, INPUT);  // initialize the pushbutton pin as an input:

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
  display.println("    Arcade Remote");
  display.display();
}
//60C08F7 menu right  60C08F7

void loop() {
  button1();
  button2();
  button3();
  button4();
  button5();
  button6();
  button7();
  button8();
  button9();
  button10();
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
    display.println("Received IR"); //why does putting too much text here break this loop?
    //display.println("    Code");
    display.println(results.value, HEX);
    display.display();
    irrecv.resume();
    } else { //button1();
      }
}

void button1() {
  button1State = digitalRead(button1Pin);
  if (button1State == HIGH) {
    irsend.sendNEC(0x60C08F7, 32);    // send ir code
    display.clearDisplay();
    display.setCursor(0, 30);
    display.println(" button 1");
    display.display();
    irrecv.enableIRIn();//re-enable the "receive" timer since send and receive use the same timer
  } else {
    stickup();
  }
}

void button2() {
  button2State = digitalRead(button2Pin);
  if (button2State == HIGH) {
    irsend.sendNEC(0x60C08F7, 32);     // send ir code
    display.clearDisplay();
    display.setCursor(0, 30);
    display.println(" button 2");
    display.display();
    irrecv.enableIRIn();//re-enable the "receive" timer since send and receive use the same timer
  } else {
    stickup();
  }
}

void button3() {
  button3State = digitalRead(button3Pin);
  if (button3State == HIGH) {
    irsend.sendNEC(0x60C08F7, 32);     // send ir code
    display.clearDisplay();
    display.setCursor(0, 30);
    display.println(" button 3");
    display.display();
    irrecv.enableIRIn();//re-enable the "receive" timer since send and receive use the same timer
  } else {
    stickup();
  }
}

void button4() {
  button4State = digitalRead(button4Pin);
  if (button4State == HIGH) {
    irsend.sendNEC(0x60C08F7, 32);     // send ir code
    display.clearDisplay();
    display.setCursor(0, 30);
    display.println(" button 4");
    display.display();
    irrecv.enableIRIn();//re-enable the "receive" timer since send and receive use the same timer
  } else {
    stickup();
  }
}

void button5() {
  button5State = digitalRead(button5Pin);
  if (button5State == HIGH) {
    irsend.sendNEC(0x60C08F7, 32);     // send ir code
    display.clearDisplay();
    display.setCursor(0, 30);
    display.println(" button 5");
    display.display();
    irrecv.enableIRIn();//re-enable the "receive" timer since send and receive use the same timer
  } else {
    stickup();
  }
}

void button6() {
  button6State = digitalRead(button6Pin);
  if (button6State == HIGH) {
    irsend.sendNEC(0x60C08F7, 32);     // send ir code
    display.clearDisplay();
    display.setCursor(0, 30);
    display.println(" button 6");
    display.display();
    irrecv.enableIRIn();//re-enable the "receive" timer since send and receive use the same timer
  } else {
    stickup();
  }
}

void button7() {
  button7State = digitalRead(button7Pin);
  if (button7State == HIGH) {
    irsend.sendNEC(0x60C08F7, 32);     // send ir code
    display.clearDisplay();
    display.setCursor(0, 30);
    display.println(" button 7");
    display.display();
    irrecv.enableIRIn();//re-enable the "receive" timer since send and receive use the same timer
  } else {
    stickup();
  }
}

void button8() {
  button8State = digitalRead(button8Pin);
  if (button8State == HIGH) {
    irsend.sendNEC(0x60C08F7, 32);     // send ir code
    display.clearDisplay();
    display.setCursor(0, 30);
    display.println(" button 8");
    display.display();
    irrecv.enableIRIn();//re-enable the "receive" timer since send and receive use the same timer
  } else {
    stickup();
  }
}

void button9() {
  button9State = digitalRead(button9Pin);
  if (button9State == HIGH) {
    irsend.sendNEC(0x60C08F7, 32);     // send ir code
    display.clearDisplay();
    display.setCursor(0, 30);
    display.println(" button 9");
    display.display();
    irrecv.enableIRIn();//re-enable the "receive" timer since send and receive use the same timer
  } else {
    stickup();
  }
}

void button10() {
  button10State = digitalRead(button10Pin);
  if (button10State == HIGH) {
    irsend.sendNEC(0x60C08F7, 32);     // send ir code
    display.clearDisplay();
    display.setCursor(0, 30);
    display.println(" button 10");
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
