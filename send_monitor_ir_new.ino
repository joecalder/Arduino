#include <IRremote.h>
#include "lcdgfx.h" //for SSD1306 OLED display

//#################  OLED DISPLAY  ###################################################
DisplaySSD1306_128x64_I2C display(-1);
char *print_this[] = {"Welcome.",
                     "Button 1",
                     "Button 2",
                     "Button 3,
                     "Button 4",
                     "Button 5"
                    };


//#################  IR Receiver & Sender ############################################
const int RECV_PIN = 7;
//send pin == 3 //for INFO only since this is default
IRrecv irrecv(RECV_PIN);
decode_results results;
IRsend irsend;

//#################  JOYSTICK  #######################################################
#define joyX A0
#define joyY A1
int xPosition = 0;
int yPosition = 0;

//#################  BUTTONS  ########################################################
const int button1Pin = 2;     // the number of the digital input pin
int button1State = 0;         // variable for reading the pushbutton status
const int button2Pin = 13;     // the number of the digital input pin
int button2State = 0;         // variable for reading the pushbutton status
const int button3Pin = 4;     // the number of the digital input pin
int button3State = 0;         // variable for reading the pushbutton status
const int button4Pin = 5;     // the number of the digital input pin
int button4State = 0;         // variable for reading the pushbutton status
const int button5Pin = 6;     // the number of the digital input pin
int button5State = 0;         // variable for reading the pushbutton status
const int button6Pin = 7;     // the number of the digital input pin
int button6State = 0;         // variable for reading the pushbutton status
const int button7Pin = 8;     // the number of the digital input pin
int button7State = 0;         // variable for reading the pushbutton status
const int button8Pin = 9;     // the number of the digital input pin
int button8State = 0;         // variable for reading the pushbutton status
const int button9Pin = 10;     // the number of the digital input pin
int button9State = 0;         // variable for reading the pushbutton status
const int button10Pin = 11;     // the number of the digital input pin
int button10State = 0;         // variable for reading the pushbutton status

void setup()
{
    //#################  OLED DISPLAY  ###################################################
    /* Select the font to use with menu and all font functions */
    display.setFixedFont( ssd1306xled_font6x8 );
    display.begin();
    display.clear();
    
    //#################  BUTTONS  ########################################################
    button1();
//    button2();
//    button3();
//    button4();
//    button5();
//    button6();
//    button7();
//    button8();
//    button9();
//    button10();
    pinMode(button1Pin, INPUT);  // initialize the pushbutton pin as an input:
//    pinMode(button2Pin, INPUT);  // initialize the pushbutton pin as an input:
//    pinMode(button3Pin, INPUT);  // initialize the pushbutton pin as an input:
//    pinMode(button4Pin, INPUT);  // initialize the pushbutton pin as an input:
//    pinMode(button5Pin, INPUT);  // initialize the pushbutton pin as an input:
//    pinMode(button6Pin, INPUT);  // initialize the pushbutton pin as an input:
//    pinMode(button7Pin, INPUT);  // initialize the pushbutton pin as an input:
//    pinMode(button8Pin, INPUT);  // initialize the pushbutton pin as an input:
//    pinMode(button9Pin, INPUT);  // initialize the pushbutton pin as an input:
//    pinMode(button10Pin, INPUT);  // initialize the pushbutton pin as an input:

    //#################  JOYSTICK  #######################################################
    stickup();
    stickdown();
    stickleft();
    stickright();
    //#################  IR Receiver  ####################################################
    receiver();
    irrecv.enableIRIn();
    irrecv.blink13(true); //blink the board LED for debugging

}



void loop()
{
    //#################  OLED DISPLAY  ###################################################
    displaystuff();
    //#################  BUTTONS  ########################################################
    button1();
//    button2();
//    button3();
//    button4();
//    button5();
//    button6();
//    button7();
//    button8();
//    button9();
//    button10();

    //#################  JOYSTICK  #######################################################
    stickup();
    stickdown();
    stickleft();
    stickright();
    xPosition = analogRead(joyX);
    yPosition = analogRead(joyY);

    //#################  IR Receiver  ####################################################
    receiver();


}

//#################  OLED DISPLAY  ###################################################
void displaystuff() {
    lcd_delay(1000);
    display.clear();
    display.printFixed(0, 16, print_this[0], STYLE_BOLD);
}

//#################  IR Receiver  ####################################################
void receiver() {
  //receive IR codes
  if (irrecv.decode(&results))
  { display.clear();
    display.printFixed(0, 16, "Received IR", STYLE_BOLD);
    display.printFixed(0, 24, results.value, STYLE_BOLD);
    irrecv.resume();
    } else { //button1();
      }
}

//#################  BUTTONS  ########################################################
void button1() {
  button1State = digitalRead(button1Pin);
  if (button1State == HIGH) {
    irsend.sendNEC(0x60C08F7, 32);    // send ir code
    display.clear();
    display.printFixed(0, 16, "Button 1", STYLE_BOLD);
    irrecv.enableIRIn();//re-enable the "receive" timer since send and receive use the same timer
  } else {
    stickup();
  }
}

//#################  JOYSTICK  #######################################################
void stickup() {
  //joystick up
  if (xPosition > 1000) {
    display.clear();
    display.printFixed(0, 16, "Stick UP", STYLE_BOLD);
    } else {
    stickdown();
  }
}

void stickdown() {
  //joystick down
  if (xPosition < 20) {
    display.clear();
    display.printFixed(0, 16, "Stick DOWN", STYLE_BOLD);
  } else {
    stickleft();
  }
}

void stickleft() {
  //joystick left
  if (yPosition < 20) {
    display.clear();
    display.printFixed(0, 16, "Stick LEFT", STYLE_BOLD);
  } else {
    stickright();
  }
}

void stickright() {
  //joystick right
  if (yPosition > 1000) {
    display.clear();
    display.printFixed(0, 16, "Stick RIGHT", STYLE_BOLD);
  } else {  }
}
