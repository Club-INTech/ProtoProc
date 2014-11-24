;espace mémoire:
;

#define LOG_TAILLE_X 2
#define LOG_TAILLE_Y 2
#define LOG_LONGUEUR 2
#define TAILLE_Y (1<<LOG_TAILLE_Y) ;hauteur de TAILLE_Y
#define TAILLE_X (1<<LOG_TAILLE_X) ;largeur de TAILLE_X
#define LONGUEUR (1<<LOG_LONGUEUR) ;longueur de LONGUEUR
#define NB_JOUEURS 1 ;nb_joueurs
#define TRUE 1
#define FALSE 0
#define TAILLE_WORD 2 ;nombre de bit dans un mot machine

#define WORD_PAR_X (LOG_TAILLE_X/TAILLE_WORD)+1
#define WORD_PAR_Y (LOG_TAILLE_Y/TAILLE_WORD)+1
; nombre de mots nécessaires pour coder une abscisse ou une ordonnnée
; par exemple, si on a des mots de 3 bits, et qu'il y a 2^7 = 128 cases en largeur (ou hauteur), il faut 7/3+1=3 mots pour coder l'abscisse (ou l'ordonnée)

; "table" a besoin de 2 valeurs différentes pour juste jouer (vide / plein), mieux vaut NB_JOUEURS+2 valeurs pour l'affichage graphique (1 couleur pour vide, 1 couleur pour plein, 1 couleur par joueur).
; du coup, il faudrait au moins 3 bits pour stocker chaque valeur
; il y a trois indices: un pour X, un pour Y, un pour le mot désiré
; l'organisation est faite ainsi: XXXYYYWWW (avec "LOG_TAILLE_X" fois X, "LOG_TAILLE_Y" fois Y, 3 fois W)
; "table" doit être aligné sur une puissance de 2 plus grande que LOG_TAILLE_X + LOG_TAILLE_Y + 3

table dw (1 << (LOG_TAILLE_X+LOG_TAILLE_Y+3)) dup (?)

; joueurs
; il y a 4 indices dans ce tableau.
; J: l'indice du joueur, entre 0 et NB_JOUEURS - 1 (max 4 joueurs). Tient sur 2 bits.
; Q: l'indice de la longueur de la queue, entre 0 et LONGUEUR-1. Tient sur LOG_LONGUEUR bits.
; A: l'indice d'abscisse ou d'ordonnée (0: abscisse, 1: ordonnée). Tient sur 1 bit.
; W: l'indice à l'intérieur de l'abscisse (ou de l'ordonnée) elle-même, entre 0 et NB_WORD_POUR_POSITION-1. Tient probablement sur 2 bits
; l'organisation est faite ainsi: JJ   QQQ   QQQ   WWA
;                                  3     2     1     0

joueurs dw 1 << (1+2+2+LOG_LONGUEUR)) dup (?)
indices dw (NB_JOUEURS) dup (?)
direction dw (NB_JOUEURS) dup (?)
ok db FALSE
dir dw 0, 1, 0, -1, 0

; INITIALISATION

; initialise la table à 0

; index prend les valeurs de 0 à TAILLE_Y*TAILLE_X-1
mov index, TAILLE_Y*TAILLE_X ; i registre pour parcourir toute la table
mov base, table ; table est une adresse, constante
boucleInitTable:
dec index
mov [base|index], 0
jnz index, boucleInitTable

; générateur d'aléatoire?

; i prend les valeurs de 0 à NB_JOUEURS-1
mov i, NB_JOUEURS
bouclePourToutJoueur:
dec i

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

mov base, 666444222000
peut s'écrire en assembleur sans macro:
mov base0, 000
mov base1, 222
mov base2, 444
mov base3, 666

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

mov reg, imm
peut s'écrire en assembleur sans macro:
mov ACC, imm
mov reg, ACC

Instructions nécessaires:
mov ACC, imm
mov reg, ACC
mov [index], reg
inc reg
cpinc reg ; conditional positive incrementation
cninc reg ; condition negative incrementation
not reg
cmp reg
jnz add
xor ACC, reg1 ; comparaison
and ACC, imm ; pour les calculs de modulo


composition instruction:
code instruction
imm (3)
reg (3 ou 4)
adr(16)
-> en codant une instruction sur 4 octets, on peut facilement avoir quelque chose de pas mal
