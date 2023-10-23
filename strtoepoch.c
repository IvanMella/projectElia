/************************************************************************
 * 									*
 *  Convert a String to seconds from epoch using time.h 		*
 *  The input string must be this format: "dd-mm-yyyy hh:mm:ss"		*
 *  Return a time_t value						*
 * 									*
 *  2023 Ivan Mella							*
 ************************************************************************/
#include <bits/types/time_t.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

time_t strtoepoch(const char * str)
{
	/* Hold str to be modified					*/
	char d[25];
	/* Pointers to d tokens						*/
	char *token[6];

	/* Time structures and vars					*/
	struct tm t = {0};
        time_t seconds;

	/* copy *str to *d						*/
	strcpy(d, str);

	/* Find the each pointer to token				*/
	token[0] = strtok(d, "-");
	for(int i = 1; i < 6; i++)
		token[i] = strtok(NULL, "- :");

	/* spit the strings out						*/
	//for(int i = 0; i < 6; i++)
	//	printf("%d -> %s\n",i , token[i]);

	/* Fill time structure						*/
	t.tm_sec = atoi(token[5]);	/* seconds, (0 to 59)		*/
	t.tm_min = atoi(token[4]);	/* minutes, range 0 to 59	*/
	t.tm_hour = atoi(token[3]);	/* hours, range 0 to 23		*/
	t.tm_mday = atoi(token[0]);	/* day of the month, (1 to 31)	*/
	t.tm_mon = atoi(token[1]) - 1;	/* month, (0 to 11)		*/
	t.tm_year = atoi(token[2]) - 1900;	/* Years since 1900	*/
	t.tm_isdst = -1;		/* daylight saving time		*/

	/* spit out each field of t structure 				*/
	//printf("'struct tm' fields: %d | %d | %d | %d | %d | %d  \n",\
		t.tm_year, t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min,\
		t.tm_sec);

	/* convert struct tm into time_t				*/
	seconds = mktime(&t);

	/* verify if it's ok						*/
	//strftime(buffer,80,"%x - %I:%M%p", &t);
	//printf("Formatted date & time : %s\n", buffer );
	//printf("Computed time epoch = (%d Bytes) %d -> %s",\
		sizeof(seconds), seconds, ctime(&seconds));
	return seconds;
}


void epochtostr(time_t t, char * result)
{
	struct tm  ts;

	// Format time, "ddd yyyy-mm-dd hh:mm:ss zzz"
	ts = *localtime(&t);
	strftime(result, 40, "%d-%m-%Y %H:%M", &ts);
}

