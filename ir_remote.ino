//#define DECODE_NEC
#include <Arduino.h>
#include <IRremote.hpp>
#include "lcdgfx.h" //for SSD1306 OLED display

//#################  OLED DISPLAY  ###################################################
DisplaySSD1306_128x64_I2C display(-1);

//#################  IR Receiver & Sender ############################################
#define IR_RECEIVE_PIN 12
#define IR_SEND_PIN 3
String incoming_ir_code;
String ir_protocol;
//String display_text = "Welcome.";

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
{   Serial.begin(115200);
    //#################  OLED DISPLAY  ###################################################
    display.setFixedFont( ssd1306xled_font6x8 );
    display.begin();
    display.clear();
       
    //#################  BUTTONS  ########################################################
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

    //#################  JOYSTICK  #######################################################
    stickup();
    stickdown();
    stickleft();
    stickright();
    //#################  IR  #############################################################
    pinMode(IR_RECEIVE_PIN, INPUT);
    pinMode(IR_SEND_PIN, OUTPUT);
    IrReceiver.begin(IR_RECEIVE_PIN);
    IrSender.begin(IR_SEND_PIN, DISABLE_LED_FEEDBACK, USE_DEFAULT_FEEDBACK_LED_PIN);  //must be disabled to also receive IR signals
}

void loop()
{   //#################  IR Receiver  ####################################################
    getRemoteCode();
    //#################  BUTTONS  ########################################################
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

    //#################  JOYSTICK  #######################################################
    stickup();
    stickdown();
    stickleft();
    stickright();
    xPosition = analogRead(joyX);
    yPosition = analogRead(joyY);

}

//#################  IR Receiver  ####################################################

void getRemoteCode()
{   
    if (IrReceiver.decode()) { // an infrared signal is received
    incoming_ir_code = IrReceiver.decodedIRData.decodedRawData; //save incoming code to variable
    //ir_protocol = getProtocolString(IrReceiver.decodedIRData.protocol);//save incoming protocol to variable
    printRemoteCode(); //split out here to determine whether incoming code is valid and printable
    delay(100);
    }
    else {  }
    IrReceiver.resume();
}

void printRemoteCode()
{ 
  if (incoming_ir_code != "0") {
        ir_protocol = getProtocolString(IrReceiver.decodedIRData.protocol);
        IrReceiver.printIRResultShort(&Serial);
        display.clear();
        display.printFixed(16, 16, "Received IR", STYLE_BOLD);
        display.printFixed(8, 32, (ir_protocol.c_str()), STYLE_NORMAL);
        display.printFixed(8, 48, (incoming_ir_code.c_str()), STYLE_NORMAL);
        Serial.print(F("Decoded protocol: "));
        Serial.print(ir_protocol);
        Serial.print(F(", decoded raw data: "));
  #if (__INT_WIDTH__ < 32)
        Serial.print(IrReceiver.decodedIRData.decodedRawData);
  #else
        PrintULL::print(&Serial, IrReceiver.decodedIRData.decodedRawData);
  #endif
        Serial.print(F(", decoded address: "));
        Serial.print(IrReceiver.decodedIRData.address); //todo maybe save to variable
        Serial.print(F(", decoded command: "));
        Serial.println(IrReceiver.decodedIRData.command); //todo maybe save to variable
        IrReceiver.resume();
  } else {  }
}

//#################  IR CODES  ########################################################
//Onkyo
//IrSender.sendNECRaw(0xFB046DD2, 1); //onkyo receiver on
//IrSender.sendNECRaw(0xB8476CD2, 1); //onkyo receiver off
//IrSender.sendNECRaw(0xFD026DD2, 1); //onkyo volume up
//IrSender.sendNECRaw(0xFC036DD2, 1); //onkyo volume down
//Protocol=NEC Address=0x6DD2 Command=0x5 Raw-Data=0xFA056DD2 32 bits LSB first //onkyo mute

