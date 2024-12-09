// C++ code
//pin numbers
const int en12 = 13;
const int en34 = 12;
const int lFor = 10;
const int lBack = 11;
const int rBack = 6;
const int rFor = 9;
const int leftTrig = 8;
const int leftEcho = 7;
const int frontTrig = 5;
const int frontEcho = 4;
const int rightTrig = 3;
const int rightEcho = 2;
const int start = A0;
const int reset = A5;
bool startPress = false;

int delayTime = 2000;
int speed = 150;
int turnSpeed = 150;
int turnTime = 2000;
int turnThresh = 6;


void setup()
{
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
  Serial.begin(9600);
}

void loop()
{
  long forwardDistance;
  long rightDistance;
  long leftDistance;
  if (digitalRead(start) == HIGH){
    startPress = true;
  }
  else {
    digitalWrite(en12, LOW);
    digitalWrite(en34, LOW);
  }
  Serial.println(digitalRead(start));
  while(startPress) {
  	forwardDistance = frontScan();
  	rightDistance = rightScan();
  	leftDistance = leftScan();
    digitalWrite(en12, HIGH);
    digitalWrite(en34, HIGH);
    analogWrite(lFor, speed);
    analogWrite(lBack, 0);
    analogWrite(rFor, .929*speed);
    analogWrite(rBack, 0);
  	/*if (forwardDistance < turnThresh) {
    	if (rightDistance < leftDistance) {
      		turnLeft(turnTime);
    	}
    	else {
      		turnRight(turnTime);
    	}
  	}*/
  }
  if (digitalRead(reset) == HIGH) {
    startPress = false;
  }
}

//turns the car right for duration time
void turnRight(int time) 
{
  analogWrite(lFor, 0);
  analogWrite(lBack, turnSpeed);
  analogWrite(lFor, turnSpeed);
  analogWrite(lBack, 0);
  
  delay(time);
}

//turns the car left for duration time
void turnLeft(int time) 
{
  analogWrite(lFor, turnSpeed);
  analogWrite(lBack, 0);
  analogWrite(lFor, 0);
  analogWrite(lBack, turnSpeed);
  
  delay(time);
}

//checks to see if there is a wall close in front
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

//checks to see if there is a wall close to the right
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
}

//checks to see if there is a wall close to the left
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