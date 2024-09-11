#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define LIG 20
#define COL 20

// init la grille avec des valeurs aléatoire :
void initGrille(int grille[LIG][COL])
{
	srand(time(NULL));
	// for (int i = 0; i < LIG; i++)
	// {
	// 	for (int j = 0; j < COL; j++)
	// 	{
	// 		grille[i][j] = rand() % 2;
	// 	}
	// }

	// le glider :
	grille[1][2] = 1;
	grille[2][3] = 1;
	grille[3][1] = 1;
	grille[3][2] = 1;
	grille[3][3] = 1;
}

void afficherGrille(int grille[LIG][COL])
{

	for (int i = 0; i < LIG; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			printf("%c ", grille[i][j] ? 'O' : '-');
		}
		printf("\n");
	}
	printf("\n");
}

int nbVoisinVivant(int grille[LIG][COL], int x, int y)
{
	int nbVivant = 0;

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)
				continue;

			int newX = x + i;
			int newY = y + j;

			if (newX >= 0 && newX < LIG &&
				newY >= 0 && newY < COL)
			{
				nbVivant += grille[newX][newY];
			}
		}
	}
	return nbVivant;
}

// Règles du jeu :
// Une cellule vivante avec moins de deux voisins vivants meurt(seule).
// Une cellule vivante avec deux ou trois voisins vivants reste vivante.
// Une cellule vivante avec plus de trois voisins vivants meurt(surpopulation).
// Une cellule morte avec exactement trois voisins vivants devient vivante(reproduction).

void generationSuivante(int grille[LIG][COL])
{
	int grilleSvt[LIG][COL];

	for (int i = 0; i < LIG; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			int voisinVivant = nbVoisinVivant(grille, i, j);
			if (grille[i][j] == 1) // si vivante
			{

				// printf("voisinVivant : %d\n", voisinVivant);
				if (voisinVivant < 2 || voisinVivant > 3)
				{
					grilleSvt[i][j] = 0;
				}
				else
				{
					grilleSvt[i][j] = 1;
				}
			}
			else
			{
				if (voisinVivant == 3)
				{
					grilleSvt[i][j] = 1;
				}
				else
				{
					grilleSvt[i][j] = 0;
				}
			}
		}
	}
	for (int i = 0; i < LIG; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			grille[i][j] = grilleSvt[i][j];
		}
	}
}

int main()
{
	int grille[LIG][COL] = {0}; // Initialise tous les éléments à 0
	srand(time(NULL));			// Initialise la graine aléatoire ici

	// Pour générer une grille aléatoire, décommentez cette section
	
	for (int i = 0; i < LIG; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			grille[i][j] = rand() % 2;
		}
	}
	

	// initGrille(grille); // Initialise le glider

	for (int i = 0; i < 100; i++)
	{
		afficherGrille(grille);
		generationSuivante(grille);
		usleep(200000);	 // Pause pour visualiser l'évolution
		system("clear"); // Nettoie la console pour la prochaine affichage
	}

	return 0;
}