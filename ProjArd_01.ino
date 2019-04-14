
#include <Servo.h>
#include <Stepper.h>

Stepper stp = Stepper(100,8,10,9,11); //must be in order 1,3,2,4 because chip maker sux
Servo liftServo;
int pot = A0;
int potVal = 0;
int lift = 3;
int liftPos = 10;
int potBase = 0;
int pth = 20; //pot threshold
int linPos = 0;

void setup() 
{
  liftServo.attach(lift);
  Serial.begin(9600);
  stp.setSpeed(200);
  liftArm();
  delay(1000);
  setBase();
  findzero();
}

void loop() 
{ 

  liftArm();
  int del=0;
  moveTo(400);
  moveTo(10);
  lowerArm();
  delay(1000);
  
}
void moveTo(int x)
{
  if(linPos < x)
  {
    while(linPos < x)
    {
      moveRight();
    }
    return;
  }
  else if(linPos > x)
  {
    while(linPos > x)
    {
      moveLeft();
    }
    return;
  }
}

void moveLeft()
{
    stp.step(-5);
    linPos--;
}

void moveRight()
{
    stp.step(5);
    linPos++;
}

void findzero()
{
  potVal = analogRead(pot);
  while(potVal >= potBase-pth)
  {
    stp.step(-5);
    potVal = analogRead(pot);
  }
  linPos = 0;
}

void scoot()
{
  potVal = analogRead(pot);
  if(potVal < potBase-pth)
  {
    moveRight();
  }
  else if(potVal > potBase+pth*2)
  {
    moveLeft();
  }
  
}

void liftArm()
{
  while (liftPos>0)
  {
    liftServo.write(liftPos);
    liftPos--;
    delay(60);
  }
}

void lowerArm()
{
  while (liftPos<50)
  {
    liftServo.write(liftPos);
    liftPos++;
    delay(60);
  }
}

void setBase()
{
  liftArm();
  delay(1000);
  potBase = analogRead(pot);
}
