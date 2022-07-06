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

## Schéma électrique et routage de la carte Capteur

A partir des spécifications techniques et des datasheet des composants nous avons pu, dans un premier temps, 
réaliser le schéma électrique de la carte capteur.


![schemas_electrique_carte_capteur](./shemas_elec_carte_capteur.svg)

Nous avons ensuite, toujours à l'aide de proteus, pu faire le routage de cette même carte. Après usinage de la carte 
et une scéance de soudure, nous obtenons la carte suivante:

![recto_carte_capteurs](./recto_carte_capteurs.jpeg)
![verso_carte_capteurs](./verso_carte_capteurs.jpeg)

