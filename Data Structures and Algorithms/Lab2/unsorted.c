/*
    Soren Madsen
    LAB 2
    22 April 2018
    Implements an ADT, SET, for an unsorted array of strings and uses functions to manipulate
    this array.
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "set.h"

struct set{
    int eltCount;
    int maxCapacity;
    char **eltList;
};

 // Create Set
 // Big O of O(n)
 // Creates a set by initializing the variables and allocating memory
 // for those variables defined in the struct and returns the new SET.

SET *createSet(int maxElts){
    SET *sp;
    sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->eltCount = 0;
    sp->maxCapacity = maxElts;
    sp->eltList = malloc(sizeof(char*) * maxElts);
    assert(sp->eltList != NULL);
    return sp;
}

 // Destroy Set
 // Big O of O(n)
 // Destroys the set passed through by freeing the allocated memory.

void destroySet(SET *sp){
    assert(sp != NULL);
    assert(sp->eltList != NULL);
    for(int i = 0; i < sp->eltCount; i++){
	free(sp->eltList[i]);
    }
    free(sp->eltList);
    free(sp);
}

 // Number of Elements
 // Big O of O(1)
 // Returns the number of elements of sp.

int numElements(SET *sp){
    assert(sp != NULL);
    return sp->eltCount;
}

 // Sequestial Search
 // Big O of O(n)
 // Searches for an element and returns a valid index if found.

static int search(SET *sp, char *elt){
    for(int i = 0; i < sp->eltCount; i++){
	if(strcmp(elt, sp->eltList[i]) == 0) return i;
    }
    return -1;
}

 // Add Element
 // Big O of O(1)
 // Adds an element to the array.

void addElement(SET *sp, char *elt){
    assert(sp != NULL && elt != NULL);
    if(sp->eltCount == sp->maxCapacity) return;
    if(search(sp, elt) >= 0) return;
    sp->eltList[sp->eltCount++] = strdup(elt);
}

 // Remove Element
 // Big O of O(1)
 // Removes an element from the array.

void removeElement(SET *sp, char *elt){
    assert(sp != NULL && elt != NULL);
    int i = search(sp, elt);
    if(i >= 0){
	free(sp->eltList[i]);
	sp->eltList[i] = sp->eltList[sp->eltCount - 1];
    	sp->eltCount--;
    }
}

 // Find Element
 // Big O of O(n)
 // Finds an element in the array and returns the element if found.

char *findElement(SET *sp, char *elt){
    assert(sp != NULL && elt != NULL);
    int i = search(sp, elt);
    if(i == -1) return NULL;
    return sp->eltList[i];
}

 // Get Elements
 // Big O of O(n)
 // Allocates memory for a new array and returns a copy of the SET's array made to that allocation.

char **getElements(SET *sp){
  assert(sp != NULL);
  char** hold = malloc(sizeof(char*)*sp->eltCount);
  assert(hold != NULL);
  return memcpy(hold, sp->eltList, sizeof(char*)*sp->eltCount);
}
