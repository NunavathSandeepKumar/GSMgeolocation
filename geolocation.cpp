#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;
int temp=0,i;
// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
String stringVal = "";
void setup(){ 
 Serial.begin(9600); 
 ss.begin(GPSBaud); 
 lcd.begin(16,2); 
 pinMode(13,OUTPUT); 
 digitalWrite(13,LOW); 
 lcd.print("Vehicle Tracking"); 
 lcd.setCursor(0,1); 
 lcd.print("    System      "); 
 delay(2000); 
 gsm_init(); 
 lcd.clear();   
 Serial.println("AT+CNMI=2,2,0,0,0"); 
 lcd.print("GPS Initializing"); 
 lcd.setCursor(0,1); 
 lcd.print("  No GPS Range  ");  
 delay(2000); 
 lcd.clear(); 
 lcd.print("GPS Range Found"); 
 lcd.setCursor(0,1); 
 lcd.print("GPS is Ready"); 
 delay(2000); 
lcd.clear(); 
 lcd.print("System Ready"); 
 temp=0;
}

void loop()
{ 
serialEvent();
  
    while(temp)  
    {   
     while (ss.available() > 0)   
     {    
      gps.encode(ss.read());       
         if (gps.location.isUpdated())       
         {        
         temp=0;        
         digitalWrite(13,HIGH);        
         tracking();       
         }     
      if(!temp)        
  break;     
     }  
    }  
    digitalWrite(13,LOW);
}
void serialEvent()
{ 
 while(Serial.available()>0) 
 {  
   if(Serial.find("Track Vehicle")) 
   {  

    temp=1;      b
reak; 
   } 

   else 
   { 
   temp=0; 
   } 
 }
}
void gsm_init()
{ 
 lcd.clear(); 

 lcd.print("Finding Module.."); 
 boolean at_flag=1; 
while(at_flag) 
 { 
   Serial.println("AT"); 
   delay(1); 
   while(Serial.available()>0) 
   {  
    if(Serial.find("OK"))  
    at_flag=0; 
   } 
    
   delay(1000); 
 } 
 lcd.clear(); 
 lcd.print("Module Connected..");  delay(1000); 

 lcd.clear();  lcd.print("Disabling ECHO"); 
 boolean echo_flag=1; 
 while(echo_flag) 

 { 
   Serial.println("ATE0");    while(Serial.available()>0) 

   {      if(Serial.find("OK"))  
    echo_flag=0; 

   }    delay(1000); 

 }
