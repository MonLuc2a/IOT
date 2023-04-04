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

Ouverture contrôlée avec contrôle d'accès :

Badge RFID
Klaxon
Approche de la bonne voiture (détecteur de proximité)
Télécommande
Mélange de ces méthodes
Sécurité anti-vol :

Détecter des comportements anormaux en face de la porte (mouvements suspects, temps d'attente prolongé)
Détection d'anomalies :

La porte se ferme sur quelqu'un (capteur de force ou détecteur de proximité)
La porte est coincée et n'arrive pas à s'ouvrir (capteur de force ou détecteur de proximité)
Le moteur est en panne et rien ne se passe (mesure de la consommation électrique)
La porte s'est-elle fermée jusqu'au bout ? (capteur de force)

Interface homme-machine (IHM) :

Indicateurs lumineux (LEDs) pour signaler l'état du système
Signaux sonores (haut-parleur ou buzzer) pour avertir les utilisateurs
Envoi de notifications :

Notifications datées envoyées sur le réseau
