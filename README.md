# IOT
Projet Arduino 1 : Porte de garage sécurisée

Description du projet :
Ce projet consiste à créer un système de contrôle d'accès pour une porte de garage sécurisée, en utilisant une carte Arduino. Le système doit permettre l'ouverture et la fermeture de la porte via différents modes d'authentification, tout en assurant la sécurité des biens et des personnes. Il doit également informer les utilisateurs de l'état du système et envoyer des notifications en cas d'événements importants.

Matériel requis :

Carte Arduino (Uno, Mega, etc.)
Module RFID (RC522)
Détecteur de proximité (HC-SR04)
Capteur de force (pour détecter la fermeture complète de la porte)
Moteur pas-à-pas ou moteur à courant continu avec contrôleur
Module relais pour contrôler le moteur
Sirène ou klaxon
LEDs pour indicateurs lumineux
Haut-parleur ou buzzer pour signaux sonores
Module Wi-Fi ou Ethernet (ESP8266, ESP32 ou W5100)
Alimentation électrique
Télécommande ou application pour smartphone
Fils de connexion et breadboard
Fonctionnalités :

Plan :

Contrôle d'accès avec badge RFID
Utilisez un lecteur RFID comme le module MFRC522 et une carte RFID compatible.
Installez la bibliothèque MFRC522 pour Arduino.
Écrivez un code pour lire l'UID (identifiant unique) des cartes RFID.

Klaxon
Utilisez un capteur de son pour détecter le klaxon de la voiture.
Écrivez un code pour détecter le niveau sonore et déclencher l'ouverture de la porte lorsque le klaxon est détecté.

Approche de la bonne voiture
Utilisez un module Bluetooth (par exemple, HC-05 ou HC-06) pour détecter la présence de la voiture.
Écrivez un code pour établir une connexion Bluetooth entre la voiture et le système Arduino et déclencher l'ouverture de la porte.

Télécommande
Utilisez un récepteur infrarouge et une télécommande compatible.
Installez la bibliothèque IRremote pour Arduino.
Écrivez un code pour recevoir des signaux infrarouges et déclencher l'ouverture de la porte.

Sécurité anti-vol
Utilisez un capteur PIR (détecteur de mouvement) pour détecter des mouvements suspects près de la porte.
Écrivez un code pour déclencher une alarme ou envoyer une notification en cas de mouvement détecté.

Détection d'anomalies
Utilisez des capteurs de fin de course ou des capteurs à ultrasons pour détecter la position de la porte.
Écrivez un code pour vérifier si la porte est complètement ouverte, fermée, bloquée ou si le moteur est en panne.

Interface utilisateur
Utilisez des LEDs, des buzzers ou un écran LCD pour afficher l'état du système.
Écrivez un code pour mettre à jour l'affichage en fonction de l'état du système.
