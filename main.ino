#define TRIGGER 5
#define ECHO    4
#define motorpin 12
#define mindis 25 //add minumum distance here
#define led_pinR 10
#define led_pinG 9
#define pushbutton 2
//add pin num for led or relay here

#include <Servo.h>

Servo break_in;


void setup() {
  Serial.begin(9600);
  pinMode(pushbutton, INPUT);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(led_pinR, OUTPUT);
  pinMode(led_pinG, OUTPUT);
  break_in.attach(6);
  break_in.write(0);

  pinMode(motorpin, OUTPUT);

}
 
void loop() {
 
  // disatance calculator
  long duration, distance;
 
  
  digitalWrite(TRIGGER, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = (duration/2) / 29.1; // final distance in cm
  
  Serial.print(distance);
  Serial.println("Centimeter:");
  delay(1000);
  
  if ( distance < mindis){
    
    digitalWrite(led_pinR , HIGH);
    digitalWrite(led_pinG , LOW);
    break_in.write(90);
     digitalWrite(motorpin, LOW);

    
    //add what to do when minimum distance is reached
  }
  else if (distance < 50){
    digitalWrite(motorpin, HIGH);
    digitalWrite(led_pinG , LOW);
    break_in.write(0);
    
    digitalWrite(led_pinR , HIGH);
     
 
    
  }
  else{
    digitalWrite(led_pinR , LOW);
    digitalWrite(led_pinG , HIGH);
    break_in.write(0);
    digitalWrite(motorpin, HIGH);
  }
 
  int buttonState = digitalRead(pushbutton);
  
  if (buttonState == 1) {
       break_in.write(90);   // turn the LED on (HIGH is the voltage level)
  } else {
     break_in.write(0);    // turn the LED off by making the voltage LOW
  }
  
}
