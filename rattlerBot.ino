#include "DualVNH5019MotorShield.h"

DualVNH5019MotorShield md;
int drivePow = 100;

void stopIfFault()
{
  if (md.getM1Fault())
  {
    Serial.println("M1 fault\n");
//    while(1);
  }
  if (md.getM2Fault())
  {
    Serial.println("M2 fault\n");
//    while(1);
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.write("Hey friend\n");
  md = DualVNH5019MotorShield();
  md.init();
}

void loop()
{
  while(!Serial.available()) {
  }
  char input = Serial.read();
  Serial.write(input);
  switch(input) {
    case 'f':
      forward();
      break;  
    case 'b':
      backward();
      break;
    case 'l':
      left();
      break;
    case 'r':
      right();
      break;
    case 's':
      halt();
      break;
    case 'p':
      drivePow += 10;
      Serial.println(drivePow);
      break;
    case 'm':
      drivePow -= 10;
      Serial.println(drivePow);
      break;
  }
  delay(50);
}

void forward() {
  halt();
  md.setM1Speed(drivePow);
  md.setM2Speed(drivePow);
  stopIfFault();
}

void backward() {
  halt();
  md.setM1Speed(-drivePow);
  md.setM2Speed(-drivePow);
  stopIfFault();
}

void left() {
  halt();
  md.setM1Speed(-drivePow);
  md.setM2Speed(drivePow);
  stopIfFault();
}

void right() {
  halt();
  md.setM1Speed(drivePow);
  md.setM2Speed(-drivePow);
  stopIfFault();
}

void halt() {
  md.setM1Speed(0);
  md.setM2Speed(0);
  delay(500);
//  md.setM1Brake(drivePow);
//  md.setM2Brake(drivePow);
  stopIfFault();
}
