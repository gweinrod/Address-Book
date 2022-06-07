/*
 * node.c
 *
 *  Created on: Nov 28, 2017
 *      Author: greg
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contactNode.h"
#include "util.h"

/*
 * Create a new node
 */
cNode *createContact(char *data) {

	cNode *newNode = (cNode *) malloc(sizeof(cNode));
	char *open, *close;

	newNode->raw = malloc((strlen(data)) * sizeof(char));
	strcpy(newNode->raw, data);
	trim(newNode->raw);

	open = data;
	close = strstr(open, ",");
	newNode->lName = malloc((close - open + 1) * sizeof(char));
	strncpy(newNode->lName, open, close - open);
	trim(newNode->lName);

	open = close + 1;
	close = strstr(open, ",");
	newNode->fName = malloc((close - open + 1) * sizeof(char));
	strncpy(newNode->fName, open, close - open);
	trim(newNode->fName);

	open = close + 1;
	close = strstr(open, ",");
	newNode->email = malloc((close - open + 1) * sizeof(char));
	strncpy(newNode->email, open, close - open);
	trim(newNode->email);

	open = close + 1;
	close = strstr(open, "\n");
	newNode->phone = malloc((close - open + 1) * sizeof(char));
	strncpy(newNode->phone, open, close - open);
	trim(newNode->phone);

	newNode->prev = NULL;
	newNode->next = NULL;

	return newNode;
}

/*
 * Delete a contact node
 */
void deleteContact(cNode *node) {
	free(node->fName);
	free(node->lName);
	free(node->email);
	free(node->phone);
	free(node);
	return;
}

/*
 * Edit a contact
 */
void editContactNode(cNode *node, char field, char *data) {
	switch (field) {
	case 'l':
	case 'L':
		free(node->lName);
		node->lName = malloc(strlen(data) * sizeof(char));
		strcpy(node->lName, data);
		break;
	case 'f':
	case 'F':
		free(node->fName);
		node->fName = malloc(strlen(data) * sizeof(char));
		strcpy(node->fName, data);
		break;
	case 'e':
	case 'E':
		free(node->email);
		node->email = malloc(strlen(data) * sizeof(char));
		strcpy(node->email, data);
		break;
	case 'p':
	case 'P':
		free(node->phone);
		node->phone = malloc(strlen(data) * sizeof(char));
		strcpy(node->phone, data);
		break;
	default:
		break;
	}
	return;
}
