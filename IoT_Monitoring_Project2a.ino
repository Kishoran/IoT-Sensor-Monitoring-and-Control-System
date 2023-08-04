//using nodeMCU read value from distance sensor(ultrasonic sensor) and upload it to cloud(thinkspeak) and display it on a dashboard() in graphical format
//add button to control the device (turn ON or true OFF)
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>




const char*ssid = "Kishoran@02"; // Your network id
const char*password = "jillakanna";//your network password 
const int triggerPin = D6;
const int echoPin = D7;
const int  button = D3;

WiFiClient client;

unsigned long myChannelNumber = 2232999; //Your Channel Number (Without Brackets)
const char * myWriteAPIKey = "D4TNTAFE4GMPWZBC"; //Your Write API Key
const char * myReadAPIKey = "Z8H8NB6PQDQNAC58"; //Your Write API Key

int buttonState = 0;
int lastButtonState = 0;



void setup(){
  pinMode(triggerPin,OUTPUT); // trig
 pinMode(echoPin,INPUT); // echo
 pinMode(button , INPUT_PULLUP);
 
  Serial.begin(9600);
  delay(10);
  
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  ThingSpeak.begin(client);
  

}
void loop(){
 
 
  buttonState = digitalRead(button); 
  if(buttonState == HIGH && lastButtonState == LOW){
    digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  long  t = pulseIn(echoPin,HIGH);//return time in milliseconds untill pin 3 is high 

  int  dis =  t*0.034/2;

  Serial.println(dis);
 
  delay(1000);
  
  ThingSpeak.writeField(myChannelNumber, 1,dis, myWriteAPIKey); //Update in ThingSpeak
  delay(1000);
    
  }
  lastButtonState = buttonState;
  delay(50);


}