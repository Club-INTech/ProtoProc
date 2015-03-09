NB_JOUEURS EQU #1
JOUEUR_ACTUEL EQU r0
MUR EQU #7
NB_MURS EQU #10
INDICES_ARRAY EQU #4
INDICE_HIGH EQU r1
INDICE_LOW EQU r2
XY0 EQU r3
XY1 EQU r4
XY2 EQU r5
XY3 EQU r6
XY4 EQU r7

; INITIALISATION

; nécessaire pour "ok"
mov r8, #1

; on remet à la table à 0
mov index0, #0
mov index1, #0
mov index2, #0
mov index3, #0
mov index4, #0
mov r0, #0
	boucleInitTable:
dec index0
cdec index1
cdec index2
cdec index3
cdec index4
movg [index], r0
jnz index, boucleInitTable

mov r0, NB_MURS
mov r1, MUR
	boucleInitTableRandom:
rnd index0
rnd index1
rnd index2
rnd index3
rnd index4
movg [index], r1
dec r0
jnz r0, boucleInitTableRandom

mov JOUEUR_ACTUEL, NB_JOUEURS
	boucleInitJoueurs:
dec JOUEUR_ACTUEL

	boucleInitPositionJoueur:
rnd index0
rnd index1
rnd index2
rnd index3
rnd index4
movg r1, [index]
jnz r1, boucleInitPositionJoueur
movg [index], JOUEUR_ACTUEL
mov r1, index0
mov r2, index1
mov r3, index2
mov r4, index3
mov r5, index4

mov index1, #0
mov index2, #0 // dernier élément de la queue + 1
mov index3, JOUEUR_ACTUEL // numéro du joueur
; la mémoire vive est adressé sur 12 bits, donc index4 est non utilisé
boucleInitQueue:
mov index0, #0 // pour l'abscisse
dec index1
cdec index2
movd [index], r1
inc index0
movd [index], r2
inc index0
movd [index], r3
inc index0
movd [index], r4
inc index0
movd [index], r5
inc index0
jnz index1, boucleInitQueue
jnz index2, boucleInitQueue

jnz JOUEUR_ACTUEL, boucleInitJoueurs

mov JOUEUR_ACTUEL, NB_JOUEURS
boucleJeu:
dec JOUEUR_ACTUEL

mov index0, #0
mov index1, JOUEUR_ACTUEL
mov index2, #0
mov index3, INDICES_ARRAY
movd INDICE_LOW, [index]
inc index0
movd INDICE_HIGH, [index]	; INDICE_HIGH:INDICE_LOW contient indice[i]
dec index0
; index0 est nul
mov index1, INDICE_LOW
mov index2, INDICE_HIGH
mov index3, JOUEUR_ACTUEL
movd r7.r6.r5.r4.r3, [index] ; ils contiennent les anciennes valeurs de X et Y

inc r1
cinc r2 // incrémentation de indice[i]
// le modulo est automatique

mov index0, 0
mov index1, JOUEUR_ACTUEL
mov index2, 0
mov index3, 4
movd [index], r2.r1 // on enristre la nouvelle valeur

jnz r3, pasNouveauOk
jnz r2, pasNouveauOk
mov r8, 0 // nul: ok est vrai
// (ne pas oublier d'initialiser r10 à une valeur non nulle)

pasNouveauOk:
jnz r8, pasOk

mov index0, 0
mov index1, r2
mov index2, r3
mov index3, JOUEUR_ACTUEL
movd index, [index] // on récupère l'abscisse à cet indice
movg [index], 0 // et on y met 0

pasOk: // on a fini la condition

mov r1, INJ1 // input joueur 1
jnz r1, pas0

//00 : HAUT
inc r3
cinc r4
cxor r5
jmp finCondition

pas0:
dec r1
jnz r1, pas1
//01 : BAS
dec r3
cdec r4
cxor r5, 1
jmp finCondition

pas1:
dec r1
jnz r1, pas2
//10 : GAUCHE
dec r5
cdec r6
cdec r7
dec r5
cdec r6
cdec r7
jmp finCondition

pas2:
// du coup, c'est forcément 3
//11 : DROITE
inc r5
cinc r6
cinc r7
inc r5
cinc r6
cinc r7

finCondition:

mov index0, 0
mov index1, r2
mov index2, r3
mov index3, JOUEUR_ACTUEL

movd [index], r7.r6.r5.r4.r3

mov index0, r3
mov index1, r4
mov index2, r5
mov index3, r6
mov index4, r7

movg r1, [index]
jnz finJeu

mov r2, JOUEUR_ACTUEL
inc r2
movg [index], r2

jnz JOUEUR_ACTUEL, boucleInitJoueurs
mov JOUEUR_ACTUEL, NB_JOUEURS
jmp boucleInitJoueurs

