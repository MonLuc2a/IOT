# Porte de garage sécurisée - Projet Arduino 1

Ce projet consiste en la création d'un système de contrôle d'accès pour une porte de garage sécurisée en utilisant une carte Arduino. Le système permet l'ouverture et la fermeture de la porte via différents modes d'authentification, tout en assurant la sécurité des biens et des personnes. De plus, il informe les utilisateurs de l'état du système et envoie des notifications en cas d'événements importants.

## Fonctionnalités

Le projet utilise un ensemble de capteurs et d'actuateurs pour créer un système de contrôle d'accès flexible et polyvalent. Les principales fonctionnalités du système comprennent :

- Enregistrement des informations d'accès dans la mémoire vive (EEPROM)
- Contrôle d'un élément motorisé (ex. verrou électrique)
- Mécanisme d'autocontrôle basé sur un capteur à ultrasons
- Détection de toucher tactile avec un capteur capacitif
- Interaction avec un ordinateur pour visualiser l'historique des accès

## Matériel requis

- Arduino Uno
- Capteur à ultrasons HC-SR04
- Lecteur RFID MFRC522
- Moteur
- Résistances
- Fils de connexion

## Broches utilisées

- Broche 2: Trigger Pin du capteur à ultrasons
- Broche 3: Broche de commande du moteur
- Broche 4: Broche LED
- Broche 5: Bouton d'arrêt du moteur
- Broche 7: Echo Pin du capteur à ultrasons
- Broche 8: LED pour indiquer l'état du verrou
- Broche 9: RST_PIN pour le lecteur RFID
- Broche 10: SS_PIN pour le lecteur RFID

## Fonctionnement

1. Le système vérifie si une carte RFID est détectée et si l'ID correspond à l'ID autorisé.
2. Si la carte RFID est autorisée, le système active la LED et le moteur pendant 5 secondes ou jusqu'à ce que le bouton d'arrêt soit appuyé.
3. Le capteur à ultrasons mesure la distance et, si la distance est supérieure à 10 cm, la LED s'éteint et le moteur s'arrête si nécessaire.
4. Les données d'accès, y compris les horodatages, sont enregistrées dans l'EEPROM de l'Arduino.

## Fonctions principales

- `checkRFID()`: Vérifie si une carte RFID est détectée et si l'ID correspond.
- `getID()`: Lit l'ID de la carte RFID.
- `checkUltrasonic()`: Vérifie la distance mesurée par le capteur à ultrasons.
- `microsecondsToCentimeters(long microseconds)`: Convertit la durée en microsecondes en centimètres.
- `writeToEEPROM(String data)`: Écrit les données dans l'EEPROM.
- `digitalClockDisplay(String access_status)`: Affiche l'horodatage et le statut d'accès.
- `setTimeAndDate()`: Définit l'heure et la date.
- `checkUserInput()`: Vérifie les entrées de l'utilisateur.
- `displayAccessHistory()`: Affiche l'historique d'accès stocké dans l'EEPROM.
- `StopMotor()`: Arrête le moteur lorsque le bouton d'arrêt est appuyé ou après 5 secondes.

## Utilisation

1. Téléversez le code sur l'Arduino.
2. Connectez tous les composants selon les broches mentionnées ci-dessus.
3. Ouvrez le moniteur série et réglez la vitesse de transmission à 9600 bauds.
4. Lorsqu'une carte RFID autorisée est détectée, le système affiche "Access Granted"

## Shéma

![shéma](Untitled_Workspace.png)
