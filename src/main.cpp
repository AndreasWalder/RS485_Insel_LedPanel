#include <Arduino.h>

//int SlaveId = 0;  //Bus-Adresse by Switch 1 - 7

int CheckSlaveId = 0; //Bus-Adresse by Switch 1 - 7
int Id;
char packet;
long Lifebit = 0;
long Lifebitzeit = 0;
const int buttonId1 = 7;     // the number of the pushbutton pin
const int buttonId2 = 6;     // the number of the pushbutton pin
const int buttonId3 = 5;     // the number of the pushbutton pin

/*-----( Import needed libraries )-----*/
//#include <ICSC.h>
#define SerialDebug      0      // 0 = ohne Debug ; 1 = mit Debug
#define RS485orRS232     0       // 0 = mit RS485 Ansteuerung; 1 = ohne RS485 Ansteuerung

//#include "Led.h"
#include <LedPanel.h>
#include <avr/wdt.h>

#include <SoftwareSerial.h>
/*-----( Declare Constants and Pin Numbers )-----*/
#define SSerialRX        2  //Serial Receive pin RO
#define SSerialTX        4  //Serial Transmit pin DI

#define SSerialTxControl 3   //RS485 Direction control RE DE

#define RS485Transmit    HIGH
#define RS485Receive     LOW

#define Pin13LED         13
#define Pin12TASTER        12

/*-----( Declare objects )-----*/
SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX

byte byteRead;
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

//Auswertung auswertung;
LedPanel ledPanel;
//Led ledArray[]={(1),(2),(3),(4),(5),(6),(7),(8)};
//Led led8=ledArray[7];
//Led led1=ledArray[0];
//Led led2=ledArray[1];
//Led led3=ledArray[2];
//Led led4=ledArray[3];
//Led led5=ledArray[4];
//Led led6=ledArray[5];
//Led led7=ledArray[6];
 
void setup()
{
//  ledAr(0) = led1
pinMode(LED_BUILTIN, OUTPUT);
  
  if (digitalRead(buttonId1) == HIGH){
    // SlaveId = 1;
    CheckSlaveId = CheckSlaveId + 1;
  }
  
  if (digitalRead(buttonId2) == HIGH){
    // SlaveId = 2;
    CheckSlaveId = CheckSlaveId + 2;
  }
  if (digitalRead(buttonId3) == HIGH){
    // SlaveId = 3;
    CheckSlaveId = CheckSlaveId + 4;
  }
  if (CheckSlaveId < 1 || CheckSlaveId > 4){
    // SlaveId = 0;
    CheckSlaveId = 0;
    }
   
  Serial.begin(9600);
   
Serial.println(CheckSlaveId);
   if (CheckSlaveId == 1 )
  {    
  Serial.println("Serial_Kipptisch_rechts (Putzstation 8)");
   }
   if (CheckSlaveId == 2 )
  {    
    Serial.println("SerialDebug_Kipptisch_links (Putzstation 9)");
  }
   if (CheckSlaveId == 3 )
  {    
    Serial.println("SerialDebug_Drehtisch (Putzstation 11)");
  }
   if (CheckSlaveId == 4 )
  {    
    Serial.println("(Putzstation 10)");
  }
  
  pinMode(Pin13LED, OUTPUT);   
  pinMode(SSerialTxControl, OUTPUT);    
  
  // Start the software serial port, to another device
   RS485Serial.begin(9600);   // set the data rate 
   
  
  ledPanel.initLedPanel(CheckSlaveId);
 wdt_enable(WDTO_2S);  //2s Watchdog 
}

//void serialEvent() {
//  if (RS485orRS232) {
//   while (Serial.available()) {
//     // get the new byte:
//     char inChar = (char)Serial.read();
//     // add it to the inputString:
//     inputString += inChar;
//     // if the incoming character is a newline, set a flag
//     // so the main loop can do something about it:
//     if (inChar == '\n') {
//       stringComplete = true;
//     }
//   }
//  }
//}  

void serialRS485Event() {
    while (RS485Serial.available()) 
    {
     digitalWrite(LED_BUILTIN, LOW);
       // get the new byte:
       packet = RS485Serial.read();
       char inChar = (char)packet;
       // add it to the inputString:
       inputString += inChar;
       // if the incoming character is a newline, set a flag
       // so the main loop can do something about it:
       if  ( packet==2)
       {
        inputString = "";
        stringComplete = false;
       }
       if (packet == 3) 
       {
             stringComplete = true;
             return;
       }
    }  
}
 

void loop() 

{
     
      Lifebitzeit++;
      if (Lifebitzeit > 100000)
      {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));  
        Lifebit++;
        if (SerialDebug) {
        Serial.print(Lifebit);
          }
     Lifebitzeit = 0;
      }
   
    serialRS485Event(); 
    if (stringComplete)
     {
         ledPanel.InputExecute(inputString);
         inputString = "";
         stringComplete = false;
     }
     ledPanel.ExecutePanel();
      
    wdt_reset();
    
} 