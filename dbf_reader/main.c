# include <stdio.h>
# include <stdlib.h>

typedef struct DatabaseRecords
{
	char fieldName[11];		// 0 - 10
	char fieldType;			// 11
	char reservedf[4];		// 12 - 15
	unsigned char fieldLength;	// 16
	char fieldDecimal;		// 17
	char waid;			// 18 - 19
	char example;			// 20
	char reserveds[10];		// 21 - 30
	char mdxflag;			// 31
} dbr;

typedef struct FieldDescriptorArray
{
	char vdbase;		// 0
	char open[3];		// 1 - 3
	long recordsdb;		// 4 - 7
	int headerb;		// 8 - 9
	int recordb;		// 10 - 11
	char reservedf[2];	// 12 - 13
	char transaction;	// 14
	char encryptionflag;	// 15
	char reserveds[12];	// 16 - 27
	char mdxflag;		// 28
	char driverid;		// 29
	char reservedt[2];	// 30 - 31
	dbr *fd;		// 32 - n
	char end;		// n + 1
} fda;

int main(int argc, char *argv[])
{
	printf("inizio\n");
	fda *mainfda;
	printf("prima check\n");
	if (argc < 2)
	{
		fprintf(stderr, "Missing required argument.\n"
			"Usage: %s bin_file \n\n", argv[0]);
		exit(1);
	}

	printf("prima fopen\n");
	FILE *f = fopen(argv[1], "rb");

	printf("dopo fopen\n");
	fread(mainfda, sizeof(fda), 1, f);
	printf("dopo fread\n");
	fclose(f);
	printf("dopo fclose\n");
	//printf();

	return 0;
}



