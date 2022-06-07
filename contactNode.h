/*
 * node.h
 *
 *  Created on: Nov 28, 2017
 *      Author: greg
 */

#ifndef CONTACTNODE_H_
#define CONTACTNODE_H_

/*
 * Structure definition of a contact node
 */
typedef struct contactNode {
	char *raw, *fName, *lName, *email, *phone;	//fields for data

	struct contactNode *prev, *next;	//pointers to previous or next contacts

} cNode;


/*
 * Create a new node out of a data string
 */
cNode *createContact(char *data);

/*
 * Delete a contact node
 */
void deleteContact(cNode *node);

void editContactNode(cNode *node, char field, char *data);

#endif /* CONTACTNODE_H_ */
