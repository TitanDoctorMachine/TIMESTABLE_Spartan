#include "TIMESTABLE_SPARTAN.h"
#include <NTPClient.h>
#include <WiFiUdp.h>

const long OffsetSeconds = -10800; // Need to change per geographic region;

WiFiUDP ntpUDP;
NTPClient timeReference_1(ntpUDP, "pool.ntp.org", OffsetSeconds); 
NTPClient timeReference_2(ntpUDP, "b.ntp.br", OffsetSeconds);
NTPClient timeReference_3(ntpUDP, "a.st1.ntp.br", OffsetSeconds);

int BeginStartTime, nextMintUpdate; //Yes, its MINT flavor, YUMMY!
time_t GlobalepochTime; 
time_t Server_Time_Secs;
struct tm * Server_Time = gmtime ((time_t *)&Server_Time_Secs);

/* MADE FOR ESP8266 USE;
NEED INTERNET CONNECTION;
FOR SPARTAN_INFRASTRUCTURE SOFTWARES;
*/

bool GetNetTime(){

//redundancy methods, three Servers;
        if (timeReference_1.update()){
            GlobalepochTime = timeReference_1.getEpochTime();        
            BeginStartTime = timeReference_1.getMinutes();
            return 1;

        } else if (timeReference_2.update()){
            GlobalepochTime = timeReference_2.getEpochTime();        
            BeginStartTime = timeReference_2.getMinutes();
            return 1;

        } else if (timeReference_3.update()){
            GlobalepochTime = timeReference_3.getEpochTime();        
            BeginStartTime = timeReference_3.getMinutes();
            return 1;

        } else {
        return 0;
        
        }
}


bool TIMESTABLE_SPARTAN::begin(){

  timeReference_1.begin();
  timeReference_2.begin();
  timeReference_3.begin();
  bool retr = GetNetTime();
    
    nextMintUpdate = BeginStartTime + 2;
      if (nextMintUpdate >= 60){nextMintUpdate = 0;}

    return retr;

}
void mkeit(){Server_Time = gmtime ((time_t *)&Server_Time_Secs);} // to update structure

void TIMESTABLE_SPARTAN::update(){
      
        time_t SySTime = millis() / 1000;        
        
        if (Server_Time->tm_min == nextMintUpdate){ // TaskedSync
          nextMintUpdate = Server_Time->tm_min + 2; // add +2 minutes
          if (nextMintUpdate >= 60){nextMintUpdate = 0;}
              if (GetNetTime()){
              GlobalepochTime = GlobalepochTime - SySTime;
              //Serial.println("GetNetTime!"); DEBUG
              } 
        }
        Server_Time_Secs = GlobalepochTime + SySTime;
        mkeit();
}


String TIMESTABLE_SPARTAN::GetRunningTime(){
        String Formated_Output = "";
        time_t SySTime = millis() / 1000;        
        struct tm *RunningTime = gmtime ((time_t *)&SySTime);

          Formated_Output += String (RunningTime->tm_hour);    
          Formated_Output += ":";
          Formated_Output += String(RunningTime->tm_min);
          Formated_Output += ":";
          Formated_Output += String(RunningTime->tm_sec);

        return Formated_Output;

}

String TIMESTABLE_SPARTAN::GetFormatedTIME(){
    
     mkeit();
     String FormTime = String(Server_Time->tm_hour);
            FormTime += ":";
            FormTime += String(Server_Time->tm_min);
            FormTime += ":";
            FormTime += String(Server_Time->tm_sec);
     return FormTime;
}
          
String TIMESTABLE_SPARTAN::GetFormatedDATE(){
    
     mkeit();
     String FormTime = String(Server_Time->tm_mday);
            FormTime += "/";
            FormTime += String(Server_Time->tm_mon + 1);
            FormTime += "/";
            FormTime += String(Server_Time->tm_year + 1900);
     return FormTime; 
}

int TIMESTABLE_SPARTAN::GetHours(){mkeit();return Server_Time->tm_hour;}
int TIMESTABLE_SPARTAN::GetMinute(){mkeit();return Server_Time->tm_min;}
int TIMESTABLE_SPARTAN::GetSeconds(){mkeit();return Server_Time->tm_sec;}
int TIMESTABLE_SPARTAN::GetDay(){mkeit();return Server_Time->tm_mday;}
int TIMESTABLE_SPARTAN::GetMonth(){mkeit();return Server_Time->tm_mon;}
int TIMESTABLE_SPARTAN::GetYear(){mkeit();return Server_Time->tm_year;}
//endofall