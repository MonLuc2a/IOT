// Définir les broches pour le lecteur RFID
#define RST_PIN 9
#define SS_PIN  10

// Définir les broches pour les autres composants
const int pingPin = 2;        // Trigger Pin du capteur à ultrasons
const int echoPin = 7;        // Echo Pin du capteur à ultrasons
const int ledPin = 4;
const int motorPin = 3;
const int touchSensorPin = A0;

int eepromAddress = 0;        // Adresse pour l'enregistrement dans l'EEPROM

// Variables pour le lecteur RFID
byte readCard[4];
String cardID = "85C85183";
String tagID = "";

bool motorState = false;      // État du moteur (activé ou désactivé)

MFRC522 mfrc522(SS_PIN, RST_PIN);

// Enumération pour les différents états du programme
enum State {
  CHECK_RFID,
  CHECK_ULTRASONIC,
  CHECK_TOUCH_SENSOR,
  CHECK_USER_INPUT
};

State currentState;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();         // Initialiser le lecteur RFID
  pinMode(4, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(pingPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(touchSensorPin, INPUT);

  setTimeAndDate();           // Définir l'heure et la date

  currentState = CHECK_USER_INPUT;  
}

void loop() {
  // Exécuter la fonction correspondant à l'état actuel
  switch (currentState) {
    case CHECK_RFID:
      checkRFID();
      currentState = CHECK_ULTRASONIC;
      break;
    case CHECK_ULTRASONIC:
      checkUltrasonic();
      currentState = CHECK_TOUCH_SENSOR;
      break;
    case CHECK_TOUCH_SENSOR:
      checkTouchSensor();
      currentState = CHECK_RFID;
      break;
    case CHECK_USER_INPUT:
      checkUserInput();
      currentState = CHECK_RFID;
      break;
  }
}

// Vérifier si une carte RFID est détectée et si l'ID correspond
void checkRFID() {
  while (getID()) {
    if (tagID == cardID) {
      Serial.println("Access Granted!");
      digitalClockDisplay("Access Granted");
      digitalWrite(4, LOW);
      digitalWrite(8, HIGH);
      motorState = true;
    } else {
      Serial.println("Access Denied!");
      digitalClockDisplay("Access Denied");
      digitalWrite(4, HIGH);
      delay(1000);
    }

    Serial.print("ID: ");
    Serial.println(tagID);
    digitalWrite(4, LOW);
  }
}

// Lire l'ID de la carte RFID
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

// Vérifier la distance mesurée par le capteur à ultrasons
void checkUltrasonic() {
  long duration, cm;
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  // Si la distance est supérieure à 10 cm, allumer la LED et activer le moteur si nécessaire
  if (cm >= 10) {
    digitalWrite(ledPin, LOW);
    if (motorState) { 
      digitalWrite(motorPin, HIGH);
    }
  }
  else {
    digitalWrite(ledPin, HIGH);
    digitalWrite(8, LOW);
    motorState = false; // Désactiver le moteur
    digitalWrite(motorPin, LOW);
  }
  delay(100);
}

// Convertir la durée en microsecondes en centimètres
long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

// Vérifier l'état du capteur tactile
void checkTouchSensor() {
  int touchValue = analogRead(touchSensorPin);
  if (touchValue > 512) { // Seuil arbitraire, à ajuster en fonction de vos besoins
    // Faites quelque chose lorsque le capteur tactile est activé
    Serial.println("Touch Sensor Activated");
    // Ajoutez ici les actions que vous souhaitez effectuer lorsque le capteur tactile est activé
  }
}

// Écrire les données dans l'EEPROM
void writeToEEPROM(String data) {
  for (uint16_t i = 0; i < data.length(); i++) {
    EEPROM.write(eepromAddress, data[i]);
    eepromAddress++;
  }
  EEPROM.write(eepromAddress, '\n'); // Ajouter un saut de ligne pour séparer les entrées
  eepromAddress++;
}

// Afficher l'horodatage et le statut d'accès
void digitalClockDisplay(String access_status) {
  time_t currentTime = now(); // Obtenir le temps actuel
  String log_entry = access_status + " Time: ";
  log_entry += String(hour(currentTime)) + ":";
  log_entry += String(minute(currentTime)) + ":";
  log_entry += String(second(currentTime)) + " ";
  log_entry += String(day(currentTime)) + "/";
  log_entry += String(month(currentTime)) + "/";
  log_entry += String(year(currentTime));
  
  Serial.println(log_entry);
  writeToEEPROM(log_entry);
}

// Définir l'heure et la date
void setTimeAndDate() {
  // Définissez ici l'heure et la date actuelles
  setTime(14, 30, 0, 24, 4, 2023);
}

// Vérifier les entrées de l'utilisateur
void checkUserInput() {
  if (Serial.available()) {
    char userInput = Serial.read();
    if (userInput == '1') {
      displayAccessHistory();
    } else if (userInput == '2') {
      Serial.println("Quitting...");
    }
  }
}

void displayAccessHistory() {
  Serial.println("Access history:");
  for (int i = 0; i < eepromAddress; i++) {
    char logChar = EEPROM.read(i);
    if (logChar != '\n') {
      Serial.print(logChar);
    } else {
      Serial.println();
    }
  }
  Serial.println("End of access history.");
}

