# ProtoProc #

## Equipe: ##
- Dédé Belnet
- Raoul Bernard
- Pierre Bourré
- Martial Costantini
- Pierre-François Gimenez

# Projet: #
Concevoir et construire une console de jeu avec des portes logiques.

## Etapes ##
- concevoir un processeur RISC
- le réaliser électroniquement
- écrire un assembleur
- écrire un compilateur (?)
- écrire un jeu
- intégrer des éléments extérieurs (écran, manette)
- jouer

## Constituant d'un processeur ##
- ALU (unité arithmétique et logique)
- Register file
- Séquenceur
- Horloge
- Contrôleur mémoire
- Contrôleur d'interruption
- MMU

A se répartir.

## Détection d'erreur ##
- Le code de Berger est un exemple de code utilisable. Voir dans "download" pour plus d'infos.
- Que faire en cas de détection d'erreur? Lever une interruption?

## Eléments à choisir ##
- Combien de bits? (bits effectivement utilisés + bits de redondance)
- Quels adressages disponibles?
- Jeu d'instruction? (voir plus bas)
- Mode idle?
- Timer? Compteur?

### Proposition ###
- 3 bits (données) + 2 bits (contrôle par code de Berger)
- 8 registres accessibles: ACC1, ACC2, SP (accessible?), flags (zero, sign, carry) (accessible?), index high, index low, E/S 1 (ou seulement entrée), E/S 2 (ou seulement sortie). Registre nul? (utile pour comparaison à zéro et initialisation)
- adressage sur 15 bits immédiats (cf largeur du bus de la mémoire ram de RS)
- adresse sur 15 bits immédiats + 6 bits provenant des deux registres d'index (une adresse du genre 1400 + INDEX)


## Matériel utilisé ##
- transistor
- portes logiques
- décodeur ?
- bascule ?
- (dé)multiplexeur ?
- eeprom ? (mémoire programme et microcode) (utiliser communication parallèle: http://fr.rs-online.com/web/p/memoires-eeprom/0394504/)
- ram ? (mémoire données et mémoire de la carte graphique. Y'a pas de SDRAM traversant chez RS mais y'a du SRAM: http://fr.rs-online.com/web/p/memoires-sram/0538148/)

L'avantage avec un processeur lent, c'est que les temps d'accès mémoire se font en un tic d'horloge...

## Jeu d'instructions ##
Si on veut un jeu rapide, il ne faut pas se contenter de quelques instructions mais ajouter des instructions assez haut niveau.
Il y a deux sortes d'instructions: les câblés (inaltérables) et les micro-codés (programmable).
Les câblés sont plus rapides que les micro-codés, mais consomment beaucoup de portes logiques.

### Instructions câblée monocycle ###
- mov
- Instructions logiques et arithmétiques sur deux registres
- Saut conditionnel (se base sur les flags)
- Saut inconditionnel
- load/store
- nop

### Instructions microcodées à voir selon le jeu. ###
- Pile ? (push, pop, call, ret)
- load/store avec index?
- Echange du contenu de deux registres ?
- Comparaison suivi d'un saut ?
- Instructions sur des booléens ?
- Instructions mémoire-registre ?

## Idées ##
- Un jeu d'instruction dynamique (qui change sans que le processeur ne s'éteigne)
- Il faudrait en plus du processeur et de sa mémoire, une carte son (pour jouer de la musique avec un floppy) et une carte graphique (qui transmet les informations de la mémoire à la matrice de led). Les fréquences de ces trois systèmes ne sont pas forcément les mêmes.
- La carte graphique pourrait gérer une matrice de diode pour les images et des afficheurs 7 segments pour les nombres. Voire utiliser un petit écran LCD.