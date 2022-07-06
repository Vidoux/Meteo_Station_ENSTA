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

<img src="./shemas_elec_carte_capteur.svg" style=" max-width:700px" alt="schéma électrique de la carte capteur" >

Nous avons ensuite, toujours à l'aide de proteus, pu faire le routage de cette même carte. Après usinage de la carte 
et une scéance de soudure, nous obtenons la carte suivante:

<img src="./recto_carte_capteurs.jpeg" style=" max-width:400px"  >
<img src="./verso_carte_capteurs.jpeg" style=" max-width:400px"  >
