
// C++ code
//pin numbers
const int en12 = 11;
const int en34 = 6;
const int lFor = 12;
const int lBack = 13;
const int rBack = 7;
const int rFor = 8;
const int leftTrig = 4;
const int leftEcho = 5;
const int frontTrig = 10;
const int frontEcho = 9;
const int rightTrig = 3;
const int rightEcho = 2;
const int start = A0;
const int reset = A5;
bool startPress = false;

int delayTime = 2000;
int speed = 255;
int turnSpeed = 150;
int turnThresh = 5;


void setup()
{
  Serial.begin(9600);
  //pin assignments
  pinMode(en12, OUTPUT);
  pinMode(en34, OUTPUT);
  pinMode(lFor, OUTPUT);
  pinMode(lBack, OUTPUT);
  pinMode(rFor, OUTPUT);
  pinMode(rBack, OUTPUT);
  pinMode(leftTrig, OUTPUT);
  pinMode(leftEcho, INPUT);
  pinMode(frontTrig, OUTPUT);
  pinMode(frontEcho, INPUT);
  pinMode(rightTrig, OUTPUT);
  pinMode(rightEcho, INPUT);
  pinMode(start, INPUT);
  pinMode(reset, INPUT);
  
}

void loop()
{
  //inititalize the distance variables
  Serial.println(0);
  long forwardDistance;
  long rightDistance;
  long leftDistance;
  //start moving when the button is pressed
  if (digitalRead(start) == HIGH){
    startPress = true;
  }
  //otherwise, do not move
  else {
    digitalWrite(en12, LOW);
    digitalWrite(en34, LOW);
  }
  while(startPress) {
    //after the start button has been pressed, calculate the distance from the car to the wall
  	forwardDistance = frontScan();
  	rightDistance = rightScan();
  	leftDistance = leftScan();
    //move forward
    digitalWrite(en12, HIGH);
    digitalWrite(en34, HIGH);
    
    analogWrite(lFor, 255);
    analogWrite(lBack, 0);
    analogWrite(rFor, 130);
    analogWrite(rBack, 0);
    
    Serial.println("front");
    Serial.println(forwardDistance);
    Serial.println("right");
    Serial.println(rightDistance);
    Serial.println("left");
    Serial.println(leftDistance);
    if (rightDistance < turnThresh) {
      Serial.println("turn left");
      turnLeft();
    }
    if (leftDistance < turnThresh) {
      Serial.println("turn right");
      turnRight();
    }
    if (forwardDistance < turnThresh) {
    	if (rightDistance < leftDistance) {
          Serial.println("turn left");
      		turnLeft();
          
    	}
    	else {
          Serial.println("turn right");
      		turnRight();
          
    	}
  	}
  }
  if (digitalRead(reset) == HIGH) {
    startPress = false;
  }
}

//turns the car right for duration time
void turnRight() 
{
  while((frontScan()<turnThresh)||(leftScan()<turnThresh)) {
    analogWrite(lFor, turnSpeed);
    analogWrite(lBack, LOW);
    analogWrite(rFor, LOW);
    analogWrite(rBack,turnSpeed);
  }
  
  
}

//turns the car left for duration time
void turnLeft() 
{
  
  while((frontScan()<turnThresh)||(rightScan()<turnThresh)) {
    analogWrite(lFor, LOW);
    analogWrite(lBack, turnSpeed);
    analogWrite(rFor, turnSpeed);
    analogWrite(rBack, LOW);
  }

}

//checks distance from car to wall in front
long frontScan()
{
  long duration, inches;
  digitalWrite(frontTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(frontTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(frontTrig, LOW);
  duration = pulseIn(frontEcho, HIGH);
  inches = duration / 74 / 2;
  return inches;
  
}

//checks distance from car to wall to the right
long rightScan()
{
  long duration, inches;
  digitalWrite(rightTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(rightTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(rightTrig, LOW);
  duration = pulseIn(rightEcho, HIGH);
  inches = duration / 74 / 2;
  return inches;
  Serial.println(inches);
}

//checks distance from car to wall to the left
long leftScan()
{
  long duration, inches;
  digitalWrite(leftTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(leftTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(leftTrig, LOW);
  duration = pulseIn(leftEcho, HIGH);
  inches = duration / 74 / 2;
  return inches;
}
