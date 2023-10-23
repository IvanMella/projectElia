/************************************************************************
 * 									*
 *  Converts a Date epoch demo						*
 * 									*
 *  2023 Ivan Mella							*
 ************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	char d[] = "12-07-2021 08:05:11";
	char *token[6];
	struct tm t = {0};
        time_t seconds;
	char buffer[80];

	/* find the each pointer to token				*/
	token[0] = strtok(d, "-");
	for(int i = 1; i < 6; i++)
		token[i] = strtok(NULL, "- :");

	/* spit the strings out						*/
	for(int i = 0; i < 6; i++)
		printf("%d -> %s\n",i , token[i]);

	/* Fill time structure						*/
	t.tm_sec = atoi(token[5]);	/* seconds, (0 to 59)		*/
	t.tm_min = atoi(token[4]);	/* minutes, range 0 to 59	*/
	t.tm_hour = atoi(token[3]);	/* hours, range 0 to 23		*/
	t.tm_mday = atoi(token[0]);	/* day of the month, (1 to 31)	*/
	t.tm_mon = atoi(token[1]) - 1;	/* month, (0 to 11)		*/
	t.tm_year = atoi(token[2]) - 1900;	/* Years since 1900	*/
	t.tm_isdst = -1;			/* daylight saving time		*/

	/* spit out each field of t structure 				*/
	printf("'struct tm' fields: %d | %d | %d | %d | %d | %d  \n",\
		t.tm_year, t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min,\
		t.tm_sec);

	/* convert struct tm into time_t				*/
	seconds = mktime(&t);

	/* verify if it's ok						*/
	strftime(buffer,80,"%x - %I:%M%p", &t);
	printf("Formatted date & time : %s\n", buffer );
	printf("Computed time epoch = (%d Bytes) %d -> %s",\
		sizeof(seconds), seconds, ctime(&seconds));

}
