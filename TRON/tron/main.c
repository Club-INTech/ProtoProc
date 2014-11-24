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

            int old_x = joueurs[i][indice[i]][0];
            int old_y = joueurs[i][indice[i]][1];

            ok |= ((indice[i]+1) == LONGUEUR);

            indice[i]++;
            indice[i] %= LONGUEUR;

            if(ok)
                table[joueurs[i][indice[i]][0]][joueurs[i][indice[i]][1]] = 0;

            joueurs[i][indice[i]][0] = (old_x+dir_x[direction[i]]+LARGEUR)%LARGEUR;
            joueurs[i][indice[i]][1] = (old_y+dir_x[direction[i]+1]+HAUTEUR)%HAUTEUR;

            if(table[joueurs[i][indice[i]][0]][joueurs[i][indice[i]][1]] != 0)
            {
                printf("Joueur %d a perdu!", i+1);
                return EXIT_SUCCESS;
            }

            table[joueurs[i][indice[i]][0]][joueurs[i][indice[i]][1]] = i+1;

        }
    }

    return 0;
}

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
    // initialisation de la table (sans obstacles ici)
    for(i = 0; i < LARGEUR; i++)
        for(j = 0; j < HAUTEUR; j++)
            table[i][j] = 0;

    srand(time(NULL));

    for(i = 0; i < 10; i++)
        table[rand()%LARGEUR][rand()%HAUTEUR] = 255;

    for(i = 0; i < NB_JOUEURS; i++)
    {
        do {
            // init des positions des joueurs
            joueurs[i][0][0] = rand()%LARGEUR;
            joueurs[i][0][1] = rand()%HAUTEUR;
        } while(table[joueurs[i][0][0]][joueurs[i][0][1]] != 0);

        table[joueurs[i][0][0]][joueurs[i][0][1]] = i+1; // on note l'obstacle

        for(j = 1; j < LONGUEUR; j++)
        {
            joueurs[i][j][0] = joueurs[i][0][0];
            joueurs[i][j][1] = joueurs[i][0][1];
        }
    }

}
