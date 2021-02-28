# Manual d'utilisation Station Meteo

### Introduction

Ce manuel représente un suivi étape par étape de l'installation et de l'utilisation de notre projet pour le cours de IoT.
Il représente aussi des spécifications sur la manière et la bonne procédure a suivre lors de l'utilisation

### Fonctionnement

L'objectif premier de la station météo est de diffuser des métriques comme Pression, Température, et humidité.

Les diffusions sont afficher a deux endroits
* Le LCD
* L'assistant virtual Home assistant

ses deux méthodes seront détaillés plus loin dans le document tant vis a vis l'utilisation, l'installation ainsi que les limitations.

Le fonctionnement général de la station météo est un système majoritairement automatisé. Donc facile d'utilisation. Lors du démarrage, la station météo tentera de se connecter
a un réseau Wifi. La station météo a été concu pour reconnaitre les réseaux qui ont déja été "découvert" et sont automatiquement enregistré sur l'appareil.

Lorsque la connexion sera effectué, la station aura accès a l'ensemble de ses fonctionnalités. La communication avec une entité distante est géré par un envoi de message via le reseau.

La station météo pourra alors commencer son travail. Le BME280 (Capteur sur le ESP32) pourra donc communiquer avec le réseau et envoyer les données.

* L'affichage LCD 
L'affichage LCD prend est a même la station météo. Il affiche la température l'humidité ainsi que la pression.
* L'affichage via Home assistant
l'affichage HA est un affichage distant. Il n'a pas a etre dépendant de la distance entre la station météo et le HA
Il affiche la même chose que l'Affichage LCD et le style d'affichage peut être modifier selon ses préférences/besoins.

### Spécificité

**NB: L'installation et la configuration étape par étape sera effectuer dans la prochaine section.** 

L'affichage est ici géré par Home assistant  https://www.home-assistant.io/docs/
Le hosting de Home assistant est fait via une Machine virtuelle de type virtualBox https://www.virtualbox.org/
L'envoi de message est communiqué par un Broker: MQTT dans notre cas. https://www.home-assistant.io/docs/mqtt/discovery/

### Installation & Configuration


#### Etape 1 : Installation de HomeAssistant

Télécharger VirtualBox et HomeAssistant (voir lien plus haut).

HomeAssistant est une image de Virtualbox elle doit donc être utiliser dans un Virtualisateur de machine.

**NB: nous utilisons VirtualBox. Cependant, d'autre virtualisateur peuvent être utilisé. Il faut donc choisir la bonne image dépendant du virtualisateur**

![VirtualBox](/Image/VirtualBox.png)

Pour monter l'image que vous venez de télécharger: Selectionner dans la barre de tâches : Machine
Dans le menu Déroulant sélectionné New et suivez les instructions.

![HomeAssistant](/Image/HomeAssistant.png)

lorsque l'image est monté,  Aller dans configuration et selectionné l'onglet : Network

Dans Network il est très important que le mode d'accès réseau soit : Bridged Adapter.


![HomeAssistant2](/Image/HomeAssistant2.png)

Par la suite, Appuyer sur Start et connectez-vous avec le login : root.

Le home assistant afficheras alors les informations systeme. 
Prenez en note l'adresse IPV4 (nous en aurons besoin plus tard).

![HomeassistantCLI](/Image/HomeAssistantCLI.png)


#### Etape 2 : Réglage de l'interface de Home Assistant

Par la suite, allez dans votre fureteur préféré et entrez l'Adresse que vous venez de prendre en note (soit le ipv4) suivi du port par default qui est 8123
donc l'adresse devrait ressembler a celle-ci (inscrire adresse)

**NB: à la première connexion l'interface vous demandera de crée un utilisateur avec un mot de passe. Il est important de saisir quelque chose qui sera facilement accessible par vous. Nous en auront besoin plus tard lors de la connexion a mqtt.** 

![Apercu](/Image/Apercu.png)

Dans cette partie, nous allons ajouter les composantes nécessaires au fonctionnement de l'échange de message.
Il existe de nombreux "plugin" pour Home assistant. Par contre, deux plugin nous intéresse particulièrement : Mosquito Broker et File Editor.

![Plugin](/Image/Plugins.png)

Le File Editor sert a configurer les settings et les bons status pour avoir accès au données du ESP32.

#### Etape 3 : Configuration des routes 

Le File Editor sert a configurer les settings et les bons status pour avoir accès au données du ESP32.

Dans le File Editor, Selectionné OPEN WEB UI.

Vous aurez donc accès a un Arbre de fichier. Le fichier qui nous interesse est le /config/configuration.yaml

Et vous aurez simplement à ajouter ses lignes de codes a la fin du fichier.

![Code](/Image/Code.png)

Il faut maintenant ajouter les jauges qui vont finalement afficher les résultats de la station Météo

**NB :  Il existe plusieurs thèmes et style. Donc, a vous de choisir lequel correspond le mieux a vos besoins.**

Voici comment rentrer les jauges.

Les jauges sont choisis dans les cartes. Lors de l'ajout du code nous avons accès au différente entité que nous avons ajouté précédement dans le code.
Si vous souhaitez appliquer des modifications ou ajouter des entités vous pouvez simplement les rajouter dans le code.

![Jauge](/Image/Jauge.png)