/*
    Soren Madsen
    LAB 2
    22 April 2018
    Implements an ADT, SET, for a list of sorted strings and functions that manipulate the SET.
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

 // Search
 // Big O of O(log(n))
 // Returns the index of an element or where an element should be inserted.
 // Also, it uses found to determine whether an element actually exists after the binary search.

static int search(SET *sp, char *elt, bool *found){
    int lo, hi, mid;
    lo = 0;
    hi = sp->eltCount - 1;
    while (lo <= hi){
	mid = (lo + hi)/ 2;
	if(strcmp(elt,sp->eltList[mid]) < 0) hi = mid - 1;
	else if(strcmp(elt,sp->eltList[mid]) > 0) lo = mid + 1;
	else{
	    *found = true;
	    return mid;
	}
    }
    return lo;
}

 // Add Element
 // Big O of O(n)
 // Adds an element to the array, if it does not already exist. It staggers all the following
 // elements to maintain the sorted nature of the array

void addElement(SET *sp, char *elt){
    assert(sp != NULL && elt != NULL);
    bool found = false;
    int idx = search(sp, elt, &found);
    if(sp->eltCount == sp->maxCapacity) return;
    if(found) return;
    for(int i = sp->eltCount; i > idx; i--){
	sp->eltList[i] = sp->eltList[i - 1];
    }
    sp->eltList[idx] = strdup(elt);
    sp->eltCount++;
}

 // Remove Element
 // Big O of O(n)
 // Removes an element from the array and staggers the elements to maintain the sorted nature

void removeElement(SET *sp, char *elt){
    assert(sp != NULL && elt != NULL);
    bool found = false;
    int i = search(sp, elt, &found);
    if(i >= 0 && found){
	free(sp->eltList[i]);
	for(int j = i + 1; j < sp->eltCount; j++){
	     sp->eltList[j-1] = sp->eltList[j];
	}
	sp->eltCount--;
    }
}

 // Find Element
 // Big O of O(log(n))
 // Finds and returns an element if found in the array

char *findElement(SET *sp, char *elt){
    assert(sp != NULL && elt != NULL);
    bool found = false;
    int i = search(sp, elt, &found);
    if(!found) return NULL;
    return sp->eltList[i];
}

 // Get Elements
 // Big O of O(n)
 // Returns the elements of the SET in a newly allocated array

char **getElements(SET *sp){
    assert(sp != NULL);
    char** hold = malloc(sizeof(char*)*sp->eltCount);
    assert(hold != NULL);
    return memcpy(hold, sp->eltList, sizeof(char*)*sp->eltCount);
}
