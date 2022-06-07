/*
 ============================================================================
 Name        : GWeinrodAddressBook.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "contactNode.h"
#include "addressBook.h"
#include "util.h"

/*
 * the main function is responsible for creating an address book structure,
 * processing user input, and executing functions contained in the
 * addressBook module.
 */
int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0);					//turn off output buffering

	addressBook *aBook = malloc(sizeof(addressBook));  	//make a new address book
	aBook->root = NULL;									//and initialize it to null/empty
	aBook->size = 0;

	char buf[BUFSIZ];


	//prompt user for commands, execute until quit command is received
	char command = ' ';
	while(command != 'q') {
		int index;
		char field;
		printf("%s", "Ready\n");
		fgets(buf, BUFSIZ, stdin);
		command = buf[0];
		switch(command) {
		case 'a': case 'A':	//add
			index = atoi(fgets(buf, BUFSIZ, stdin));
			insertContact(aBook, index, fgets(buf, BUFSIZ, stdin));
			break;
		case 'd': case 'D':	//delete
			removeContact(aBook, atoi(fgets(buf, BUFSIZ, stdin)));
			break;
		case 'g': case 'G':	//get (print the whole thing)
			printContact(aBook, atoi(fgets(buf, BUFSIZ, stdin)));
			break;
		case 'f': case 'F':	//get a field(print a field)
			index = atoi(fgets(buf, BUFSIZ, stdin));
			printField(aBook, index, fgets(buf, BUFSIZ, stdin));
			break;
		case 'n': case 'N':	//get # of contacts in the list
			printSize(aBook);
			break;
		case 'l': case 'L':	//load a file
			loadBook(aBook, trim(fgets(buf, BUFSIZ, stdin)));
			break;
		case 's': case 'S':	//save to file
			saveBook(aBook, trim(fgets(buf, BUFSIZ, stdin)));
			break;
		case 'q': case 'Q':	//quit
			break;
		case 'e': case 'E':
			index = atoi(fgets(buf, BUFSIZ, stdin));
			fgets(buf, BUFSIZ, stdin);
			field = buf[0];
			editContact(aBook, index, field, trim(fgets(buf, BUFSIZ, stdin)));
			break;
		case 'o': case 'O':
			sortBook(aBook);
			break;
		default:
			//improper command was entered, loop menu
			break;
		}
	}

	return EXIT_SUCCESS;
}
