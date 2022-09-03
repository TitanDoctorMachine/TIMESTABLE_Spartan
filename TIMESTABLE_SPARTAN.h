#ifndef TIMESTABLE_SPARTAN_H
#define TIMESTABLE_SPARTAN_H

#include <Arduino.h>

class TIMESTABLE_SPARTAN{
      public:

      bool begin();
      void update();

      String GetRunningTime();      
      String GetFormatedTIME();
      String GetFormatedDATE();

      int GetHours();
      int GetMinute();
      int GetSeconds();
      
      int GetDay();
      int GetMonth();
      int GetYear();

      
};


#endif
