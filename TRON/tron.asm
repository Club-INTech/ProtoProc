; organisation de la mémoire graphique:
; XXX XXX XXY YYY YYY -> valeur
; 

#define LOG_TAILLE_X 8 ; 256
#define LOG_TAILLE_Y 7 ; 128
#define LOG_LONGUEUR 2 ; longueur de la queue
#define TAILLE_Y (1<<LOG_TAILLE_Y) ;hauteur de TAILLE_Y
#define TAILLE_X (1<<LOG_TAILLE_X) ;largeur de TAILLE_X
#define LONGUEUR (1<<LOG_LONGUEUR)
#define NB_JOUEURS 1 ;nb_joueurs
#define TAILLE_WORD 3 ;nombre de bit dans un mot machine
#define MUR (NB_JOUEURS+1)

#define WORD_PAR_X (LOG_TAILLE_X/TAILLE_WORD)+1
#define WORD_PAR_Y (LOG_TAILLE_Y/TAILLE_WORD)+1
; nombre de mots nécessaires pour coder une abscisse ou une ordonnnée
; par exemple, si on a des mots de 3 bits, et qu'il y a 2^7 = 128 cases en largeur (ou hauteur), il faut 7/3+1=3 mots pour coder l'abscisse (ou l'ordonnée)

; "table" a besoin de 2 valeurs différentes pour juste jouer (vide / plein), mieux vaut NB_JOUEURS+2 valeurs pour l'affichage graphique (1 couleur pour vide, 1 couleur pour plein, 1 couleur par joueur).
; du coup, il faudrait au moins 3 bits pour stocker chaque valeur

; il y a trois indices: un pour X, un pour Y, un pour le mot désiré
; l'organisation est faite ainsi: XXXYYY (avec "LOG_TAILLE_X" fois X, "LOG_TAILLE_Y" fois Y)
; "table" doit être aligné sur une puissance de 2 plus grande que LOG_TAILLE_X + LOG_TAILLE_Y + 3

table dw (1 << (LOG_TAILLE_X+LOG_TAILLE_Y+3)) dup (?)

; joueurs
; il y a 4 indices dans ce tableau.
; J: l'indice du joueur, entre 0 et NB_JOUEURS - 1 (max 4 joueurs). Tient sur 2 bits.
; Q: l'indice de la longueur de la queue, entre 0 et LONGUEUR-1. Tient sur LOG_LONGUEUR bits.
; W: l'indice à l'intérieur de l'abscisse (ou de l'ordonnée) elle-même, entre 0 et NB_WORD_POUR_POSITION-1. Tient sur 3 bits
; l'organisation est faite ainsi: JJ   QQQ   QQQ   WWW
;                                  3     2     1     0

; pour indices: 100 000 0JJ WWW

joueurs dw 1 << (1+2+2+LOG_LONGUEUR)) dup (?)
indices dw (NB_JOUEURS) dup (?)
direction dw (NB_JOUEURS) dup (?)
ok db FALSE
dir dw 0, 1, 0, -1, 0

; INITIALISATION

; initialise la table à 0

; index prend les valeurs de 0 à TAILLE_Y*TAILLE_X-1
mov index, TAILLE_Y*TAILLE_X ; i registre pour parcourir toute la table
mov base, table ; table est une adresse, constante. Attention, on utilise un OU logique après, il faut donc
; que l'utilisation des bits soit bien répartie entre l'index et la base
boucleInitTable:
dec index
mov [base|index], 0
jnz index, boucleInitTable

; générateur d'aléatoire?

; i prend les valeurs de 0 à NB_JOUEURS-1
mov i, NB_JOUEURS
bouclePourToutJoueur:
dec i

; LIGNES 

; j prend les valeurs de 1 à LONGUEUR-1
mov base1, ((LONGUEUR-1) & 7)+1 ; mot faible de LONGUEUR-1
mov base2, ((LONGUEUR-1) >> 3)+1 ; mot fort de LONGUEUR-1
mov base3, i

boucleInitQueue:
dec base1
cdec base2		; ne fait la décrémentation que si le dernier résultat a overflow


jnz base1, boucleInitQueue
jnz base2, boucleInitQueue
; on arrête si le dernier tour fut celui de 0 0

jnz j, boucleInitQueue
JJ QQQ QQQ AWW

jnz i, bouclePourToutJoueur



registres:
i, j, registre de 3 bits
index, registre de 5*3 bits
index est le mot de poids faible, jusqu'à index4, le mot de poids fort.
flags: nul (ou non-nul) = overflow d'incrémentation, overflow dec (vrai si le mot vaut 111)

mov index, 888666444222000
peut s'écrire en assembleur sans macro:
mov index0, 000
mov index1, 222
mov index2, 444
mov index3, 666
mov index4, 888

jnz reg, adr
peut s'écrire en assembleur sans macro:
cmp reg : met à jour les flags
jnz adr : consulte les flags pour sauter

dec reg
peut s'écrire en assembleur sans macro:
neg reg
inc reg
neg reg
qui peut encore s'écrire:
not reg
inc reg
inc reg
not reg
inc reg

jmp adr
peut s'écrire en assembleur sans macro:
cmp reg
jnz adr
not reg
cmp reg
not red
jnz adr

jne reg1, reg2, adr
peut s'écrire en assembleur sans macro:
mov ACC, reg1
xor ACC, reg2
cmp ACC
jnz adr

or ACC, imm
peut s'écrire en assembleur sans macro:
not ACC
and ACC, ~imm
not ACC

mov reg, imm
peut s'écrire en assembleur sans macro:
mov ACC, imm
mov reg, ACC

mov [index], reg1:reg2
qui envoie un double-mot (reg1 poids fort, reg2 poids faible) (little endian)
peut s'écrire en assembleur sans macro:
mov [index], reg2
inc index
mov [index], reg1
dec index

mov [index], reg1:reg2:reg3
qui envoie un triple-mot (reg1 poids fort, reg3 poids faible) (little endian)
peut s'écrire en assembleur sans macro:
mov [index], reg3
inc index
mov [index], reg2
inc index
mov [index], reg1
dec index
dec index

mov reg1:reg2:reg3, [index]
qui lit un triple-mot (reg1 poids fort, reg3 poids faible) (little endian)
peut s'écrire en assembleur sans macro:
mov reg3, [index]
inc index
mov reg2, [index]
inc index
mov reg1, [index]
dec index
dec index

Instructions nécessaires:
mov ACC, imm
mov reg, ACC
mov reg1, reg2
movg [index], reg ; mov graphique: envoie la valeur au processeur graphique
movg reg, [index] ;
movd [index], reg ; mov data
movd reg, [index] ; mov data
inc reg
dec reg
cinc reg ; conditional incrementation
cdec reg ; condition decrementation
cxor (reg) // effectue xor reg, 1 si overflow précédent
cmp reg
jnz adr
jmp adr
rnd reg1 ; valeur aléatoire dans reg1 (convertisseur analogique numérique relié à une antenne dont on prend les bits de poids faible)

composition instruction:
code instruction (4)
imm ou reg ou adr (4)
imm ou reg ou adr (4)
imm ou reg ou adr (4)
-> en codant une instruction sur 2 octets, on peut facilement avoir quelque chose de pas mal
