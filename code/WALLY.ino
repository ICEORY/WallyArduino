#define LP_SERVO 2
#define RP_SERVO 3
#define LP_LED  4
#define RP_LED  5
#define P_INF  1
#define LC_MOTOR 7
#define LP_MOTOR 9
#define RC_MOTOR 8
#define RP_MOTOR 10
void MotorInit()
{
  pinMode(LC_MOTOR, OUTPUT); //high for right running
  pinMode(LP_MOTOR, OUTPUT); //low for contray running
  pinMode(RC_MOTOR, OUTPUT); //high for run
  pinMode(RP_MOTOR, OUTPUT); //low for stop
}
void MotorGo()
{
  digitalWrite(LC_MOTOR,HIGH);
  digitalWrite(LP_MOTOR,HIGH);
  digitalWrite(RC_MOTOR,HIGH);
  digitalWrite(RP_MOTOR,HIGH);
}
void MotorLeft()
{
  digitalWrite(LC_MOTOR,LOW);
  digitalWrite(LP_MOTOR,HIGH);
  digitalWrite(RC_MOTOR,HIGH);
  digitalWrite(RP_MOTOR,HIGH);
}
void MotorRight()
{
  digitalWrite(LC_MOTOR,HIGH);
  digitalWrite(LP_MOTOR,HIGH);
  digitalWrite(RC_MOTOR,LOW);
  digitalWrite(RP_MOTOR,HIGH);
}
void MotorStop()
{
  digitalWrite(LC_MOTOR,HIGH);
  digitalWrite(LP_MOTOR,LOW);
  digitalWrite(RC_MOTOR,HIGH);
  digitalWrite(RP_MOTOR,LOW);
}
void MotorBack()
{
  digitalWrite(LC_MOTOR,LOW);
  digitalWrite(LP_MOTOR,HIGH);
  digitalWrite(RC_MOTOR,LOW);
  digitalWrite(RP_MOTOR,HIGH);
}
////////////////////////////////////////////////////////////////////////////////////////////
//init the servo motor
void ServoInit()
{
  pinMode(LP_SERVO,OUTPUT);
  digitalWrite(LP_SERVO,HIGH);
  pinMode(RP_SERVO,OUTPUT);
  digitalWrite(RP_SERVO,HIGH);
}
//control the servo,left is angel the eye_control servo on you leftsight ,while the right is your rightsight 
void ServoControl(int left,int right)
{
  int i=0;
  left=left*100/9+500;
  right=right*100/9+500;
  for (i=0;i<60;i++)
  { 
    digitalWrite(LP_SERVO,HIGH);
    delayMicroseconds(left);
    digitalWrite(LP_SERVO,LOW);
    digitalWrite(RP_SERVO,HIGH);
    delayMicroseconds(right);
    digitalWrite(RP_SERVO,LOW);
    delay(19);
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//init the LED control port
void LEDInit()
{
  pinMode(LP_LED,OUTPUT);
  digitalWrite(LP_LED,HIGH);
  pinMode(RP_LED,OUTPUT);
  digitalWrite(RP_LED,HIGH);
}
//shaking the LED on the eyes
void LEDShake()
{
  int i=0;
  for (i=0;i<2;i++)
  {
    digitalWrite(LP_LED,LOW);
    digitalWrite(RP_LED,LOW);
    delay(100);
    digitalWrite(LP_LED,HIGH);
    digitalWrite(RP_LED,HIGH);
    delay(500);
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////
//init the infrared control port
void InfInit()
{
  pinMode(P_INF,INPUT);
  digitalWrite(P_INF,HIGH);
}
//read the infrared data
int InfRead()
{
  return analogRead(P_INF);
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
void setup() {
  ServoInit();
  InfInit();
  LEDInit();
  MotorInit();
  Serial.begin(9600);
  ServoControl(80,35);
}

void loop() {
 static int state =0;
 int infR=InfRead();
 Serial.println(infR);
 switch(state)
 {
   case 0: MotorGo();break;
   case 1: MotorLeft();break;
   case 2: MotorRight();break;
   case 3: MotorBack();break;
   case 4: MotorStop();break;
   case 5: state=0;return;
   default: break;
 }
 if(infR<=600)
 {
   ServoControl(120,0);
   LEDShake();
   delay(1000);
   ServoControl(40,70);
   LEDShake();
   delay(1000);
   ServoControl(75,35);
   state++;
 }
 else delay(500);
}
