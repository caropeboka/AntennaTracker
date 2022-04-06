#include <Servo.h>
// Include the Arduino Stepper Library
#include <Stepper.h>
Servo myservo;  // create servo object to control a servo

int angle =90;    // initial angle  for servo
int angleStep =5;

#define LEFT 12   // pin 12 is connected to left button
#define RIGHT  7  // pin 2 is connected to right button
#include <Robojax_L298N_DC_motor.h>
// motor 1 settings
#define IN1 2
#define IN2 4
#define ENA 3 // this pin must be PWM enabled pin



const int CCW = 2; // do not change
const int CW  = 1; // do not change
// Number of steps per output rotation
const int stepsPerRevolution = 20;

#define motor1 1 // do not change
#define motor2 2 // do not change

//*** Potentiometer and push button for motor 1 started 

const int motor1PushButtonCW = 8;
//const int motor1PushButtonStop = 9;
const int motor1PushButtonCCW = 10;
const int pot1Input = A0;
const int motor1Minimum =15;//30% is minimum for motor 1

// do not change below this line
int motor1Direction =CCW;//
int motor1StopState=HIGH;//Stope state of motor 1
int motor1Speed =0;// speed of motor 1
//*** Potentiometer and push button for motor 1 ended
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



// use the line below for single motor
Robojax_L298N_DC_motor motor(IN1, IN2, ENA, true);
// Create Instance of Stepper library
Stepper myStepper(stepsPerRevolution, 5, 6, 9, 11);
// use the line below for two motors
//Robojax_L298N_DC_motor motor(IN1, IN2, ENA, IN2, IN3, ENB, true);
void setup() {
    // set the speed at 60 rpm:
  myStepper.setSpeed(60);
  // Servo button demo by Robojax.com
  Serial.begin(9600);          //  setup serial
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(LEFT,INPUT_PULLUP); // assign pin 12 ass input for Left button
  pinMode(RIGHT,INPUT_PULLUP);// assing pin 2 as input for right button
  myservo.write(angle);// send servo to the middle at 90 degrees
 Serial.println("Robojax Servo Button ");
 motor.begin();

  //L298N DC Motor by Robojax.com
  pinMode(motor1PushButtonCW, INPUT_PULLUP);
  //pinMode(motor1PushButtonStop, INPUT_PULLUP);
  pinMode(motor1PushButtonCCW, INPUT_PULLUP);
}

void loop() {
  // Servo button demo by Robojax.com
  while(digitalRead(RIGHT) == LOW){
    Serial.println("counterclockwise");
    myStepper.step(-stepsPerRevolution);
    if (angle > 0 && angle <= 180) {
      angle = angle - angleStep;
       if(angle < 0){
        angle = 0;
       }else{
      myservo.write(angle); // move the servo to desired angle
      Serial.print("Moved to: ");
      Serial.print(angle);   // print the angle
      Serial.println(" degree");
       }
    }
    
  //delay(100); // waits for the servo to get there
  }// while
 // Servo button demo by Robojax.com

  while(digitalRead(LEFT) == LOW){
    Serial.println("clockwise");
    myStepper.step(stepsPerRevolution);
    // Servo button demo by Robojax.com
    if (angle >= 0 && angle <= 180) {
      angle = angle + angleStep;
      if(angle >180){
        angle =180;
       }else{
      myservo.write(angle); // move the servo to desired angle
      Serial.print("Moved to: ");
      Serial.print(angle);   // print the angle
      Serial.println(" degree");
       }
    }
    
 // delay(100); // waits for the servo to get there
  }// 

  updateState1();//read all push buttons
  int pot1Value= analogRead(pot1Input);// read potentiometer value

  motor1Speed = map(pot1Value, 0,1023, motor1Minimum, 100);// convert 0-5V to 0-100%


  if(motor1StopState ==HIGH)
  {
    motor.brake(1);
    //delay(1000);
    //motor.rotate(motor1, motor1Speed, motor1Direction);  
   
  }else{
    motor.rotate(motor1, motor1Speed, motor1Direction);
    delay(200);
      motor1StopState =HIGH;
  }
  //motor.demo(1);

  //motor.rotate(motor1, motor1Speed, CW);//run motor1 at 60% speed in CW direction
 delay(100);
}
void updateState1()
{

  if(digitalRead(motor1PushButtonCW) ==LOW && motor1StopState !=LOW){

   motor1Direction =CW;// CW button is pressed
   //delay(200);  
   motor1StopState =LOW;
   //delay(200);
  }  

  if(digitalRead(motor1PushButtonCCW) ==LOW && motor1StopState !=LOW)
  {
   motor1Direction =CCW;
   //delay(200);
   motor1StopState =LOW;
   //delay(200);   

  }  
  /*if(digitalRead(motor1PushButtonStop) ==LOW)
  {
   motor1StopState =HIGH;// STOP button is pressed 
  }*/  
}//updateState end
