# Weather_Station_ENSTA_B

Le projet est une station météo connectée.
Nous avons réalisé deux cartes électroniques qui constituent la station météo.

## Introduction

- Carte Capteur :

Cette carte a pour rôle d'être positionnée en extérieur, elle prend les mesures d'hygrométrie, de température et de 
pression atmosphérique. Elle transmet toutes ces données à la seconde carte, la carte serveur, via un module de 
transmission LoRa.   

- Carte Serveur

Cette carte réceptionne tout d'abord les données de la carte capteur. Elle est également équipée d'un capteur de 
température et d'hygrométrie pour avoir ces données sur l'intérieur du local. Cette carte a également pour objectif 
de créer un serveur web sur un réseau local afin de publier les résultats des capteurs sur une page web.

Nous n'avons pas eu à réalisée cette carte, celle-ci a été conçue par les enseignants du module et nous a été livrée 
déjà soudée, prête à être utilisée.

## Schéma électrique et routage de la carte Capteur

À partir des spécifications techniques et des datasheet des composants, nous avons pu, dans un premier temps, 
réaliser le schéma électrique de la carte capteur.


![schemas_electrique_carte_capteur](./shemas_elec_carte_capteur.svg)

Nous avons ensuite, toujours à l'aide de proteus, pu faire le routage de cette même carte. Après usinage de la carte 
et une séance de soudure, nous obtenons la carte suivante :

![recto_carte_capteurs](./recto_carte_capteurs.jpeg)
![verso_carte_capteurs](./verso_carte_capteurs.jpeg)

## Programmation du Serveur Web

La carte Serveur est équipée d'un microcontroller ESP32 qui est équipée d'une puce wifi.
On peut ainsi connecter notre carte sur un réseau wifi existant afin d'en faire un serveur web. En connaissant 
l'adresse ip de la carte sur le réseau, n'importe qui connecté sur le réseau peut alors se connecter sur la page 
hébergée par l'Arduino via son adresse IP. Si l'IP de la carte est "192.168.0.47" par exemple, on peut accéder à la 
page en entrant "http://192.168.0.47" dans la barre de recherche d'un navigateur.

Pour programmer le serveur, nous nous sommes inspirés de cette page internet :<br>
[https://tommydesrochers.com/controlez-votre-esp32-a-partir-dune-page-web-version-facile-esp32-ep3/](https://tommydesrochers.com/controlez-votre-esp32-a-partir-dune-page-web-version-facile-esp32-ep3/)

Le principe est d'abord de se connecter à un réseau wifi, pour cela on initialise le ssid et le mot de passe du 
réseau souhaité :

```C++
const char *ssid = "groupe8";
const char *password = "groupe8pswd";
```

De plus, la bibliothèque ```#include <WebServer.h>``` simplifie la création d'un serveur web.
La programmation de celui-ci est alors asser simple, on peut donc afficher les valeurs de tous les différents 
capteurs de toute la station. Le code de la page HTML hébergée par le serveur est mis à jour régulièrement (toutes 
les 4s) avec les nouvelles valeurs des capteurs.

## Récupération des données capteur

Pour récupérer les données capteurs, l'idée n'est pas d'utiliser les bibliothèques des fabricants, mais d'utiliser 
directement la communication en I2C et la manipulation des registres pour lire les valeurs de chaque capteur.
Nous avons ainsi essayé de regrouper toutes les fonctions de récupération des données des capteurs dans des 
librairies, chacune dédiées à un constructeur.
Pour cela nous sommes parties de la documentation arduino : https://docs.arduino.cc/learn/contributions/arduino-creating-library-guide

Nous avons donc deux librairies : Une pour les fonctions liées au capteur de pression BMP180 et l'autre dédiée au 
capteur SHT21. Afin d'utiliser ces deux librairies, les dossiers de celles ci doivent-être copiées dans le dossier 
"libraries" d'Arduino avant la compilation et le téléversement.
Chaque fonction des librairies est commentée. Ci-dessous un résumé des fonctions utiles pour le programme final:

BMP180:
```C++
int32_t getPressure();
void begin();
```
SHT21:
```C++
//TODO
```
    





