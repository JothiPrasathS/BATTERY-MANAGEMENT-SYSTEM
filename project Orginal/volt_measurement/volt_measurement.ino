#include <LiquidCrystal.h>  
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

//////////////////////////////////////////////////////

float Vcin=0,Vcout=0;
float R1 = 10000;              // R1 = 10K ohm                                       
float R2 = 1000;               // R2 =  1K ohm 
float Vdin=0,Vdout=0;
float R3 = 10000;              // R3 = 10K ohm                                       
float R4 = 1000;               // R4 =  1K ohm 

/////////////////////////////////////////////////////

double Voltage = 0;
double Current = 0;
double Voltage1 = 0;
double Current1 = 0;
float Batterycapacity = 11.1;            //2000mAh 3.7v Li-ion
float Devicewatt = 2;               //2.5 Watts 12v gear Motor, inverter Load

//////////////////////////////////////////////////////

void setup()
{  
lcd.begin(20, 4);  
Serial.begin(9600);
}

////////////////////////////////////////////////////

void loop() 
{
float S = analogRead(A4);   // Solar in            
float si = S*0.027; //6.6V
float I = analogRead(A5);   //inverter output           
float io = I*0.6; //250V

////////////////////////////////////////////////////////////////

float C=analogRead(A0);       //read from A3
Vcout = C*(4.5/1024.0);        //convert into voltage
Vcin = Vcout*((R1+R2)/R2);      //voltage divider equation 

////////////////////////////////////////////////////////////

float D=analogRead(A1);       //read from A4
Vdout = D*(4.5/1024.0);        //convert into voltage
Vdin = Vdout*((R3+R4)/R4);      //voltage divider equation 

//////////////////////////////////////////////////////////////// charging

for(int i = 0; i < 1000; i++)   // Voltage is Sensed 1000 Times for precision
{
Voltage = (Voltage + (.0049 * analogRead(A2) ) );    // (5 V / 1024 (Analog) = 0.0049) which converter Measured analog input voltage to 5 V Range
delay(1);
}
Voltage = Voltage /1000;
Current = (Voltage -3.175)/ 0.100; // Sensed voltage is converter to current 5Amp=185, 20Amp=100, 30Amp=66

///////////////////////////////////////////////////////// discharging

for(int i = 0; i < 1000; i++)   // Voltage is Sensed 1000 Times for precision
{
Voltage1 = (Voltage1 + (.0049 * analogRead(A3) ) );    // (5 V / 1024 (Analog) = 0.0049) which converter Measured analog input voltage to 5 V Range
delay(1);
}
Voltage1 = Voltage1 /1000;
Current1 = (Voltage1 -3.21)/ 0.183; // Sensed voltage is converter to current 5Amp=185, 20Amp=100, 30Amp=66

////////////////////////////////////////////////////////////////////

float t = (Batterycapacity / Current);      //Charging Time = Battery Capacity in Ah / Charging current in Ampere.
float Ct = ((t*0.30)+t);                //Constant current = 0.6 and HW kit = Current;

////////////////////////////////////////////////////////////////////

float Dt = ((Batterycapacity * Vdin * 0.9)/Devicewatt);      //Discharging Time = (Battery Capacity * Battery Volt * 0.9 )/ Device Watt.

//////////////////////////////////////////////////////////////////////

lcd.setCursor(0,0);   //Charging volt amps
lcd.print("Vc=");  
lcd.print(Vcin,2);    
lcd.print("V"); 
lcd.print(" ");
//delay(1000);
lcd.setCursor(9,0); 
lcd.print(", Ic=");  
lcd.print(Current,2);    
//lcd.print("A"); 
lcd.print(" ");
//delay(1000);

////////////////////////////////////////////////////////////

if(Vdin < 1)    //Discharging volt amps
{
  lcd.setCursor(0,1);   
  lcd.print("Vd=0.00");   
  lcd.print("V"); 
  lcd.print(" ");
}
 else
 {
  lcd.setCursor(0,1);   
  lcd.print("Vd=");  
  lcd.print(Vdin,2); 
  lcd.print("V"); 
  lcd.print(" ");
 }
lcd.setCursor(9,1); 
lcd.print(", Id=");  
lcd.print(Current1,2);    
//lcd.print("A"); 
lcd.print(" ");

///////////////////////////////////////////////////////////

if(Current < 0.09)   //0.09 error in charging current sensor
{
 lcd.setCursor(0,2); 
 lcd.print("Ct=0.00");      
 lcd.print("h"); 
 lcd.print(" ");
}
 else
 {
 lcd.setCursor(0,2); 
 lcd.print("Ct=");  
 lcd.print(Ct);    
 lcd.print("h"); 
 lcd.print(" ");
 }
 
///////////////////////////////////////////////////

if(Current1 < 0.07)   //0.07 error in Discharging current sensor
{
  lcd.setCursor(9,2);
  lcd.print(",Dt=0.00"); 
  lcd.print("h"); 
  lcd.print(" "); 
}
 else
 {
  lcd.setCursor(9,2);  
  
  lcd.print(",Dt=");  
  lcd.print(Dt);    
  lcd.print("h"); 
lcd.print(" ");
 }
 
////////////////////////////////////////////////

lcd.setCursor(0,3);  
lcd.print("Sin=");  
lcd.print(si,2);    //lcd.print("V");
lcd.print(" ");  
lcd.setCursor(9,3);   
lcd.print(",AC=");   
lcd.print(io);    
//lcd.print("V");
lcd.print(" ");
//delay(1000);
//lcd.clear();
}
