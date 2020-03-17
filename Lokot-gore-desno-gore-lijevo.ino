/*
  servo ide na 9
  joysitck ide na A0 i A1

  gore desno gore lijevo otkljucava
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position
int sensorPinX = A0;    // select the input pin for the potentiometer
int sensorPinY = A1;    // select the input pin for the potentiometer

int sensorValueX = 0;  // variable to store the value coming from the sensor
int sensorValueY = 0;  // variable to store the value coming from the sensor

bool isread = false;

int step = 0; // dokle je doslo

void setup() {
 // initialize serial communications at 9600 bps:
  Serial.begin(9600);

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  // read the value from the sensor:
  sensorValueX = analogRead(sensorPinX);
  sensorValueY = analogRead(sensorPinY);

  if (isread && !(sensorValueX > 900 || sensorValueX < 100) && !(sensorValueY > 900 || sensorValueY < 100)) {
    isread= false;
  }

  else {
  
    if (sensorValueX > 900 && !isread) {
//      Serial.print("LIJEVO\n");
      step=read(4);
      isread = true;
    }
  
    if (sensorValueX < 100 && !isread) {
//      Serial.print("DESNO\n");
      step=read(2);
      isread = true;
    }
  
    if (sensorValueY > 900 && !isread) {
//      Serial.print("GORE\n");
      step=read(1);
      isread = true;
    }
  
    if (sensorValueY < 100 && !isread) {
//      Serial.print("DOLJE\n");
      step=read(3);
      isread = true;
    }

//    Serial.print(step);
//    Serial.print("\n");

    if (step == 4) unlock();
    else lock();
  }

  delay(10);

}

void lock() {
  myservo.write(180);
}

void unlock() {
  myservo.write(90);
}

int read(int x) {
  if (x==1 && step==0) return 1;
  if (x==2 && step==1) return 2;
  if (x==1 && step==2) return 3;
  if (x==4 && step==3) return 4;
  if (x==1) return 1;
  return 0; 
}
