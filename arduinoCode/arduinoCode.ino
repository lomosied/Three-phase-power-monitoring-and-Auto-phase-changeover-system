// include the library code:
#include <LiquidCrystal.h>

///Sim800L
#include <SoftwareSerial.h>
//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(11, 10); //SIM800L Tx & Rx is connected to Arduino #11 & #10  

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 33, en = 31, d4 = 29, d5 = 27, d6 = 25, d7 = 23;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int valueR = 0;
int valueY = 0;
int valueB = 0;

float dcVoltageR;
float dcVoltageY;
float dcVoltageB;

float acVoltageR;
float acVoltageY;
float acVoltageB;

/****Declaration of Load pins****/
/*
 * Loads on R phase = 1, 2
 * Loafs on Y phase = 3, 4
 * Loads on B Phase = 5, 6
 */
int Load1S0 = 2;
int Load1S1 = 3;
int Load1S2 = 4;
int Load1S3 = 5;

int Load2S0 = 6;
int Load2S1 = 7;
int Load2S2 = 8;
int Load2S3 = 9;

int Load7S0 = 12;
int Load7S1 = 13;
int Load7S2 = 34;
int Load7S3 = 36;

int Load12S0 = 38;
int Load12S1 = 40;
int Load12S2 = 42;
int Load12S3 = 44;
/***End of Loads****/
String message;

void setup(){
  Serial.begin(9600);

    lcd.begin(16, 2);

  /****Declaration of Load pins****/
pinMode(Load1S0, OUTPUT);
pinMode(Load1S1, OUTPUT);
pinMode(Load1S2, OUTPUT);
pinMode(Load1S3, OUTPUT);

pinMode(Load2S0, OUTPUT);
pinMode(Load2S1, OUTPUT);
pinMode(Load2S2, OUTPUT);
pinMode(Load2S3, OUTPUT);

pinMode(Load7S0, OUTPUT);
pinMode(Load7S1, OUTPUT);
pinMode(Load7S2, OUTPUT);
pinMode(Load7S3, OUTPUT);

pinMode(Load12S0, OUTPUT);
pinMode(Load12S1, OUTPUT);
pinMode(Load12S2, OUTPUT);
pinMode(Load12S3, OUTPUT);
/***End of Loads****/

digitalWrite(Load1S0, LOW);
}

