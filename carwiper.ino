#include <SoftwareSerial.h> // TX RX software library for bluetooth

#include <Servo.h> // servo library 
Servo myservo; // servo name

int bluetoothTx = 10; // bluetooth tx to 10 pin
int bluetoothRx = 11; // bluetooth rx to 11 pin
int angle =25;    // initial angle  for servo (beteen 1 and 179)
int angleStep =10;
const int minAngle = 0;
const int maxAngle = 180;


SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup() {
  myservo.attach(9); // attach servo signal wire to pin 9
  //Setup usb serial connection to computer
  Serial.begin(9600);
  //Setup Bluetooth serial connection to android
  bluetooth.begin(9600);
  myservo.write(0);
}

void loop() {
  //Read from bluetooth and write to usb serial
  if(bluetooth.available()>0 ) {
    int servopos = bluetooth.read(); // save the received number to servopos
    Serial.println(servopos); // serial print servopos current number received from bluetooth
    myservo.write(servopos); // roate the servo the angle received from the android app
  }  else if (bluetooth.read()=='x'){
  for (angle = 25; angle <= 180; angle += 5) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(angle);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (angle = 180; angle >= 25; angle -= 5) { // goes from 180 degrees to 0 degrees
    myservo.write(angle);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
}



