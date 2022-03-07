#ifndef PENDU_H
	#define PENDU_H

	#include <stdlib.h>
	#include <stdio.h>
	#include <ctype.h>
	#include <string.h>
	#include <time.h>
	#include <unistd.h>

	void	ep_putchar(char c);

	char	*setMotMystere();
	char	*getMysteryWord(FILE* dico, int max);
	int		getNumberOfWords(char* chaine, FILE* dico);
	void	ep_displayPendu(int vies);

/*	typedef	dessin	dessin

	struct	dessin
	{
		char	un[20] = {'|', '\n', '|', '\n', '|', '\n', '|', '\n', '|', '\n', '|', '\n', '|', '\n', '|', '\n', '|', '\n', '|', 0};
		char	deux[41] = {}
	}*/

	#define TAILLE_MAX 51

#endif
