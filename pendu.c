#include "pendu.h"

int	getNumberOfWords(char* chaine, FILE* dico)
{
	int cpt = 0;

	while (fgets(chaine, TAILLE_MAX, dico))
		cpt++;

	rewind(dico);
	return (cpt);
}

char	*getMysteryWord(FILE* dico, int max)
{
	char*	chaine;
	int	randomizer = 0;

	chaine = malloc(sizeof(char) * TAILLE_MAX);
	
	srand(time(NULL));
	randomizer = (rand() % max);

	do
	{
		fgets(chaine, TAILLE_MAX, dico);
		randomizer--;
	}while (randomizer >= 0);

	return (chaine);
}

char	*setMotMystere()
{
	char*	chaine;
	FILE*	dico = NULL;
	int	nbRandomWords = 0;

	chaine = malloc(sizeof(char) * TAILLE_MAX);

	dico = fopen("dictionnaire.txt", "r");

	if (dico == NULL)
	{
		printf("***********************************************\n");
		printf("****                ERREUR                 ****\n");
		printf("****LE DICTIONNNAIRE N'A PAS PU ETRE OUVERT****\n");
		printf("****         FERMETURE DU PROGRAMME        ****\n");
		printf("***********************************************\n");

		exit(0);
	}
	nbRandomWords = getNumberOfWords(chaine, dico);
	chaine = getMysteryWord(dico, nbRandomWords);

	fclose(dico);

	return (chaine);
}

char	lireCaractere()
{
	char	caractere = 0;

	printf("____________________________\n\n");
	printf("Veuillez rentrer un lettre :  \n");
	printf("____________________________\n");

	caractere = getchar();
	caractere = toupper(caractere);

	while (getchar() != '\n') ;

	printf("\n");
	return (caractere);
}

int	findCharacter(const char* motMystere, const char playerInput)
{
	int	len;
	int i = 0;

	len = strlen(motMystere);

	while (i < len)
	{
		if (playerInput == motMystere[i])
			return (i);
		i++;
	}
	return (-1);
}

char	*updatePlayerWord(char* playerWord, const char *motMystere, char playerInput, long *cpt)
{
	unsigned int	i = 0;
	
	while (i < strlen(playerWord))
	{
		if (motMystere[i] == playerInput)
		{
			playerWord[i] = playerInput;
			*cpt += 1;
		}
		i++;
	}
	return (playerWord);
}

char	*initPlayerWord(const char* motMystere)
{
	char*	word = NULL;
	int	i = 0;
	int	len;

	len = strlen(motMystere);

	word = malloc(sizeof(char) * len);

	while (i < len - 1)
	{
		word[i] = '*';
		i++;
	}
	word[i] = '\0';
	return (word);
}

int	restartGame()
{
	int	restart = 1;

	printf("Voulez vous relancer une partie ?\n");
	printf("Tapez [1] pour relancer ou appuyez sur n'importe quelle touche pour quitter\n");

	restart = getchar();

	while (getchar() != '\n') ;

	if (restart == '1')
	{
		printf("\n\n\n\n");
		printf("---------------\n");
		printf("NOUVELLE PARTIE\n");
		printf("---------------\n");

		return (1);
	}
	else
	{
		printf("------------\n");
		printf("ARRET DU JEU\n");
		printf("------------\n");

		return (0);
	}
	return 0;
}

void	fonctionMere()
{
	char	*motMystere;
	char	*playerWord	= NULL;
	char	playerInput	= 0;
	int	i, vies;
	long	cpt;
	int	restart		= 1;
	char	*alpha;
	int	index		= 0;

	alpha = malloc(sizeof(char) * 27);
	alpha[26] = '\0';

	printf("---- JEU DU PENDU ----\n\n");
	printf("Bon vous connaissez le but du jeu...\n\n");
	printf("*****************\n");
	printf("** C'EST PARTI **\n");
	printf("*****************\n");
	do
	{
		i = 0;
		while (alpha[i] != 0)
		{
			alpha[i] = 0;
			i++;
		}
		i = 0, vies = 10, cpt = 0;

		motMystere = setMotMystere();
//		printf("Mot mystere = %s\n", motMystere);

		playerWord = initPlayerWord(motMystere);
		do
		{
			printf("Mot :\n\n%s\n", playerWord);

			playerInput = lireCaractere();

			if (strchr(alpha, playerInput) == NULL)
			{
				if (strchr(motMystere, playerInput))
				{
					alpha[index] = playerInput;
					index++;
				}
				i = findCharacter(motMystere, playerInput);
				
				printf("\n\n\n\n\n\n\n\n");	
				if (i == -1)
				{
	
					vies--;
	
					printf("Rate !\n");
	
				}
				else
				{
					playerWord = updatePlayerWord(playerWord, motMystere, playerInput, &cpt);
	
					printf("Vous avez trouve une lettre !\n");
				}
//				printf("Mot :\n%s\n", playerWord);
	
				if (vies > 1)
					printf("--- Il vous reste %d vies ---\n", vies);
				else if (vies == 1)
					printf("--- Il vous reste %d vie ---\n", vies);
				printf("\n");
	
//				printf("cpt = %ld\n", cpt);
//				printf("len = %ld\n", strlen(motMystere) - 1);
			}
			else
				printf("T'as deja rentre cette lettre pd\n");
		}while (vies > 0 && cpt < strlen(motMystere) - 1);

		if (vies == 0)
		{
			printf("T'as perdu...\nT'es un peu nul x)\n");
			printf("Pour la peine, jte dirais pas le mot\n");
			printf("Nan jdeconne c'etait : %s\n", motMystere);
			printf("mais c'est pas grave, tu peux reessayer !\n");
		}
		else
			printf("\nBien ouej, le mot etait bien :\n%s !", motMystere);
		restart = restartGame();
	}while (restart == 1);
}

int	main(int argc, char *argv[])
{
	printf("\n\n\n\n\n");
	fonctionMere();

	return 0;
}
