/* Vraj Shah */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "debug.h"

typedef struct Node{
        struct Node *next;
        void *data;
}Node;

/* Allocates for each node in the linked list */
static Node *allocate_node(void *data) {
        Node *node = (Node *)malloc(sizeof(Node));
        static int allocations = 0;
        if (node != NULL) {
                allocations++;
                if(TEXT)printf("DIAGNOSTIC: %d nodes allocated\n", allocations);

        }
        else {
                if(TEXT)printf("ERROR: linklist.c: Failed to malloc a node.\n");
        }
        return node;
}

bool insert(Node **head, void *data, bool (*comparisonFunc)(void *, void *)){
	if(DEBUG)printf("START OF INSERT");
        bool results = true;
        Node *new_node = allocate_node(data);
        if(new_node == NULL){
                results = false;
        }else{
                new_node->next = NULL;
                new_node->data = data;
                Node **pointerToPointer = (Node **)head;
                while (*pointerToPointer != NULL && comparisonFunc((*pointerToPointer)->data, new_node->data)){
                        pointerToPointer = &(*pointerToPointer)->next;
                }
                new_node->next = *pointerToPointer;
                *pointerToPointer = new_node;
        }
        return results;
	if(DEBUG)printf("Result: END OF INSERT");
}

int main(){
	printf("NO ERRORS for Insert, IT WORKED");
}