//Roku
//Protocol=NEC Address=0xC4EA Command=0x2D Raw-Data=0xD22DC4EA 32 bits LSB first //roku right
//Protocol=NEC Address=0xC4EA Command=0x33 Raw-Data=0xCC33C4EA 32 bits LSB first //roku down
//Protocol=NEC Address=0xC4EA Command=0x1E Raw-Data=0xE11EC4EA 32 bits LSB first //roku left
//Protocol=NEC Address=0xC4EA Command=0x19 Raw-Data=0xE619C4EA 32 bits LSB first //roku up
//Protocol=NEC Address=0xC4EA Command=0x2A Raw-Data=0xD52AC4EA 32 bits LSB first //roku select
//Protocol=NEC Address=0xC4EA Command=0x66 Raw-Data=0x9966C4EA 32 bits LSB first //roku back
//Protocol=NEC Address=0xC4EA Command=0x3 Raw-Data=0xFC03C4EA 32 bits LSB first //roku home
//Protocol=NEC Address=0xC4EA Command=0x4C Raw-Data=0xB34CC4EA 32 bits LSB first //roku play/pause
//Protocol=NEC Address=0xC4EA Command=0x34 Raw-Data=0xCB34C4EA 32 bits LSB first //roku rewind
//Protocol=NEC Address=0xC4EA Command=0x55 Raw-Data=0xAA55C4EA 32 bits LSB first //roku forward
//Protocol=NEC Address=0xC4EA Command=0xC Raw-Data=0xF30CC4EA 32 bits LSB first //roku power off

//Samsung
//Protocol=Samsung Address=0x707 Command=0x2 Raw-Data=0xFD020707 32 bits LSB first
//Decoded protocol: Samsung, decoded raw data: 4244768519, decoded address: 1799, decoded command: 2

//#################  BUTTONS  ########################################################
void button1() {
  button1State = digitalRead(button1Pin);
  if (button1State == HIGH) {
    IrSender.sendNEC(0x9966C4EA, 32);  //roku back
    display.clear();
    display.printFixedN(0, 16, "Roku Back", STYLE_BOLD, FONT_SIZE_2X);
    delay(200);
    IrReceiver.resume();
    } else {    }
  }
void button2() {
  button2State = digitalRead(button2Pin);
  if (button2State == HIGH) {
    IrSender.sendNEC(0xD52AC4EA, 32); //roku select
    display.clear();
    display.printFixedN(0, 16, "Roku Select", STYLE_BOLD, FONT_SIZE_2X);
    delay(200);
    IrReceiver.resume();
    } else {   }
  } 
void button3() {
  button3State = digitalRead(button3Pin);
  if (button3State == HIGH) {
    IrSender.sendNEC(0xCB34C4EA, 32); //roku rewind
    display.clear();
    display.printFixedN(0, 16, "Roku Rewind", STYLE_BOLD, FONT_SIZE_2X);
    delay(200);
    IrReceiver.resume();
    } else {  }
  } 
void button4() {
  button4State = digitalRead(button4Pin);
  if (button4State == HIGH) {
    IrSender.sendNEC(0xB34CC4EA, 32);    // roku play/pause
    display.clear();
    display.printFixedN(0, 16, "Roku Play", STYLE_BOLD, FONT_SIZE_2X);
      display.printFixedN(8, 32, "/ Pause", STYLE_BOLD, FONT_SIZE_2X);
    delay(200);
    IrReceiver.resume();
    } else {  }
  } 
void button5() {
  button5State = digitalRead(button5Pin);
  if (button5State == HIGH) {
    IrSender.sendNEC(0xAA55C4EA, 32);    // roku fast forward
    display.clear();
    display.printFixedN(0, 16, "Roku Fast", STYLE_BOLD, FONT_SIZE_2X);
      display.printFixedN(8, 32, "Forward", STYLE_BOLD, FONT_SIZE_2X);
    delay(200);
    IrReceiver.resume();
    } else {  }
  } 
