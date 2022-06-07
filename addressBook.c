/*
 * addressBook.c
 *
 *  Created on: Nov 28, 2017
 *      Author: greg
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contactNode.h"
#include "addressBook.h"

//insert
void insertContact(addressBook *book, int index, char *data) {

	cNode *newNode = createContact(data);

	if (book->root) {	//book is not empty
		if (index == 0) {
			//inserting at the root
			newNode->next = book->root;
			book->root->prev = newNode;
			book->root = newNode;
		} else if (index == (book->size)) {
			//inserting at the tail
			cNode *tail = walk(book, book->size - 1);
			newNode->prev = tail;
			tail->next = newNode;
		} else {
			//inserting in the middle
			cNode *current = walk(book, index);
			newNode->next = current;
			newNode->prev = current->prev;
			current->prev->next = newNode;
			current->prev = newNode;
		}
	} else {
		book->root = newNode;	//book is empty, insert at the root
	}

	book->size++;
	return;
}

//remove, do nothing if index is higher than # of contacts
void removeContact(addressBook *book, int index) {

	if (index <= (book->size - 1)) {
		//valid deletion
		if (index == 0) {
			//deleting root
			if (book->size == 1) {
				//root is the last item
				deleteContact(book->root);
			} else {
				//root is not the last item
				book->root = book->root->next;
				deleteContact(book->root->prev);
				book->root->prev = NULL;
			}
		} else if (index == (book->size - 1)) {
			//deleting tail
			cNode *current = walk(book, index);
			current->prev->next = NULL;
			deleteContact(current);
		} else {
			//deleting in the middle
			cNode *current = walk(book, index);
			current->prev->next = current->next;
			current->next->prev = current->prev;
			deleteContact(current);
		}
		book->size--;
	}
	return;
}

//print a contact.... comma,delimited,fields
void printContact(addressBook *book, int index) {
	if (index < (book->size)) {
		cNode *current = walk(book, index);
		printf("%s,%s,%s,%s\n", current->lName, current->fName, current->email,
				current->phone);
	}
	return;
}

//print a field
void printField(addressBook *book, int index, char *field) {
	if (index < (book->size)) {
		cNode *current = walk(book, index);
		switch (field[0]) {
		case 'l':
		case 'L':
			printf("%s\n", current->lName);
			break;
		case 'f':
		case 'F':
			printf("%s\n", current->fName);
			break;
		case 'e':
		case 'E':
			printf("%s\n", current->email);
			break;
		case 'p':
		case 'P':
			printf("%s\n", current->phone);
			break;
		default:
			break;
		}
	}
	return;
}

//print # of contacts
void printSize(addressBook *book) {
	printf("%d\n", book->size);
	return;
}

void editContact(addressBook *book, int index, char field, char *data) {
	if (index < (book->size)) {
		cNode *current = walk(book, index);
		editContactNode(current, field, data);
	}
	return;
}

//load book from file
void loadBook(addressBook *book, char *filename) {

	char buf[BUFSIZ];

	FILE *loadFile = fopen(filename, "r");

	fgets(buf, BUFSIZ, loadFile);

	while (fgets(buf, BUFSIZ, loadFile) != NULL) {
		insertContact(book, book->size, buf);
	}

	fclose(loadFile);

	return;
}

//save book to file
void saveBook(addressBook *book, char *filename) {
	cNode *current = book->root;
	FILE *saveFile = fopen(filename, "w");

	fprintf(saveFile, "%s", "lastName,firstName,email,phoneNumber\n");

	while (current) {
		fprintf(saveFile, "%s,%s,%s,%s\n", current->lName, current->fName,
				current->email, current->phone);
		current = current->next;
	}

	fclose(saveFile);

	return;
}

//find a node by index
cNode *walk(addressBook *book, int n) {
	cNode *current = book->root;
	int i = 0;
	while (i < n) {
		current = current->next;
		i++;
	}
	return current;
}

//selection sort (find minimum, place at beginning, so on, so forth)
void sortBook(addressBook *book) {

	if (book->root) {
		cNode *current = book->root;		//start selection sort at the beginning
		int sorted = 0;						//size of sorted section
		while (sorted < book->size) {		//while sorted size is less than book size
			cNode *min = findMin(current);  //find the next minimum value
			if(current != min) swapNodes(current, min);		//swap the current with the minimum (if not already the minimum)
			if(current == book->root) book->root = min;		//the root was swapped, update reference
			sorted++;						//increment the size of the sorted section
			current = min->next;			//advance to the first unsorted element
		}

	}

	return;
}

cNode *findMin(cNode *start) {
	cNode *min = start;
	cNode *current = start;
	while (current) {
		if (strcmp(current->raw, min->raw) < 0) {
			min = current;
		}
		current = current->next;
	}

	return min;
}

void swapNodes(cNode *a, cNode *b) {
	if(!a->prev) {
		//swapping to the root
		if(!b->next) {
			//swapping the tail(b) to the root(a)
			if(a->next == b) {
				//swapping the tail(b) to the root(a) in a two item list
				b->next = a;
				a->prev = b;
				b->prev = NULL;
				a->next = NULL;
			} else {
				//swapping tail(b) to the root(a) in a three+ item list
				a->next->prev = b;
				b->prev->next = a;
				a->prev = b->prev;
				b->next = a->next;
				b->prev = NULL;
				a->next = NULL;
			}
		} else {
			//swapping a middle item(b) to the root(a)
			b->prev->next = a;
			b->next->prev = a;
			a->next->prev = b;
			a->prev = b->prev;
			cNode *temp = a->next;
			a->next = b->next;
			b->next = temp;
			b->prev = NULL;
		}
	} else if (!b->prev) {
		//root was given as b
		swapNodes(b, a);
	} else if (!b->next) {
		//swapping middle item to the tail
		b->prev->next = a;
		a->prev->next = b;
		a->next->prev = b;
		b->next = a->next;
		a->next = NULL;
		cNode *temp = b->prev;
		b->prev = a->prev;
		a->prev = temp;
	} else if (!a->next) {
		//tail was given as a
		swapNodes(b, a);
	} else {
		//swapping two interior items
		if(a->next == b) {
			//swapping two adjacent interior nodes
			 a->prev->next = b;
			 b->next->prev = a;
			 b->prev = a->prev;
			 a->prev = b;
			 a->next = b->next;
			 b->next = a;
		} else if(b->next == a) {
			//try again
			swapNodes(b,a);
		} else {
			//swapping two non-adjacent interior nodes
			a->prev->next = b;			//update adjacent links
			a->next->prev = b;
			b->prev->next = a;
			b->next->prev = a;
			cNode *tempPrev = a->prev;
			cNode *tempNext = a->next;
			a->prev = b->prev;			//update swaps' links
			a->next = b->next;
			b->prev = tempPrev;
			b->next = tempNext;
		}

	}
	return;
}

