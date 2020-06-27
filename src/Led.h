#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            8

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      8

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

class Led
{
  int Cmd,ledIndex; 
  unsigned int blinkTimerMilli;
  unsigned int currentMillis;
  public : int R;
           int G;
           int B;
          bool MbBlinken = 0;
          Led(int newledindex); 
          void SetPixelColor(int Rval,int Gval, int Bval);
           void SetPixelColor(uint32_t color);
           void SetBlinken(bool BlinkVal);
           void ExecBlinken();
           void SetIndex(int newIndex);
  bool Blinken,BlinkenLedAus;
 // Adafruit_NeoPixel pixels ;

  uint32_t LedOff = pixels.Color(0,0,0); // Led color aus
  uint32_t magenta = pixels.Color(100, 0, 100);
  uint32_t red = pixels.Color(100, 0, 0);
  uint32_t green = pixels.Color(0, 100, 0);
  uint32_t blue = pixels.Color(0, 0, 100);
  uint32_t yellow = pixels.Color(125, 80, 0);
  uint32_t purple = pixels.Color(80, 0, 80);
  uint32_t aqua = pixels.Color(0, 100, 100);
   
 String getValue(String data, int index)
  {
    char separator = ',';
    int found = 0;
    int strIndex[] = {0, -1};
    int maxIndex = data.length()-1;
    for(int i=0; i<=maxIndex && found<=index; i++)
    {
      if(data.charAt(i)==separator || i==maxIndex)
      {
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
      }
    }
    return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
  }
     
       
  void InputExecute(String inputString)
  {
     if (SerialDebug) {
     Serial.print("SlaveID: ");
     Serial.print(CheckSlaveId);
     Serial.println();
     }
    String IdString = getValue(inputString, 0);
    Id = IdString.toInt(); 
    if (Id != CheckSlaveId && Id != 0) {return;}
    
   
    String LedIdString = getValue(inputString, 2);
    int tmpledid,tmpBlinken,tmpR,tmpG,tmpB;
    tmpledid = LedIdString.toInt();
    if (tmpledid != ledIndex && tmpledid != 0) {return;}

    String CmdString = getValue(inputString, 1);
    Cmd = CmdString.toInt();
    String RString = getValue(inputString, 3);
    tmpR = RString.toInt();
    String GString = getValue(inputString, 4);
    tmpG = GString.toInt();
    String BString = getValue(inputString, 5);
    tmpB = BString.toInt();
    String BlinkenString = getValue(inputString, 6);
    tmpBlinken = BlinkenString.toInt();
    if (SerialDebug) {
            Serial.print("Id");
            Serial.print(Id);
            Serial.print("/");
            Serial.print("Cmd: ");
            Serial.print(Cmd);
            Serial.print("/");
            Serial.print("LedId: ");
            Serial.print(tmpledid);
            Serial.print("/");
            Serial.print("R: ");
            Serial.print(tmpR);
            Serial.print("/");
            Serial.print("G: ");
            Serial.print(tmpG);
            Serial.print("/"); 
            Serial.print("B: ");
            Serial.print(tmpB);
            Serial.print("/");
            Serial.print("Blinken: ");
            Serial.print(tmpBlinken);
             Serial.println();
            } 
  
    
    if (tmpBlinken == 1) 
    {
       SetBlinken(true);
     }
    else
    {
      SetBlinken(false);
    }
    SetPixelColor(tmpR,tmpG,tmpB);    
    }
};


Led::Led(int newledindex)
{
  ledIndex = newledindex;
  BlinkenLedAus=false;
  Blinken =false;
  MbBlinken = false;
}


void Led::SetPixelColor(int Rval,int Gval, int Bval)
{
    R= Rval;
    G= Gval;
    B= Bval;
    if (SerialDebug) {
    Serial.print("ledIndex: ");
    Serial.print(ledIndex);
    Serial.println(); 
    }
   pixels.setPixelColor(ledIndex -1, pixels.Color(R,G,B)); // Moderately bright green color.  
   pixels.show();    
}

void Led::SetPixelColor(uint32_t color)
{     
   pixels.setPixelColor(ledIndex -1, color); // Moderately bright green color.  
   pixels.show();
}

void Led::SetBlinken(bool BlinkVal)
{
   
   if (Blinken != BlinkVal)
   {
      blinkTimerMilli= millis();
      Blinken = BlinkVal;
      if (SerialDebug) {
      Serial.print("Blinken:");
      Serial.print(Blinken);
      Serial.println();
      }
   }
}


void   Led::ExecBlinken()
{
 
      if (Blinken == false && BlinkenLedAus == false) 
      {
        return;
      }
    
      currentMillis=millis();
      if (currentMillis-blinkTimerMilli < 300) 
      {
        return;
      }
       MbBlinken = !MbBlinken;
       switch (MbBlinken) {
       case true:
         pixels.setPixelColor(ledIndex -1, pixels.Color(R,G,B));
         BlinkenLedAus == false;
       break;
       case false:
         pixels.setPixelColor(ledIndex -1,pixels.Color(0,0,0)); 
         BlinkenLedAus == true;
       break;
        }
          
     pixels.show(); // This sends the updated pixel color to the hardware.
     blinkTimerMilli = currentMillis;
   
}
