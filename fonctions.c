#include <stdio.h>
#include <stdlib.h>

void deplacerCurseur(FILE *fichier, int numero)
{
	char caractereLu = 0;

	rewind(fichier);

	while (numero > 0)
	{
		caractereLu = fgetc(fichier);
		if (caractereLu == '\n')
			numero--;
	}
	fseek(fichier, 0, SEEK_CUR);
	//printf("CaractereLu : %d\n", caractereLu);
}