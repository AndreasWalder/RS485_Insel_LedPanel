#include "Arduino.h"
#include "Led.h"
const int LedCount = 8;

 Led ledArray[] = {(1),(2),(3),(4),(5),(6),(7),(8)};
 class LedPanel

{
  public:
        
        void initLedPanel(int SlaveId);
        void ExecutePanel();
        void InputExecute(String inputString);
        //LedPanel(); 
          
         
  private:
        int mySlaveId;  
        uint32_t initFarbe;
        uint32_t LedOff = pixels.Color(0,0,0); // Led color aus
        uint32_t magenta = pixels.Color(50, 0, 50);
        uint32_t red = pixels.Color(50, 0, 0);
        uint32_t green = pixels.Color(0, 10, 0);
        uint32_t blue = pixels.Color(0, 0, 50);
        uint32_t yellow = pixels.Color(62, 40, 0);
        uint32_t purple = pixels.Color(40, 0, 40);
        uint32_t aqua = pixels.Color(0, 50, 50);   
        Led *ptTmp;
              
};

 

void LedPanel::initLedPanel(int SlaveId)
   {

          mySlaveId = SlaveId;
          ptTmp = ledArray;
          
           pixels.begin(); // This initializes the NeoPixel library.
            if (mySlaveId == 0)
             {    
                for(int i=0;i<4;i++){
                    initFarbe = red;
                    for(int i=0;i<LedCount;i++){
                    ptTmp[i].SetPixelColor(initFarbe);
                    }
                    delay(500); // Delay for a period of time (in milliseconds).
                    for(int i=0;i<LedCount;i++){
                    ptTmp[i].SetPixelColor(LedOff);
                    }
                    delay(500); // Delay for a period of time (in milliseconds).
               }
            return;
            }
            
            if (mySlaveId == 1)
            {    
            initFarbe = green;
            }
             if (mySlaveId == 2)
            {    
              initFarbe = blue;
            }
             if (mySlaveId == 3)
            {    
             initFarbe = purple;
            }
             if (mySlaveId == 4)
            {    
             initFarbe = yellow;
            }

           
           for(int i=0;i<LedCount;i++){
           ptTmp[i].SetPixelColor(initFarbe);
           delay(100); // Delay for a period of time (in milliseconds).
           }
      
           for (int i=LedCount;i>=0;i--) {
           ptTmp[i].SetPixelColor(LedOff);
           delay(100); // Delay for a period of time (in milliseconds).
          }
       
 
   }

//  LedPanel::LedPanel()
//   {
//    //ptTmp=ledArray;
//   }

  void LedPanel::ExecutePanel()
  {
    for(int i=0;i<LedCount;i++){
        ledArray[i].ExecBlinken();
     }
     
  }

  void LedPanel::InputExecute(String inputString)
  {
    
    ptTmp=ledArray;  
    for(int i=0;i<LedCount;i++){
        ptTmp[i].InputExecute(inputString);
    }
  }
  

