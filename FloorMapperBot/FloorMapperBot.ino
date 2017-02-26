#include <ArduinoJson.h>

int leftIR = A4;
int rightIR = A5;

int leftBummper = 6;
int rightBummper = 7;

int directionA = 12;
int directionB = 13;
int speedA = 3;
int speedB = 11;
int brakeA = 9;
int brakeB = 8;

//Driving values
double mapingSpeed = 0.8;
double distanceToMaintainFromWall = 50;
double wallFollowingLeeway = 10;

//Mapping values
double lastDistanceFromWall;
double sensorOffset = 8; //Distance from center of robot to sensor

int posX = 1000;
int posY = 1000;


int phase = 0; //The phase the room maping operation


//A grid which goes from -1000,
bool exploredArea[2000][2000];
bool wallLocations[2000][2000];


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(leftIR, INPUT);
  pinMode(rightIR, INPUT); 

  pinMode(leftBummper, INPUT);
  pinMode(rightBummper, INPUT);

  pinMode(directionA, OUTPUT);
  pinMode(directionB, OUTPUT);
  pinMode(speedA, OUTPUT);
  pinMode(speedB, OUTPUT);
  pinMode(brakeA, OUTPUT);
  pinMode(brakeB, OUTPUT); 

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(convertAnalogToCm(analogRead(leftIR)));
  Serial.print(",");
  Serial.print(convertAnalogToCm(analogRead(rightIR)));
  Serial.print(",");
  Serial.print(digitalRead(leftBummper));
  Serial.print(",");
  Serial.print(digitalRead(rightBummper));

}




double convertAnalogToCm (double raw) {
  float voltFromRaw = map(raw,0, 1023, 0,5000);
  double CM = 27.728*pow(voltFromRaw/1000.0,-1.2045);
  if(CM < 10) {
    CM = -1;
  } else if(CM >80) {
    CM = -2;
  }
  return CM;
}


//Driving Functions
//Tank Drive
void drive (double leftDrive, double rightDrive) {
  if(leftDrive > 0) {
    digitalWrite(directionA, HIGH);
    analogWrite(speedA, percentToAnalog(leftDrive));
  } else {
    digitalWrite(directionA, LOW);
    analogWrite(speedA, percentToAnalog(leftDrive * -1));
  }

  if(rightDrive > 0) {
    digitalWrite(directionB, HIGH);
    analogWrite(speedA, percentToAnalog(rightDrive));
  } else {
    digitalWrite(directionB, LOW);
    analogWrite(speedA, percentToAnalog(rightDrive * -1));
  }
  
  analogWrite(speedA, percentToAnalog(leftDrive));
  analogWrite(speedB, percentToAnalog(rightDrive));
  digitalWrite(brakeA, LOW);
  digitalWrite(brakeB, LOW);  
}

int percentToAnalog (double percent) {
  return (int)percent * 100 /255;
}


//Sensor Functions
double getDistanceRight() {
  return convertAnalogToCm(analogRead(rightIR));
}

double getDistanceLeft() {
  return convertAnalogToCm(analogRead(rightIR));
}

bool isHittingWall() {
  return digitalRead(leftBummper) == HIGH || digitalRead(rightBummper) == HIGH;
}


//Mapping functions
void addWallToMap(double distanceToWall, bool rightSide) {
  
}

void startUp() {
  //If we detect a wall to the right
  if(getDistanceRight() > 0) {
    //goto perimeter follow phase
    lastDistanceFromWall = getDistanceRight();
  } else {
    //rotate until wall on right
    drive(0.6, -0.6);
  }
}

void followWall() {
  //drive forward
  //if wall is increasing in distance turn right
  //if wall is decreasing indistance turn left
  
}






