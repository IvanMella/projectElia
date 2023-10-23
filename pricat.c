# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include "strtoepoch.h"
# include <string.h>

typedef struct FinRow
{
	time_t date;
	double open;
	double high;
	double low;
	double close;
	double volume;
} binaryblock;

double ema_calc_elia(double, double, double);
double ema_calc(double, double, int);
void print_ema(binaryblock *, int, int[]);
void print_base_data(binaryblock *, int);


int main(int argc, char *argv[])
{
	int i = 1;

	/*	SE NON RICEVO FILE DI INPUT LANCIO UN ERRORE E CHIUDO	*/
	if (argc < 2)
	{
		printf("Inserire il file di input\n");
		exit(1);
	}

	struct stat fileinfo;
	stat(argv[1], &fileinfo);
	printf("File size: %ld bytes\n", fileinfo.st_size);

	/* TODO:
	 * Aggiungere sezione per controllo formato file */

	int numblocks = fileinfo.st_size /sizeof(binaryblock);
	/* alloca la memoria per ospitare tutto il file 		*/
	binaryblock *content = malloc(fileinfo.st_size);
	printf("Numblocks: %d\n", numblocks);

	FILE *f = fopen(argv[1], "rb");

	if (f == NULL)
	{
		char errmsg[100];
		sprintf(errmsg, "Can't open %s for reading", argv[1]);
		perror(errmsg);
		exit(1);
	}

	/* legge il file csv, lo copia in memoria (content) e lo chiude	*/
	fread(content, sizeof(binaryblock), numblocks, f);
	fclose(f);


	if (argc > 2 && !strcmp(argv[2], "--ema"))
	{
		/* Bruuutto bruttissimo bruttissimissimisssi...		*
		 * Processare gli argomenti in questo modo progressivo	*
		 * e frammentario oltre ad essere brutto e' pericoloso	*
		 * e anche mal fatto. mi sanguinano gli occhi se cerco 	*
		 * di capire cosa vuoi fare */
		if (argc < 4)
		{
			printf("Inserire almeno un periodo per l'ema");
			return 0;
		}

		/* quello che devo fare */
		//printf("Stampo l'ema\n");

		/* creo una variabile temporanea che punti a content in modo
		 * da non spostare il puntatore originale content */
		binaryblock *content_temp = content;

		/* indico un periodo che va a shiftare direttamente il puntatore
		 * content_temp di n righe */
		int period = atoi(argv[3]);
		content_temp += period;
		double smooth = 2.0;

		double smoothed = (smooth / (1 + period));

		/* assegno un primo valore ema può essere fatto così oppure
		 * calcolando l'SMA (Simple Moving Average) */
		double ema = content_temp->close;

		for (int i = period; i < numblocks; i++)
		{
			char date_str[40];

			/* facoltativo */
			epochtostr(content_temp->date, date_str);

			ema = ema_calc_elia(content_temp->close, ema, smoothed);
			printf("%s %lf %lf\n", date_str, content_temp->close, ema);

			content_temp++;
		}

		return 0;
	}

	/* se non ho chiamato la funzione ema_calc tramite "--ema" stampa
	 * i dati formattati*/
	print_base_data(content, numblocks);

	return 0;
}


void print_base_data(binaryblock *content, int numblocks)
{
	int i = 0;
	binaryblock *contentbegin = content;
	char date_str[40];

	while (i < numblocks)
	{
		epochtostr(content->date, date_str);
		printf("%s,%lf,%lf,%lf,%lf,%lf\n", 	date_str,
							content->open,
							content->high,
							content->low,
							content->close,
							content->volume);
		i++;
		content++;
	}
}


double ema_calc_elia(double current, double prev, double smoothing)
{
	/* Formula EMA:
	 * (current * (smoothing / (1 + period))) +
	 * prev * (1 - (smoothing / (1 + period))) */

	/* Se è il primo decidiamo se calcolarlo in maniera ortodossa
	 * oppure usando la formula del SMA */

	/* SMA:
	 * (a1 + a2 + ... + a_period) / period
	 **/

	double first = current * smoothing;
	double second = prev * (1 - smoothing);
	return first + second;
}



double ema_calc(double close , double prev, int multiplier)
{

	/* ci sono due formule per calcolare l'EMA. Quella che hai usato tu
	 * non è quella che mi va bene. Non ti spiego qui il perché dato
	 * che sono imbecille e non so come spiegarlo brevemente */
	return ((close - prev) * multiplier) + prev;
}

