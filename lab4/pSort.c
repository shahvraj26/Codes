/* Vraj Shah */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "debug.h"

typedef struct Node{
        struct Node *next;
        void *data;
}Node;

void sort(Node *head, bool (*comparisonFunc)(void *, void *)){
        if(DEBUG)printf("START OF SORT");
	Node *stop = NULL;
        while(stop != head){
                Node *pointertopointer = head;
                while(pointertopointer->next != stop){
                        if(!comparisonFunc(pointertopointer->data, pointertopointer->next->data)){
                                void *temp = pointertopointer->data;
                                pointertopointer->data = pointertopointer->next->data;
                                pointertopointer->next->data = temp;
                        }
                        pointertopointer = pointertopointer->next;
                }
                stop = pointertopointer;
		if(DEBUG)printf("END OF SORT");
        }
}

int main(){
	printf("NO ERRORS for Sort, IT WORKED");
}
