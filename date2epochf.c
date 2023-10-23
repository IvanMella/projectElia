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
#include "strtoepoch.h"

int main()
{
	char str[] = "12-07-2021 08:05:11";
	time_t seconds;

	seconds = strtoepoch(str);

	printf("Computed time epoch = (%d Bytes) %d -> %s",\
		sizeof(seconds), seconds, ctime(&seconds));

}
