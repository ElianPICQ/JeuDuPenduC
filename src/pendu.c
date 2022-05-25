#include "../include/pendu.h"

char	lireCaractere()
{
	char	caractere = 0;

	printf("    ==================\n");
	printf("Veuillez rentrer une lettre :  \n");
	printf("    ==================\n\n");

	caractere = getchar();
	caractere = toupper(caractere);

	while (getchar() != '\n') ; //Sert à vider le buffer de "getchar" .L'appeler directement renverrai un '\n'

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

char	*updatePlayerWord(char* playerWord, const char *motMystere, char playerInput)
{
	unsigned int	i = 0;
	
	while (i < strlen(playerWord))
	{
		if (motMystere[i] == playerInput)
			playerWord[i] = playerInput;
		i++;
	}
	return (playerWord);
}

char	*initPlayerWord(const char* motMystere)
{
	char*	word;
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

int 	playerWordIsIncomplete(char *playerWord)
{
	int i = 0;

	while(playerWord[i]) {
		if (playerWord[i++] == '*')
			return (1);
	}
	return (0);
}

int		restartGame()
{
	int	restart = 1;

	printf("\tVoulez vous relancer une partie ?\n");
	printf("\tTapez [1] pour relancer ou appuyez sur n'importe quelle touche pour quitter\n");

	restart = getchar();

	while (getchar() != '\n') ;

	if (restart == '1')
	{
		printf("\n\n\n\n");
		printf("\t---------------\n");
		printf("\tNOUVELLE PARTIE\n");
		printf("\t---------------\n");

		return (1);
	}
	else
	{
		printf("\t------------\n");
		printf("\tARRET DU JEU\n");
		printf("\t------------\n");

		return (0);
	}
	return 0;
}

void	fonctionMere()
{
	char	*motMystere = NULL;
	char	*playerWord	= NULL;
	char	playerInput	= 0;
	int 	vies;
	int		restart	= 1;
	char	*alpha;
	int		index, i;

	alpha = malloc(sizeof(char) * 27);
	alpha[26] = '\0';

	printf("\t---- JEU DU PENDU ----\n\n\n");
	printf("Bon vous connaissez le but du jeu...\n\n");
	printf("*****************\n");
	printf("** C'EST PARTI **\n");
	printf("*****************\n\n");

	printf("Ah oui, tu peux rentrer Zéro (0) à tout moment pour quitter.\n\n\n");

	while (restart == 1)
	{
		i = 0;
		vies = 10;
		index = 0;

		while (alpha[index]) {
			alpha[index++] = '0';
		}
		index = 0;

		motMystere = setMotMystere();
		playerWord = initPlayerWord(motMystere);

		while (vies > 0 && playerWordIsIncomplete(playerWord))
		{
			printf("Mot :\n\n%s\n\n", playerWord);

			playerInput = lireCaractere();
			if (playerInput == '0') {
				printf("EXIT GAME");
				exit(0);
			}

			if (strchr(alpha, playerInput)) {		//On vérifie que la lettre n'a pas déjà été rentrée (sinon -1 vie)
				vies -= 1;
				printf("\tTu as deja rentre cette lettre :(\n");
			}
			else if (strchr(motMystere, playerInput)) {			//Si la lettre est bonne (et qu'elle n'a pas été trouvée) on MaJ le playerWord)
				playerWord = updatePlayerWord(playerWord, motMystere, playerInput);
				printf("Vous avez trouve une lettre !\n");
				alpha[index] = playerInput;
				index++;
			}
			else {
				vies -=1;
				printf("\tRATE !\n\n");
				alpha[index] = playerInput;
				index++;
			}

			ep_displayPendu(vies);
	
			if (vies > 1)
				printf("\t--- Il vous reste %d vies ---\n", vies);
			else if (vies == 1)
				printf("\t--- Il vous reste %d vie ---\n", vies);
			printf("\n");

			printf("\n\n\n===================================\n|                                 |\n===================================\n\n");
		}

		if (vies == 0)
		{
			printf("T'as perdu...\nT'es un peu nul x)\n");
			printf("Pour la peine, jte dirais pas le mot\n");
			printf("Nan jdeconne c'etait : %s\n", motMystere);
			printf("mais c'est pas grave, tu peux reessayer !\n");
		}
		else
			printf("\nBien ouej, le mot etait bien :\n\t%s !\n", motMystere);
		restart = restartGame();

		free(playerWord);
		free(motMystere);
	}
	free(alpha);
}

int	main(int argc, char *argv[])
{
	printf("\n");
	fonctionMere();

	return 0;
}
