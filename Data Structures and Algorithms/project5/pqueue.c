/* Soren Madsen
 * Lab 5
 * COEN 12
 * 3 June 2018
 */

# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include "pqueue.h"

# define PARENT(i)	((i - 1) / 2)
# define LEFTC(i)	((i * 2) + 1)
# define RIGHTC(i)	((i * 2) + 2)

struct pqueue{
	int count;
	int length;
	void **data;
	int(* compare)();
};

PQ *createQueue(int (*compare)()){
	PQ *pq;
	pq = malloc(sizeof(PQ));
	assert(pq != NULL);

	pq->count = 0;
	pq->length = 10;
	pq->compare = compare;

	pq->data = malloc(sizeof(void*) * 10);
	assert(pq->data != NULL);

	return pq;
}

void destroyQueue(PQ *pq){
	assert(pq != NULL);
	for(int i = 0; i < pq->count; i++){
		free(pq->data[i]);
	}
	free(pq->data);
	free(pq);
}

int numEntries(PQ *pq){
	assert(pq != NULL);
	return pq->count;
}

void addEntry(PQ *pq, void *entry){
	int index;
	void *help;

	assert(pq != NULL && entry != NULL);

	if(pq->count == pq->length){
		pq->data = realloc(pq->data, sizeof(void *) * pq->length * 2);
		pq->length *= 2;
	}

	index = pq->count;
	pq->data[index] = entry;
	while(PARENT(index) != index){
		if((*pq->compare)(pq->data[PARENT(index)], pq->data[index]) > 0){
			help = pq->data[index];
			pq->data[index] = pq->data[PARENT(index)];
			pq->data[PARENT(index)] = help;
			index = PARENT(index);
		} else {
			break;
		}
	}
	pq->count++;
}

void *removeEntry(PQ *pq){
	assert(pq != NULL);
	if(pq->count == 0) return NULL;

	int root = 0;
	void *value;
	value = pq->data[0];

	void *help;
	pq->data[0] = pq->data[pq->count - 1];

	pq->count--;

	while(LEFTC(root) < pq->count){

		// Root has two children
		if(RIGHTC(root) < pq->count){

			// Swaps with LEFTC if LEFTC is the smaller value
			if((*pq->compare)(pq->data[LEFTC(root)], pq->data[RIGHTC(root)]) < 0){
				// Swaps only if the root is greater than LEFTC
				if((*pq->compare)(pq->data[root], pq->data[LEFTC(root)]) > 0){
					help = pq->data[root];
					pq->data[root] = pq->data[LEFTC(root)];
					pq->data[LEFTC(root)] = help;
					root = LEFTC(root);
				} else {
					break;
				}
			} 

			// Swaps with RIGHTC if LEFTC is the larger value
			else {
				// Swaps only if the root is greater than RIGHTC
				if((*pq->compare)(pq->data[root], pq->data[RIGHTC(root)]) > 0){
					help = pq->data[root];
					pq->data[root] = pq->data[RIGHTC(root)];
					pq->data[RIGHTC(root)] = help;
					root = RIGHTC(root);
				} else {
					break;
				}
			}
		}

		// Root has one child

		else {
			// Swaps only if the root is greater than LEFTC
			if((*pq->compare)(pq->data[root], pq->data[LEFTC(root)]) > 0){
				help = pq->data[root];
				pq->data[root] = pq->data[LEFTC(root)];
				pq->data[LEFTC(root)] = help;
				root = LEFTC(root);
			} else {
				break;
			} 
		}
	}
	
	return value;
}