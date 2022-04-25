#include <Servo.h>

const int buzzer = 2;
const int r_led=13;
const int g_led=10;
Servo servox; 

int maps,degree = 0,cm1 = 0,cm2 = 0;

bool person = false;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2); 
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT); 
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  Serial.begin(9600);
  servox.attach(4);
  servox.write(0);
  pinMode(r_led,OUTPUT); 
  pinMode(g_led,OUTPUT); 
}

void loop()
{
  cm1 = 0.01723 * readUltrasonicDistance(9, 9);
  delay(10);
  if(cm1 < 20){
    servox.write(90);
    person = true;
  }
  else if(20 < cm1 && cm1 < 60){
    maps = map(cm1, 20,60, 0, 90);
    degree = 90 - maps;
    servox.write(degree);
  }else{
    servox.write(0); 
  }
delay(10);
  if(person){
    digitalWrite(g_led,HIGH);
    person = false;
  }
  else{
    digitalWrite(g_led,LOW);

  }
  cm2 = 0.01723 * readUltrasonicDistance(5, 5);
  delay(10);
  if(cm2<10){
    digitalWrite(r_led,HIGH);
    tone(buzzer, 1000, 500);
  }
  else{
    digitalWrite(r_led,LOW);
  }
 }