/************************************************************************
 * 									*
 *  Converts Csv Files to Binary					*				 *									*
 * 									*
 *  2023 Ivan Mella							*
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "strtoepoch.h"

/*			TEST						*/

typedef struct FinRow
{
	time_t date;
	double open;
	double high;
	double low;
	double close;
	double volume;
} binaryblock;


int main(int argc, char *argv[])
{

	/* se il main non riceve almeno 1 argomento esce */
	if (argc < 2)
	{
		/* stampa il messaggio d' errore */
		fprintf(stderr, "Missing required argument.\n"
			"Usage: %s csv_file [bin_file] [-e nnn] [...]\n\n", argv[0]);
		exit(1);
	}

	struct stat fileinfo;
	stat(argv[1], &fileinfo);
	printf("File size: %ld bytes\n", fileinfo.st_size);

	/* alloca la memoria per ospitare tutto il file 		*/
	char *content = malloc(fileinfo.st_size);

	FILE *f = fopen(argv[1], "r");
	if (!f)
	{
		char errmsg[100];
		sprintf(errmsg, "Can't open %s for reading", argv[1]);
		perror(errmsg);
		exit(1);
	}

	/* legge il file csv, lo copia in memoria (content) e lo chiude	*/
	fread(content, sizeof(char), fileinfo.st_size, f);
	fclose(f);

	/* conta i campi nel file per sapere la memoria da allocare, 	*
	 * sottrae i primi 6 campi header che non servono		*/
	int ntokens = 0;
	char *c = content;
	while(*c != '\0')
	{
		if(*c == ',' || *c == '\n')
			ntokens++;
		c++;
	}

	ntokens -= 6;

	printf("Tokens: %d\n",ntokens);

	/* Predispone la memoria per il vettore di puntatori ai campi   */
	char **token = malloc(sizeof(char *) * (ntokens));
	if(token == NULL)
	{
		printf("Memory error!\n");
		exit(1);
	}
	/* crea un vettore (token) con tutti gli indirizzi del primo	*
	 * carattere di ogni campo					*/

	/* skippa i primi 6 campi					*/
	strtok(content, "\n,");
	for(int i = 0; i < 5; i++)
		strtok(NULL, "\n,");

	/* comincia a creare il vettore dal 6o campo			*/
	for(int i = 0; i < ntokens; i++)
	{
		token[i] = strtok(NULL, "\n,");
		//printf("%d: %s\n", i, token[i]);
	}

	/****************************************************************
	 * Let's Binarize!						*
	 ****************************************************************
	/* Prepara le dimensioni del file di output un campo size_t e 5 *
	 * campi double 						*/

	int nblocks = ntokens / 6;

	binaryblock *outputcontent = malloc(nblocks * sizeof(binaryblock));
	if(outputcontent == NULL)
	{
		printf("Memory error!\n");
		exit(1);
	}
	printf("Memoria allocata: %d bytes\n", nblocks * sizeof(binaryblock));

	binaryblock *startbuf = outputcontent;
	/* riempie outputcontent	*/
	for(int i = 0; i < ntokens; i+=6)
	{
		outputcontent->date = strtoepoch(token[i]);
		outputcontent->open = atof(token[i + 1]);
		outputcontent->high = atof(token[i + 2]);
		outputcontent->low = atof(token[i + 3]);
		outputcontent->close = atof(token[i + 4]);
		outputcontent->volume = atof(token[i + 5]);
		outputcontent++;
		//printf("%d..",i);
	}

	FILE *write_ptr;

	printf("Writing.. ");

	if(argc == 3)
	{
		printf("%s\n", argv[2]);
		write_ptr = fopen(argv[2],"wb");
	}
	else
	{
		printf("output.bin\n");
		write_ptr = fopen("output.bin","wb");
	}

	/* Dump the whole array to the file in one shot 		*/
	fwrite(startbuf, sizeof(binaryblock), nblocks, write_ptr);

	fclose(write_ptr);

	/* Free memory							*/
	free(content);
	free(token);
	free(startbuf);

}
