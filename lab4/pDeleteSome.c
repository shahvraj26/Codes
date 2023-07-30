/* Vraj Shah */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "debug.h"

typedef struct Node{
        struct Node *next;
        void *data;
}Node;

/* Frees node in the linked list */
static void free_node(Node *node) {
        static int freed = 0;
        if (node != NULL) {
                freed++;
                free(node);
                //if(TEXT)printf("Unable to insert into in-play list\n");
                if(TEXT)printf("DIAGNOSTIC: %d nodes freed\n", freed);
        }
        else {
                if(TEXT)printf("ERROR: Attempted to free null node.\n");
        }
}

int deleteSome(Node *head, bool (*criteriaFunc)(void *), void (*actionFunc)(void *)){
	if(DEBUG)printf("START OF DELETESOME");
        int count = 0;
        Node **pointertopointer = (Node **)head;
        while (*pointertopointer != NULL){
                Node *holder = *pointertopointer;
                if(criteriaFunc(holder->data)){
                        actionFunc(holder->data);
                        *pointertopointer = holder->next;
                        free_node(holder);
                        count++;
                } else{
                        pointertopointer = &(*pointertopointer)->next;
                }
        }
        return count;
	if(DEBUG)printf("%d count: END OF DELETESOME", count);
}

int main(){
	printf("NO ERRORS for deleteSome, IT WORKED");
}

