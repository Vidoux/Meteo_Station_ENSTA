# Weather_Station_ENSTA_B

Le projet est une station météo connectée.
Nous avons réalisé deux cartes électroniques qui constituent la station météo.

## Introduction

    Carte Capteur :

Cette carte a pour rôle d'être positionnée en extérieur, elle prend les mesures d'hygrométrie, de température et de 
pression atmosphérique. Elle transmet toutes ces données à la seconde carte, la carte serveur, via un module de 
transmission LoRa.   

    Carte Serveur

Cette carte réceptionne tout d'abord les données de la carte capteur. Elle est également équipée d'un capteur de 
température et d'hygrométrie pour avoir ces données sur l'intérieur du local. Cette carte a également pour objectif 
de créer un serveur web sur un réseau local afin de publier les résultats des capteurs sur une page web.


