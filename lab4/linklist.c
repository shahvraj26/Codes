/* Vraj Shah */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "altmem.h"

#include "debug.h"

#include "linklist.h"

typedef struct Node{
        struct Node *next;
        void *data;
}Node;

/* Allocates for each node in the linked list */
static Node *allocate_node(void *data) {
	//Using aalternative_malloc get the malloc of the Node
	Node *node = (Node *)alternative_malloc(sizeof(Node));
    	static int allocations = 0;
	if (node != NULL) {
		//Allocate
        	allocations++;
		if(TEXT)printf("DIAGNOSTIC: %d nodes allocated\n", allocations);

    	} 
	else {
        	if(TEXT)printf("ERROR: linklist.c: Failed to malloc a node.\n");
    	}
    	return node;
} 

/* Frees node in the linked list */
static void free_node(Node *node) {
	static int freed = 0;
    	if (node != NULL) {
        	freed++;
        	//Free with alternative free
		alternative_free(node);
		if(TEXT)printf("DIAGNOSTIC: %d nodes freed\n", freed);
    	} 
	else {
        	if(TEXT)printf("ERROR: Attempted to free null node.\n");
    	}
}

/* Iterate function for linked list */
void iterate(void *head , void (*actionFunc)(void *)){
	Node *current = head;
	while (current != NULL){
		//Run the specific action function based on program
		actionFunc(current->data);
		//Iterate to next node
		current = current->next;
	}
}

/* Insert function for linked list, Returns a boolean value */
bool insert(void *head, void *data, bool (*comparisonFunc)(void *, void *), int text){
	bool results = true;
	//Allocate the new node
	Node *new_node = allocate_node(data);
	//If node is null return false
	if(new_node == NULL){
		results = false;
	}else{
		//Make sure next node is Null, and data is pointed to specific data
		new_node->next = NULL;	
		new_node->data = data;
		Node **pointerToPointer = head;
		while (*pointerToPointer != NULL && !comparisonFunc(new_node->data, (*pointerToPointer)->data)){
			//set pointerToPointer to the address of the pointer in the next node
			pointerToPointer = &(*pointerToPointer)->next;
		}
		//insert into next
		new_node->next = *pointerToPointer;
    		*pointerToPointer = new_node;
	}
	//return the result
	return results;
}

/* Delete Some function for linked list */
int deleteSome(void *head, bool (*criteriaFunc)(void *), void (*actionFunc)(void *), int text){
	int count = 0;
	Node **pointertopointer = head;
	while (*pointertopointer != NULL){
		Node *holder = *pointertopointer;
		//if Criteriafunction is true
		if(criteriaFunc(holder->data)){
			//Do the specific action function
			actionFunc(holder->data);
			*pointertopointer = holder->next;
			//Free the node
			free_node(holder);
			count++;
		} else{
			pointertopointer = &(*pointertopointer)->next;
		}
	}
	//Return the amount deleted
	return count;
}

/* Sort function for linked list */
void sort(void *head, bool (*comparisonFunc)(void *, void *)){
	Node *stop = NULL;
	while(stop != head){
		Node *pointertopointer = head;
		while(pointertopointer->next != stop){
			//if the comparison function is not qualified to each other
			if(comparisonFunc(pointertopointer->next->data, pointertopointer->data)){
				//create a temp value that points to data
				void *temp = pointertopointer->data;
				//the data value is equal to the data value in the next node
				pointertopointer->data = pointertopointer->next->data;
				//set the next node data value to temp
				pointertopointer->next->data = temp;
			}
			pointertopointer = pointertopointer->next;	
		}
		stop = pointertopointer;
	}
}
