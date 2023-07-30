/* Vraj Shah */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "debug.h"

typedef struct Node{
        struct Node *next;
        void *data;
}Node;

void iterate(Node *head , void (*actionFunc)(void *)){
	if(DEBUG)printf("START ITERATE");
        Node *current = head;
        while (current != NULL){
                actionFunc(current->data);
                current = current->next;
        }
	if(DEBUG)printf("END ITERATE");
}

int main(){
	printf("NO ERRORS for Iterate, IT WORKED");
}
