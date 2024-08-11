#include <SoftwareSerial.h>
SoftwareSerial SIM900(7, 8);
String textSMS;
int data = 0;
int val = 0;
int const tringpin = 13;
int const echopin = 5;
int inputpin = 10;
int pirState = LOW;
int ledpin = 11;

String f1001 = "+91XXXXXXXXXX";
String f1002 = "+91XXXXXXXXXX";
String f1003 = "+91XXXXXXXXXX";

void setup(){

  Serial.begin(9600);
  Serial.println("Calibrating the sensor");
  SIM900.begin(9600);
  pinMode(tringpin, OUTPUT);
  pinMode(echopin, INPUT);
  pinMode(ledpin, OUTPUT);
  pinMode(inputpin, INPUT);
  Serial.println(" logging time completed!");
  for (int i=0;i<15;i++){
    Serial.println(".");
    delay(1);
  }
  Serial.println("Done sensor is activated");
  delay(1);
}

void loop(){

  val = digitalRead(inputpin);

  int duration,distance;
  digitalWrite(tringpin, HIGH);
  delay(1);
  digitalWrite(tringpin, LOW);

  duration = pulseIn(echopin, HIGH);
  Serial.println("scanning the area");

  distance = (duration/2) / 29.1;
  

  if(distance <= 100 && distance >= 0 && val == HIGH){
    digitalWrite(ledpin, HIGH);
    Serial.println("object detected");
    Serial.println("Motion detected!");

    textSMS = "\nIntruder detected";
    sendsms(textSMS, f1001);
    Serial.println(textSMS);
    Serial.println("message sent.");
    delay(1000);

    sendsms("Intruder Detected!!!!!!!!!", f1002); 
  Serial.println(textSMS);
  Serial.println("message sent."); 
delay(1000);

  sendsms("Intruder Detected!!!!!!!!!", f1003); 
  Serial.println(textSMS);
  Serial.println("message sent."); 
delay(1000);
if (pirState == LOW){
      
      pirState = HIGH;
    }
  }else{
    digitalWrite(ledpin, LOW);
    if (pirState == HIGH){
      pirState = LOW;
    }
  }
}

void sendsms(String message, String number){
  String mnumber = "AT + CMGS = \""+number+"\"";
  SIM900.print("AT+CMGF=1\r");
  delay(1000);
  SIM900.println(mnumber);

  delay(1000);
  SIM900.println(message);
  delay(1000);
  SIM900.println((char)26);
  delay(1000);
  SIM900.println();
  delay(1000);
}
