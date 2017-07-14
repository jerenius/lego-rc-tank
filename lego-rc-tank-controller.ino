#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

int xPin1 = A1;
int yPin1 = A0;
int button1 = 6;
int xPosition1 = 0;
int yPosition1 = 0;
int buttonState1 = 0;
int sendCode = 0;

void setup() {
  Serial.begin(9600); 
  pinMode(xPin1, INPUT);
  pinMode(yPin1, INPUT);
  pinMode(button1, INPUT_PULLUP);
  mySwitch.enableTransmit(10); 
}

void loop() {
  xPosition1 = analogRead(xPin1);
  yPosition1 = analogRead(yPin1);
  buttonState1 = digitalRead(button1);
 
  if (yPosition1 < 500 and yPosition1 > 400 and xPosition1 > 400 and xPosition1 < 500)
  {
     Serial.println("Stop");
     sendCode = 1;
  }
  else if (yPosition1 > 500 and yPosition1 < 800 and xPosition1 > 300 and xPosition1 < 700)
  {
    Serial.println("Forward half speed");
    sendCode = 1250;
  } 
  else if (yPosition1 >= 800 and xPosition1 > 300 and xPosition1 < 700) 
  {
    Serial.println("Forward full speed");
    sendCode = 1000;
  }
  else if (yPosition1 >= 700 and xPosition1 >= 700)
  {
    Serial.println("Forward and turn right");
    sendCode = 1500;
  }
  else if (yPosition1 > 300 and yPosition1 < 700 and xPosition1 >= 700)
  {
    Serial.println("Turn right");
    sendCode = 2000;
  }
  else if (yPosition1 <= 300 and xPosition1 >= 700)
  {
    Serial.println("Reverse and turn right");
    sendCode = 2500;
  }
  else if (yPosition1 <= 300 and xPosition1 > 300 and xPosition1 < 700) 
  {
    Serial.println("Reverse");
    sendCode = 3000;
  }
  else if (yPosition1 <= 300 and xPosition1 <= 700)
  {
    Serial.println("Reverse and turn right");
    sendCode = 3500;
  }
  else if (yPosition1 > 300 and yPosition1 < 700 and xPosition1 <= 700)
  {
    Serial.println("Turn left");
    sendCode = 4000;
  }
  else if (yPosition1 >= 700 and xPosition1 <= 700)
  {
    Serial.println("Forward and turn left");
    sendCode = 4500;
  }
  
 mySwitch.send(sendCode, 24);

if (buttonState1 == 0)
  { 
    mySwitch.send(sendCode, 24); 
    Serial.println("Button pressed, stopping");
    delay(1000);
  }
   
  delay(75); // add some delay 
}
