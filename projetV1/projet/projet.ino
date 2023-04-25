#include "SPI.h"
#include "MFRC522.h"

#define RST_PIN 9 // RES pin
#define SS_PIN  10 // SDA (SS) pin

const int pingPin = 2; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 7; // Echo Pin of Ultrasonic Sensor
const int ledPin = 4;
const int motorPin = 3;
const int touchSensorPin = A0;

byte readCard[4];
String cardID = "80712FA5"; 
String tagID = "";

bool motorState = false;
unsigned long motorStartTime = 0;

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(4, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(pingPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(touchSensorPin, INPUT);
}

void loop() {
  checkRFID();
  checkUltrasonic();
  //checkTouchSensor();
}

void checkRFID() {
  while (getID()) {
    if (tagID == cardID) {
      Serial.println("Access Granted!");
      digitalWrite(4, LOW);
      digitalWrite(8, HIGH);
      motorState = true;
    }
    else {
      Serial.println("Access Denied!");
      digitalWrite(4, HIGH);
      delay(1000);
    }
    Serial.print("ID: ");
    Serial.println(tagID);
    digitalWrite(4, LOW);
  }
}

boolean getID() {
  if (! mfrc522.PICC_IsNewCardPresent()) {
    return false;
  }

  if (! mfrc522.PICC_ReadCardSerial()) {
    return false;
  }

  tagID = "";
  
  for (uint8_t i = 0; i < 4; i++) {
    tagID.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  tagID.toUpperCase();
  mfrc522.PICC_HaltA();
  return true;
}

void checkUltrasonic() {
  long duration, cm;
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  if (cm >= 10) {
    digitalWrite(ledPin, LOW);
    if (motorState) { // Only turn on the motor if motorState is true
      digitalWrite(motorPin, HIGH);
    }
  }
  else {
    digitalWrite(ledPin, HIGH);
    digitalWrite(8, LOW);
    motorState = false; // Set motor state to false (OFF)
    digitalWrite(motorPin, LOW);
  }
  delay(100);
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
