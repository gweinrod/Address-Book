/*
 * util.c
 *
 *  Created on: Nov 28, 2017
 *      Author: greg
 */


#include <string.h>
#include "util.h"


char *trim(char *source){
	if(source[strlen(source) - 1] == '\n') {
		source[strlen(source) - 1] = '\0';
	}
	return source;
}
