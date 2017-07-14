#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

int STBY = 10; //standby

//Motor A
int PWMA = 3; //Speed control 
int AIN1 = 9; //Direction
int AIN2 = 8; //Direction

//Motor B
int PWMB = 5; //Speed control
int BIN1 = 11; //Direction
int BIN2 = 12; //Direction

void setup(){
  Serial.begin(9600);
  Serial.println("So it begins");
  pinMode(STBY, OUTPUT);

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);


  mySwitch.enableReceive(0);
}

void loop(){
if (mySwitch.available()) {
    
    int value = mySwitch.getReceivedValue();

     Serial.print(value);
     Serial.print(": " );
    switch (value) {
       
       case 1000:
       Serial.println("Forward");
       move(1, 255, 1);
       move(0, 255, 1);
       break;
       case 1250:
       Serial.println("Forward half");
       move(1, 128, 1);
       move(0, 128, 1);
       break;
       case 1500:
       Serial.println("Forward and right");
       move(1, 128, 1);
       move(0, 100, 1);
       break;
       case 2000:
       Serial.println("Right");
       move(1, 128, 0);
       move(0, 128, 1);
       break;
       case 2500:
       Serial.println("Reverse and right");
         //move(1, 128, 0);
       //move(2, 128, 1);
       break;
       case 3000:
       Serial.println("Reverse");
       move(1, 128, 0);
       move(2, 128, 0);
       break;
       case 3500:
       Serial.println("Reverse and left");
        // move(1, 128, 1);
       //move(2, 128, 0);
       break;
       case 4000:
       Serial.println("Left");
       move(1, 128, 1);
       move(2, 128, 0);
       break;
       case 4500:
       Serial.println("Forward and left");
        // move(1, 128, 1);
       //move(2, 128, 0);
       break;
       case 1:
       Serial.println("Stay still");
       stop();
       break;
      }

    mySwitch.resetAvailable();

  } 
     

delay(10);
}
void move(int motor, int speed, int direction){
  digitalWrite(STBY, HIGH); //disable standby

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if(direction == 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }

  if(motor == 1){
    digitalWrite(AIN1, inPin1);
    digitalWrite(AIN2, inPin2);
    analogWrite(PWMA, speed);
  }else{
    digitalWrite(BIN1, inPin1);
    digitalWrite(BIN2, inPin2);
    analogWrite(PWMB, speed);
  }
}

void stop(){
  digitalWrite(STBY, LOW); 
}
