int leftIR = A4;
int rightIR = A2;
int frontTrip = 2;
int downTrip = 3;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(leftIR, INPUT);
  pinMode(rightIR, INPUT); 
  pinMode(frontTrip, INPUT);
  pinMode(downTrip, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(convertAnalogToCm(analogRead(leftIR)));
  Serial.print(",");
  Serial.print(convertAnalogToCm(analogRead(rightIR)));
  Serial.print(",");
  Serial.print(digitalRead(frontTrip));
  Serial.print(",");
  Serial.println(digitalRead(downTrip));
  delay(250);
}

double convertAnalogToCm (double raw) {

  float voltFromRaw = map(raw,0, 1023, 0,5000);
  double CM = 27.728*pow(voltFromRaw/1000.0,-1.2045);
  /*if(CM < 10) {
    CM = -1;
  } else if(CM >80) {
    CM = -2;
  }*/

  return CM;

}

