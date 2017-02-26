#include <ArduinoJson.h>

int leftIR = A4;
int rightIR = A5;

int directionA = 12;
int directionB = 13;
int speedA = 3;
int speedB = 11;
int brakeA = 9;
int brakeB = 8;


int phase = 0; //The phase the room maping operation


//A grid which goes from -1000,
bool exploredArea[2000][2000];
bool wallLocations[2000][2000];


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(leftIR, INPUT);
  pinMode(rightIR, INPUT); 


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
  Serial.print(analogRead(frontTrip));
  Serial.print(",");
  Serial.println(analogRead(downTrip));


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
void tankDrive (double leftDrive, double rightDrive) {
  if(leftDrive > 0) {
    digitalWrite(directionA, HIGH);
    analogWrite(speedA, percentToAnalog(leftDrive);
  } else {
    digitalWrite(directionA, LOW);
    analogWrite(speedA, percentToAnalog(leftDrive * -1);
  }

  if(rightDrive > 0) {
    digitalWrite(directionB, HIGH);
    analogWrite(speedA, percentToAnalog(rightDrive);
  } else {
    digitalWrite(directionB, LOW);
    analogWrite(speedA, percentToAnalog(rightDrive * -1);
  }
  
  analogWrite(speedA, percentToAnalog(leftDrive);
  analogWrite(speedB, percentToAnalog(rightDrive);
  digitalWrite(brakeA, LOW);
  digitalWrite(brakeB, LOW);  
}

int percentToAnalog (double percent) {
  return (int)percent/255;
}

//Sensor Functions

double getDistanceRight() {
  return convertAnalogToCm(analogRead(rightIR);
}

double getDistanceLeft() {
  return convertAnalogToCm(analogRead(rightIR);
}

void startUp() {
  
}




