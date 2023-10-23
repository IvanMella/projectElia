/************************************************************************
 * 									*
 *  Convert a String to seconds from epoch using time.h 		*
 *  The input string must be this format: "dd-mm-yyyy hh:mm:ss"		*
 *  Return a time_t value						*
 * 									*
 *  2023 Ivan Mella							*
 ************************************************************************/

#include <time.h>

time_t strtoepoch(const char * );
void epochtostr(time_t, char *);
