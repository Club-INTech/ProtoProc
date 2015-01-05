#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HAUTEUR 10
#define LARGEUR 10
#define LONGUEUR 5

#define NB_JOUEURS 2

#define TRUE 1
#define FALSE 0

#define HAUT 0
#define DROITE 1
#define BAS 2
#define GAUCHE 3

void affiche();
void init();

unsigned char table[LARGEUR][HAUTEUR]; // nb de joueur, 0 si rien, 255 si bloc
unsigned char joueurs[NB_JOUEURS][LONGUEUR][2];
unsigned char indice[NB_JOUEURS] = {0, 0};
unsigned char direction[NB_JOUEURS] = {HAUT, HAUT};
unsigned char ok = FALSE;
char dir_x[5] = {0, 1, 0, -1, 0};

char i, j;
char in;

int main()
{
    init();

    while(1)
    {
        for(i = 0; i < NB_JOUEURS; i++)
        {

mov reg0, NB_JOUEURS
boucleJeu:
dec reg0

            affiche();
            scanf("%d", &in);

            if(in == 8)
                direction[i] = HAUT;
            else if(in == 4)
                direction[i] = GAUCHE;
            else if(in == 6)
                direction[i] = DROITE;
            else if(in == 2)
                direction[i] = BAS;

// on n'aura qu'à lire les registres qui contiennent les valeurs. On fera en sorte qu'électriquement, le registre conserve la dernière valeur non nulle

            int old_x = joueurs[i][indice[i]][0];
            int old_y = joueurs[i][indice[i]][1];

mov index0, 0
mov index1, reg0
mov index2, 0
mov index3, 4
movd reg2:reg1, [index] // reg3:reg2 contient indice[i]
// index0 vaut 0
mov index1, reg1
mov index2, reg2
mov index3, reg0
movd reg7:reg6:reg5:reg4:reg3, [index] // ils contiennent les anciennes valeurs de X et Y
            ok |= ((indice[i]+1) == LONGUEUR);

            indice[i]++;
            indice[i] %= LONGUEUR;

inc reg1
cinc reg2 // incrémentation de indice[i]
// le modulo est automatique

mov index0, 0
mov index1, reg0
mov index2, 0
mov index3, 4
movd [index], reg2:reg1 // on enregistre la nouvelle valeur

jnz reg3, pasNouveauOk
jnz reg2, pasNouveauOk
mov reg8, 0 // nul: ok est vrai
// (ne pas oublier d'initialiser reg10 à une valeur non nulle)

pasNouveauOk:
jnz reg8, pasOk

            if(ok)
                table[joueurs[i][indice[i]][0]][joueurs[i][indice[i]][1]] = 0;

mov index0, 0
mov index1, reg2
mov index2, reg3
mov index3, reg0
movd index, [index] // on récupère l'abscisse à cet indice
movg [index], 0 // et on y met 0

pasOk: // on a fini la condition

            joueurs[i][indice[i]][0] = (old_x+dir_x[direction[i]]+LARGEUR)%LARGEUR;
            joueurs[i][indice[i]][1] = (old_y+dir_x[direction[i]+1]+HAUTEUR)%HAUTEUR;

mov reg1, INJ1 // input joueur 1
jnz reg1, pas0

//00 : HAUT
inc reg3
cinc reg4
cxor reg5
jmp finCondition

pas0:
dec reg1
jnz reg1, pas1
//01 : BAS
dec reg3
cdec reg4
cxor reg5, 1
jmp finCondition

pas1:
dec reg1
jnz reg1, pas2
//10 : GAUCHE
dec reg5
cdec reg6
cdec reg7
dec reg5
cdec reg6
cdec reg7
jmp finCondition

pas2:
// du coup, c'est forcément 3
//11 : DROITE
inc reg5
cinc reg6
cinc reg7
inc reg5
cinc reg6
cinc reg7

finCondition:

mov index0, 0
mov index1, reg2
mov index2, reg3
mov index3, reg0

movd [index], reg7:reg6:reg5:reg4:reg3

            if(table[joueurs[i][indice[i]][0]][joueurs[i][indice[i]][1]] != 0)
            {
                printf("Joueur %d a perdu!", i+1);
                return EXIT_SUCCESS;
            }

mov index0, reg3
mov index1, reg4
mov index2, reg5
mov index3, reg6
mov index4, reg7

movg reg1, [index]
jnz finJeu

            table[joueurs[i][indice[i]][0]][joueurs[i][indice[i]][1]] = i+1;

mov reg2, reg0
inc reg2
movg [index], reg2

        }
jnz reg0, boucleInitJoueurs
mov reg0, NB_JOUEURS
jmp boucleInitJoueurs
    }

    return 0;
}

finJeu: 
TODO...

void affiche()
{
    char i, j;
    for(j = 0; j < HAUTEUR; j++)
    {
        printf("\n");
        for(i = 0; i < LARGEUR; i++)
        {
            if(table[i][HAUTEUR-j-1] == 0)
                printf(".");
            else if(table[i][HAUTEUR-j-1] >= 1 && table[i][HAUTEUR-j-1] < 255)
                printf("%c",'A'+table[i][HAUTEUR-j-1]-1);
            else if(table[i][HAUTEUR-j-1] == 255)
                printf("X");
        }
    }
    printf("\n");

}

void init()
{

mov reg8, 1
    // initialisation de la table (sans obstacles ici)
    for(i = 0; i < LARGEUR; i++)
        for(j = 0; j < HAUTEUR; j++)
            table[i][j] = 0;

mov index, 0 ;taille tableau = indice max + 1 = overflow, on retombe à 0
boucleInitTable:
dec index
movg [index], 0
cmp index
jnz boucleInitTable

    srand(time(NULL));

    for(i = 0; i < 10; i++)
        table[rand()%LARGEUR][rand()%HAUTEUR] = 255;

mov reg0, 10 // valeur à ajuster...
mov reg1, MUR
boucleInitTableRandom:
rnd index0
rnd index1
rnd index2
rnd index3
rnd index4
movg [index], reg1
dec reg0
cmp reg0
jnz boucleInitTableRandom


    for(i = 0; i < NB_JOUEURS; i++)
    {
mov reg0, NB_JOUEURS
boucleInitJoueurs:
dec reg0

        do {
            // init des positions des joueurs
            joueurs[i][0][0] = rand()%LARGEUR;
            joueurs[i][0][1] = rand()%HAUTEUR;
        } while(table[joueurs[i][0][0]][joueurs[i][0][1]] != 0);
        table[joueurs[i][0][0]][joueurs[i][0][1]] = i+1; // on note l'obstacle

boucleInitPositionJoueur:
rnd index0
rnd index1
rnd index2
rnd index3
rnd index4
movg reg1, [index]
cmp reg1
jnz boucleInitPositionJoueur
movg [index], reg0 // reg0 contient le numéro du joueur
mov reg1, index0
mov reg2, index1
mov reg3, index2
mov reg4, index3
mov reg5, index4



        for(j = 1; j < LONGUEUR; j++)
        {
            joueurs[i][j][0] = joueurs[i][0][0];
            joueurs[i][j][1] = joueurs[i][0][1];
        }

mov index0, 0 // pour l'abscisse
mov index1, 0
mov index2, 0 // dernier élément de la queue + 1
mov index3, reg0 // numéro du joueur
boucleInitQueue:
dec index1
cdec index2
movd [index], reg5:reg4:reg3:reg2:reg1
jnz index1, boucleInitQueue
jnz index2, boucleInitQueue

jnz reg0, boucleInitJoueurs

    }

}
