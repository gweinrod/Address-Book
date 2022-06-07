/*
 * addressBook.h
 *
 *  Created on: Nov 28, 2017
 *      Author: greg
 */

#ifndef ADDRESSBOOK_H_
#define ADDRESSBOOK_H_

#include "contactNode.h"

typedef struct addressBook {
	cNode *root;
	int size;
} addressBook;

//insert
void insertContact(addressBook *book, int index, char *data);

//remove, do nothing if index is higher than # of contacts
void removeContact(addressBook *book, int index);

//print a contact.... comma,delimited,fields
void printContact(addressBook *book, int index);

//print a field
void printField(addressBook *book, int index, char *field);

//print # of contacts
void printSize(addressBook *book);

void editContact(addressBook *book, int index, char field, char *data);

//load book from file
void loadBook(addressBook *book, char *filename);

//save book to file
void saveBook(addressBook *book, char *filename);

//find a node by index
cNode *walk(addressBook *book, int n);

//selection sort (find minimum, place at beginning, so on, so forth)
void sortBook(addressBook *book);

//find a minimum node given a starting node in a list
cNode *findMin(cNode *start);

//swap two nodes
void swapNodes(cNode *a, cNode *b);

#endif /* ADDRESSBOOK_H_ */
