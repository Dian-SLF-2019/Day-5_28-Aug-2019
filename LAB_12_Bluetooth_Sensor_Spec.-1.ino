#include <SoftwareSerial.h>
#include <Wire.h>
SoftwareSerial mySerial(2,3); //Define PIN11 & PIN12 as RX and TX pins

int PIN_RED = 9;
int PIN_GREEN = 10;
int PIN_BLUE = 11;

String RGB = ""; 
String RGB_Previous = "255.255.255"; 
String ON = "ON"; 
String OFF = "OFF"; 
boolean RGB_Completed = false;
 
void setup() {
  pinMode (PIN_RED, OUTPUT);
  pinMode (PIN_GREEN, OUTPUT);
  pinMode (PIN_BLUE, OUTPUT);
  Serial.begin(9600); 
  mySerial.begin(9600);
  RGB.reserve(30);
}
 
void loop() {

  while(mySerial.available()){
    char ReadChar = (char)mySerial.read();
 
    if(ReadChar == ')'){
      RGB_Completed = true;
    }else{
       RGB += ReadChar;
    }
  }
  
  if(RGB_Completed){
 
      Serial.print("RGB:");
      Serial.print(RGB);
      Serial.print("     PreRGB:");
      Serial.println(RGB_Previous);
      
      if(RGB==ON){
          RGB = RGB_Previous; 
          Light_RGB_LED();
      }else if(RGB==OFF){
          RGB = "0.0.0"; 
          Light_RGB_LED();
      }else{
          Light_RGB_LED();   
          RGB_Previous = RGB;     
      }
      RGB = "";
      RGB_Completed = false;      
  } 
} 
 
void Light_RGB_LED(){
 
  int SP1 = RGB.indexOf(' ');
  int SP2 = RGB.indexOf(' ', SP1+1);
  int SP3 = RGB.indexOf(' ', SP2+1);
  String R = RGB.substring(0, SP1);
  String G = RGB.substring(SP1+1, SP2);
  String B = RGB.substring(SP2+1, SP3);

  Serial.print("R=");
  Serial.println( constrain(R.toInt(),0,255));
  Serial.print("G=");
  Serial.println(constrain(G.toInt(),0,255));
  Serial.print("B=");
  Serial.println( constrain(B.toInt(),0,255));
 
  analogWrite(PIN_RED,  (R.toInt()));
  analogWrite(PIN_GREEN, (G.toInt()));
  analogWrite(PIN_BLUE,  (B.toInt()));
 
}
