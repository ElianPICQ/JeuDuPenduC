#include "../include/pendu.h"

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
	char*	mysteryWord;
	int	randomizer = 0;

	mysteryWord = malloc(sizeof(char) * TAILLE_MAX);
	
	srand(time(NULL));
	randomizer = (rand() % max);

	do
	{
		fgets(mysteryWord, TAILLE_MAX, dico);
		randomizer--;
	}while (randomizer >= 0);

	return (mysteryWord);
}

char	*setMotMystere()
{
	char*	chaine;
	FILE*	dico = NULL;
	int	nbRandomWords;

	chaine = malloc(sizeof(char) * TAILLE_MAX);

	dico = fopen("dictionnaire.txt", "r");

	if (dico == NULL)
	{
		printf("***********************************************\n");
		printf("**                  ERREUR                   **\n");
		printf("**  LE DICTIONNNAIRE N'A PAS PU ETRE OUVERT  **\n");
		printf("**           FERMETURE DU PROGRAMME          **\n");
		printf("***********************************************\n");

		exit(0);
	}
	nbRandomWords = getNumberOfWords(chaine, dico);
	free(chaine);
	chaine = getMysteryWord(dico, nbRandomWords);

	fclose(dico);

	return (chaine);
}
