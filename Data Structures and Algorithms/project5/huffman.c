/* 
 * Soren Madsen
 * Lab 5
 * COEN 12
 * 3 June 2018
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pqueue.h"
#include <assert.h>
#include "pack.h"
#define NODE struct node
#define MAX_SIZE 256 

 // Global arrays used in the creation of the Huffman tree
int charcount[MAX_SIZE + 1];
struct node *nodes[MAX_SIZE + 1];

 // Node Compare: a compare function used to organize the priority queue
 // Complexity: O(1)
int nCompare(struct node *np1, struct node *np2){
	assert(np1 != NULL && np2 != NULL);
	return (np1->count < np2->count) ? -1 : (np1->count > np2->count);
}

 // Make Node: creates a NODE and organizes any subtrees
 // Complexity: O(1) 
NODE *makeNode(int x, NODE *leftC, NODE *rightC){
	NODE *np;

	np = malloc(sizeof(NODE));
	assert(np != NULL);

	np->count = x;

	if(leftC)
		leftC->parent = np;
	if(rightC)
		rightC->parent = np;

	return np;
}

 // Depth: Returns how many levels below the head of the tree a node exists.
 // Complexity: O(log(n))
int depth(NODE *target){
	assert(target != NULL);
	int count = 0;
	while(target->parent != NULL){
		target = target->parent;
		count++;
	}
	return count;
}

int isPrint(int c){
	if(c > 30 && c < 127) return true;
	return false;
}

int main(int argc, char *argv[])
{
	FILE *ifp;
	struct pqueue *pq;
	int c = 0;											// Uses an int because getc() returns an int
	int d;
	NODE *leftD, *rightD;

	if(argc != 3){									// Checks that two arguments are inputed
		printf("Two input files needed.\n");
		exit(EXIT_FAILURE);
	}
	if((ifp = fopen(argv[1], "rb")) == NULL){		// Checks that the file opens correctly
		printf("Cannot open file.\n");
		exit(EXIT_FAILURE);
	}
	else
		printf("Input file opened successfully.\n");
	
	pq = createQueue(nCompare);					// Call createQueue from pqueue.h to initalize using nCompare

	for(int i = 0; i < MAX_SIZE + 1; i++){		// Initialize the arrays
		charcount[i] = 0;
		nodes[i] = NULL;
	}

 // Get character counts
	while(c != EOF) {							
		c = getc(ifp);
		charcount[c]++;
	}

 // Create leaves
	for(int i = 0; i < 257; i++){
		if(charcount[i] > 0){
			nodes[i] = makeNode(charcount[i], NULL, NULL);
			addEntry(pq, nodes[i]);
		}
	}
	nodes[256] = makeNode(0, NULL, NULL);		// Assign the last node to be the end of file
	addEntry(pq, nodes[256]);

 // Build the Huffman tree
	while(numEntries(pq) > 1){
		leftD = removeEntry(pq);
		rightD = removeEntry(pq);
		addEntry(pq, makeNode(leftD->count + rightD->count,leftD, rightD));
	}

 // Print the characters and their respective occupation of memory
 // When the first print statement is not commented out, there is a segmentation fault.
 // I have been unable to find the source of the error.
	for(int i = 0; i < MAX_SIZE + 1; i++){
		if(nodes[i] != NULL){
			d = depth(nodes[i]);
			printf(isPrint(i) ? "'%c'" : "%03o", i);
			printf(": %d x %d bits = %d bits\n", charcount[i], d, d * charcount[i]);
		}
	}


 // Packs the nodes and codes the compressed file
	pack(argv[1], argv[2], nodes);
}
	






	