void button6() {
  button6State = digitalRead(button6Pin);
  if (button6State == HIGH) {
    IrSender.sendNECRaw(0xFB046DD2, 1); //onkyo receiver on
    delay(50);
    IrSender.sendNEC(0xFC03C4EA, 32);    // roku home/on
    display.clear();
    display.printFixedN(0, 8, "Power ON", STYLE_BOLD, FONT_SIZE_2X);
    display.printFixedN(0, 32, "Roku Home", STYLE_BOLD, FONT_SIZE_2X);
    delay(200);
    IrReceiver.resume();
    } else {  }
  } 
void button7() {
  button7State = digitalRead(button7Pin);
  if (button7State == HIGH) {
    IrSender.sendNECRaw(0xFC036DD2, 1); //onkyo volume down
    display.clear();
    display.printFixedN(8, 8, "Volume", STYLE_BOLD, FONT_SIZE_2X);
    display.printFixedN(12, 32, "Down", STYLE_BOLD, FONT_SIZE_2X);
    delay(200);
    IrReceiver.resume();
    } else {  }
  } 
void button8() {
  button8State = digitalRead(button8Pin);
  if (button8State == HIGH) {
    IrSender.sendNECRaw(0xFD026DD2, 1);    // onkyo volume up
    display.clear();
    display.printFixedN(8, 8, "Volume", STYLE_BOLD, FONT_SIZE_2X);
    display.printFixedN(16, 32, "Up", STYLE_BOLD, FONT_SIZE_2X);
    delay(200);
    IrReceiver.resume();
    } else {  }
  } 
void button9() {
  button9State = digitalRead(button9Pin);
  if (button9State == HIGH) {
    IrSender.sendNECRaw(0xFA056DD2, 1);    // onkyo mute
    display.clear();
    display.printFixedN(8, 16, "MUTE", STYLE_BOLD, FONT_SIZE_2X);
    delay(200);
    IrReceiver.resume();
    } else {  }
  } 
void button10() {
  button10State = digitalRead(button10Pin);
  if (button10State == HIGH) {
    IrSender.sendNECRaw(0xB8476CD2, 1); //onkyo power off
    delay(50);
    IrSender.sendNEC(0xF30CC4EA, 32);  // roku power //TODO replace this with something smarter
    display.clear();
    display.printFixedN(0, 8, "Power OFF", STYLE_BOLD, FONT_SIZE_2X);
    delay(200);
    IrReceiver.resume();
    } else {  }
  } 

//#################  JOYSTICK  #######################################################
void stickup() {
  //joystick up
  if (xPosition > 1000) {
    IrSender.sendNEC(0x60C08F7, 32);    // send ir code
    display.clear();
    display.printFixedN(0, 16, "Roku UP", STYLE_BOLD, FONT_SIZE_2X);
    delay(200);
    IrReceiver.resume();
    } else {  }
}

void stickdown() {
  //joystick down
  if (xPosition < 20) {
    IrSender.sendNEC(0x60C08F7, 32);    // send ir code
    display.clear();
    display.printFixedN(0, 16, "Roku DOWN", STYLE_BOLD, FONT_SIZE_2X);
    delay(200);
    IrReceiver.resume();
  } else {  }
}

void stickleft() {
  //joystick left
  if (yPosition < 20) {
    IrSender.sendNEC(0x60C08F7, 32);    // send ir code
    display.clear();
    display.printFixedN(0, 16, "Roku LEFT", STYLE_BOLD, FONT_SIZE_2X);
    delay(200);
    IrReceiver.resume();
  } else {  }
}

void stickright() {
  //joystick right
  if (yPosition > 1000) {
    IrSender.sendNEC(0x60C08F7, 32);    // send ir code
    display.clear();
    display.printFixedN(0, 16, "Roku RIGHT", STYLE_BOLD, FONT_SIZE_2X);
    delay(200);
    IrReceiver.resume();
  } else {  }
}