void loop(){
  valueR = analogRead(A0);
  dcVoltageR = valueR * 5.0/1023;
  acVoltageR = (dcVoltageR*50.8163)+ 0;

   valueY = analogRead(A1);
  dcVoltageY = valueY * 5.0/1023;
  acVoltageY = (dcVoltageY*50.8163)+ 0;

  valueB = analogRead(A2);
  dcVoltageB = valueB * 5.0/1023;
  acVoltageB = (dcVoltageB*50.8163)+ 0;
/*
  Serial.print("dcVoltageR = ");
  Serial.println(dcVoltageR);
  delay(500);

  Serial.print("acVoltageR = ");
  Serial.println(acVoltageR);
  delay(500);

  Serial.print("dcVoltageY = ");
  Serial.println(dcVoltageY);
  delay(500);
  Serial.print("acVoltageY = ");
  Serial.println(acVoltageY);
  delay(500);
 
  Serial.print("dcVoltageB = ");
  Serial.println(dcVoltageB);
  delay(500);
  
  Serial.print("acVoltageB = ");
  Serial.println(acVoltageB);
  delay(500);
 */
  /*Priority to loads 1, 4 & 5*/
  lcd.setCursor(0, 0);
  lcd.print("R:");
  lcd.println(acVoltageR);
    lcd.setCursor(9, 0);
  lcd.print("Y:");
  lcd.println(acVoltageY);
    lcd.setCursor(0, 1);
  lcd.print("B:");
  lcd.println(acVoltageR);
  
//////Switching Voltages on Red//////
  if (acVoltageR < 50 && acVoltageY > 200 && acVoltageB > 200 )
  {
lcd.clear();
lcd.setCursor(0, 0);
lcd.println("R phase Down");   
    digitalWrite(Load1S0, HIGH);
    digitalWrite(Load2S0, HIGH);
    digitalWrite(Load1S3, HIGH);
    digitalWrite(Load1S2, HIGH);
    digitalWrite(Load2S1, HIGH);
    digitalWrite(Load2S3, HIGH);
    digitalWrite(Load12S2, HIGH);
    
      digitalWrite(Load1S1, LOW);
      digitalWrite(Load2S2, LOW);
      message = "Red Phase down \n Priority loads Distributed \n Check Distribution Board";
      sendMessage();
      }
     else if (acVoltageR < 50 && acVoltageY < 50 && acVoltageB > 200){
lcd.clear();
lcd.setCursor(0, 0);
lcd.println("R&Y phase Down");   
      
    digitalWrite(Load1S0, HIGH);
    digitalWrite(Load2S0, HIGH);
    digitalWrite(Load1S1, HIGH);
    digitalWrite(Load1S2, HIGH);
    digitalWrite(Load7S0, HIGH);
    digitalWrite(Load7S1, HIGH);
    digitalWrite(Load7S2, HIGH);
    digitalWrite(Load2S1, HIGH);
    digitalWrite(Load2S3, HIGH);
    digitalWrite(Load12S1, HIGH);
    digitalWrite(Load12S2, HIGH);
    
    
      digitalWrite(Load1S3, LOW);
      digitalWrite(Load2S2, LOW);
      digitalWrite(Load7S3, LOW);
      message = "Red & Yellow Phase down \n Priority loads Distributed \n Check Distribution Board";
      sendMessage();
      }
      else if (acVoltageR < 50 && acVoltageY > 200 && acVoltageB < 50){
        lcd.clear();
lcd.setCursor(0, 0);
lcd.println("R&B phase Down");   

    digitalWrite(Load1S0, HIGH);
    digitalWrite(Load2S0, HIGH);
    digitalWrite(Load2S1, HIGH);
    digitalWrite(Load12S0, HIGH);
    digitalWrite(Load12S1, HIGH);
    digitalWrite(Load12S2, HIGH);
    digitalWrite(Load7S1, HIGH);
    digitalWrite(Load1S3, HIGH);
    digitalWrite(Load7S2, HIGH);
    digitalWrite(Load2S2, HIGH);
    digitalWrite(Load1S2, HIGH);
    
        digitalWrite(Load1S1, LOW);
        digitalWrite(Load2S3, LOW);
        digitalWrite(Load12S3, LOW);
   message = "Red & Blue Phase down \n Priority loads Distributed \n Check Distribution Board";
   sendMessage();
        }

  

////Switching Voltages on Yellow/////
  else if (acVoltageY < 50 && acVoltageR > 200 && acVoltageB > 200){
    lcd.clear();
lcd.setCursor(0, 0);
lcd.println("Y phase Down");   
    digitalWrite(Load7S0, HIGH);
    digitalWrite(Load7S2, HIGH);
    digitalWrite(Load7S3, HIGH);
    digitalWrite(Load1S1, HIGH);
    digitalWrite(Load2S1, HIGH);
    digitalWrite(Load12S1, HIGH);
   
    //Serial.println("Phase failure on Yellow phase");
    digitalWrite(Load7S1, LOW);
    message = "Yellow Phase down \n Priority loads Distributed \n Check Distribution Board";
    sendMessage();
    }

   /**CONDITION ALREADY MET
     else if (acVoltageY < 50 && acVoltageR < 50 && acVoltageB > 200 ){
     digitalWrite(Load7S1, HIGH);
     digitalWrite(Load7S0, HIGH);
      digitalWrite(Load7S1, HIGH);
     
     digitalWrite(Load7S2, LOW);
     
      }
      */
     else if (acVoltageY < 50 && acVoltageB < 50 && acVoltageR > 200){
      lcd.clear();
lcd.setCursor(0, 0);
lcd.println("Y&B phase Down");   
      digitalWrite(Load7S0, HIGH);
      digitalWrite(Load7S1, HIGH);
      digitalWrite(Load1S1, HIGH);
      digitalWrite(Load2S1, HIGH);
      digitalWrite(Load12S2, HIGH);
      digitalWrite(Load12S1, HIGH);
      digitalWrite(Load12S0, HIGH);
      digitalWrite(Load1S2, HIGH);
      digitalWrite(Load2S2, HIGH);
      digitalWrite(Load7S2, HIGH);
      
      digitalWrite(Load7S3, LOW);
      digitalWrite(Load12S3, LOW);

      message = "Yellow & Blue Phase down \n Priority loads Distributed \n Check Distribution Board";
      sendMessage();
      }

   
///////Switching Loads on Blue////////
   else if (acVoltageB < 2 && acVoltageR > 200 && acVoltageY > 200){
    lcd.clear();
lcd.setCursor(0, 0);
lcd.println("B phase Down");   
      digitalWrite(Load12S0, HIGH);
      digitalWrite(Load1S2, HIGH);
      digitalWrite(Load2S2, HIGH);
      digitalWrite(Load7S2, HIGH);
      digitalWrite(Load12S2, HIGH);
      digitalWrite(Load12S3, HIGH);

      digitalWrite(Load12S1, LOW);
     // Serial.println("Phase failure on Blue phase");
     message = "Blue Phase down \n Priority loads Distributed \n Check Distribution Board";
     sendMessage();
    }
    /****CONDITION ALREADY MET
        else if (acVoltageB < 50 && acVoltageY <  50 && acVoltageR > 200){
          digitalWrite(Load12S0, HIGH);
          digitalWrite(Load12S1, HIGH);
          
          digitalWrite(Load12S3, LOW);
         
        }
       
          else if (acVoltageB < 50 && acVoltageR < 50 && acVoltageY > 200){
          digitalWrite(Load12S0, HIGH);
          digitalWrite(Load12S2, HIGH);
            
            digitalWrite(Load12S1, LOW);
            }
             */

/////Switching to standby/////////
    else if (acVoltageR < 50 && acVoltageY < 50 && acVoltageB < 2){
      lcd.clear();
lcd.setCursor(0, 0);
lcd.println("R,Y&B phase Down");   
    digitalWrite(Load1S0, HIGH);
    digitalWrite(Load2S0, HIGH);
    digitalWrite(Load1S3, HIGH);
    digitalWrite(Load2S3, HIGH);
    digitalWrite(Load12S2, HIGH);
    digitalWrite(Load7S0, HIGH);
    digitalWrite(Load7S1, HIGH);
    digitalWrite(Load1S1, HIGH);
    digitalWrite(Load2S1, HIGH);
    digitalWrite(Load12S1, HIGH);
    digitalWrite(Load12S0, HIGH);
      digitalWrite(Load1S2, HIGH);
      digitalWrite(Load2S2, HIGH);
      digitalWrite(Load7S2, HIGH);



      digitalWrite(Load1S3, LOW);
      digitalWrite(Load2S3, LOW);
      digitalWrite(Load7S3, LOW);
      digitalWrite(Load12S3, LOW);
      message = "Red,Yellow & Blue Phase down \n Priority loads Distributed \n Check Distribution Board";
      sendMessage();
      }

   
    else if (acVoltageB >200 && acVoltageR > 200 && acVoltageY > 200){
      digitalWrite(Load1S1, HIGH);
      digitalWrite(Load1S2, HIGH);
      digitalWrite(Load2S2, HIGH);
      digitalWrite(Load2S1, HIGH);
      digitalWrite(Load7S1, HIGH);
      digitalWrite(Load7S2, HIGH);
      digitalWrite(Load12S1, HIGH);
      digitalWrite(Load12S2, HIGH);
      digitalWrite(Load1S3, HIGH);
      digitalWrite(Load2S3, HIGH);
      digitalWrite(Load7S3, HIGH);
      digitalWrite(Load12S3, HIGH);
      
      
      
     digitalWrite(Load1S0, LOW);
     digitalWrite(Load2S0, LOW);
     digitalWrite(Load7S0, LOW);
      digitalWrite(Load12S0, LOW);
      }
      else {}
}
void sendMessage()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);  
  //Begin serial communication with Arduino and SIM800L
     mySerial.begin(9600);
  Serial.println("Initializing..."); 
  delay(1000);
  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
 mySerial.println("AT+CMGS=\"+254797690227\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  
  mySerial.print(message); //text content
  updateSerial();
  mySerial.write(26);
  }

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
