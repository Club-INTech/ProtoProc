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

### Eléments à choisir ###
- Combien de bits? (bits effectivement utilisés + bits de redondance)
- Quels adressages disponibles?

### Matériel utilisé ###
- transistor
- portes logiques
- décodeur ?
- bascule ?
- (dé)multiplexeur ?
- eeprom ? (mémoire programme) (utiliser communication parallèle: http://fr.rs-online.com/web/p/memoires-eeprom/0394504/)
- ram ? (mémoire données. Y'a pas de SDRAM traversant chez RS mais y'a du SRAM: http://fr.rs-online.com/web/p/memoires-sram/0538148/)

L'avantage avec un processeur lent, c'est que les temps d'accès mémoire se font en un tic d'horloge...

## Idées ##
- Il faudrait en plus du processeur et de sa mémoire, une carte son (pour jouer de la musique avec un floppy) et une carte graphique (qui transmet les informations de la mémoire à la matrice de led). Les fréquences de ces trois systèmes ne sont pas forcément les mêmes.
- La carte graphique pourrait gérer une matrice de diode pour les images et des afficheurs 7 segments pour les nombres. Voire utiliser un petit écran LCD.