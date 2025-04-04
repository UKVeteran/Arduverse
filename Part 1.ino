 * After running the code, smart car will go forward 2 seconds, then go backward 2
 * seconds, then left turn for 2 seconds then right turn for 2 seconds then stop. 
 * 
 */
#define speedPinR 5    //  RIGHT PWM pin connect MODEL-X ENA
#define RightMotorDirPin1  7    //Right Motor direction pin 1 to MODEL-X IN1 
#define RightMotorDirPin2  8    //Right Motor direction pin 2 to MODEL-X IN2
#define speedPinL 6    // Left PWM pin connect MODEL-X ENB
#define LeftMotorDirPin1  9    //Left Motor direction pin 1 to MODEL-X IN3 
#define LeftMotorDirPin2  10   //Left Motor direction pin 1 to MODEL-X IN4 


/*motor control*/
void go_Advance(void)  //Forward
{
  digitalWrite(RightMotorDirPin1, LOW);
  digitalWrite(RightMotorDirPin2,HIGH);
  digitalWrite(LeftMotorDirPin1,LOW);
  digitalWrite(LeftMotorDirPin2,HIGH);
  analogWrite(speedPinL,100);
  analogWrite(speedPinR,100);
}
void go_Left(int t=0)  //Turn left
{
  digitalWrite(RightMotorDirPin1,LOW );
  digitalWrite(RightMotorDirPin2,HIGH);
  digitalWrite(LeftMotorDirPin1,HIGH);
  digitalWrite(LeftMotorDirPin2,LOW);
  analogWrite(speedPinL,0);
  analogWrite(speedPinR,100);
  delay(t);
}
void go_Right(int t=0)  //Turn right
{
  digitalWrite(RightMotorDirPin1,HIGH);
  digitalWrite(RightMotorDirPin2,LOW);
  digitalWrite(LeftMotorDirPin1,LOW);
  digitalWrite(LeftMotorDirPin2,HIGH);
  analogWrite(speedPinL,100);
  analogWrite(speedPinR,0);
  delay(t);
}
void go_Back(int t=0)  //Reverse
{
  digitalWrite(RightMotorDirPin1,HIGH);
  digitalWrite(RightMotorDirPin2,LOW);
  digitalWrite(LeftMotorDirPin1,HIGH);
  digitalWrite(LeftMotorDirPin2,LOW);
  analogWrite(speedPinL,100);
  analogWrite(speedPinR,100);
  delay(t);
}
void stop_Stop()    //Stop
{
  digitalWrite(RightMotorDirPin1, LOW);
  digitalWrite(RightMotorDirPin2,LOW);
  digitalWrite(LeftMotorDirPin1,LOW);
  digitalWrite(LeftMotorDirPin2,LOW);
}
/*set motor speed */
void set_Motorspeed(int speed_L,int speed_R)
{
  analogWrite(speedPinL,speed_L); 
  analogWrite(speedPinR,speed_R);   
}

//Pins initialize
void init_GPIO()
{
  pinMode(RightMotorDirPin1, OUTPUT); 
  pinMode(RightMotorDirPin2, OUTPUT); 
  pinMode(speedPinL, OUTPUT);  
 
  pinMode(LeftMotorDirPin1, OUTPUT);
  pinMode(LeftMotorDirPin2, OUTPUT); 
  pinMode(speedPinR, OUTPUT); 
  stop_Stop();
}

void setup()
{
  init_GPIO();
  go_Advance();//Forward
 
  delay(1000);
  
  go_Back();//Reverse
 
  delay(1000);
  
  go_Left();//Turn left
 
  delay(1000);
  
  go_Right();//Turn right
 
  delay(1000);
  
  stop_Stop();//Stop

}

void loop(){
}
