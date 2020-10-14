/* Soren Madsen
 * Lab 6
 * 10 June 2018
 * Implements an ADT, SET, using a hashed array of generic types and functions to manipulate the SET.
 * QuickSorts the final list of elements in the getElements() function.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "set.h"

#define EMPTY	  0
#define FILLED	1
#define DELETED 2

struct set{
    int count;
    int length;
    void** elts;
    char* flags;
    int (*compare)();
    unsigned (*hash)();
};

 // Create Set
 // Big O of O(n)
 // Creates a set by initializing the variables and allocating memory
 // for those variables defined in the struct and returns the new SET.

SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()){
    SET *sp;
    sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->count = 0;
    sp->length = maxElts;
    sp->elts = malloc(sizeof(void*) * maxElts);
    sp->flags = malloc(sizeof(char) * maxElts);
    sp->compare = compare;
    sp->hash = hash;
    assert(sp->elts != NULL);
    assert(sp->flags != NULL);
    for(int i = 0; i < maxElts; i++)
        sp->flags[i] = EMPTY;
    return sp;
}

// Destroy Set
// Big O of O(n)
// Destroys the set passed through by freeing the allocated memory.

void destroySet(SET *sp){
    assert(sp != NULL);
    assert(sp->elts != NULL && sp->flags!=NULL);
    for(int i = 0; i < sp->length; i++){
        if(sp->flags[i] == FILLED)
	        free(sp->elts[i]);
    }
    free(sp->flags);
    free(sp->elts);
    free(sp);
}

// Number of Elements
// Big O of O(1)
// Returns the number of elements of sp.

int numElements(SET *sp){
    assert(sp != NULL);
    return sp->count;
}

// Search
// Expected Big O of O(1), Worst Case Big O of O(n)
// Returns the index of an element or where an element should be inserted.
// Also, it uses found to determine whether an element actually exists after the binary search.

static int search(SET *sp, void *elt, bool *found){
    assert(sp != NULL);
    assert(elt != NULL);
    int hash, idx = -1;
    *found = false;
    for (int probe = 0; probe < sp->length; probe++){
       hash = ((*sp->hash)(elt) + probe) % sp->length;
	     if(sp->flags[hash] == FILLED){
	         if((*sp->compare)(sp->elts[hash], elt) == 0){
               *found = true;
		           return hash;
	         }
	     }
	     else if(sp->flags[hash] == EMPTY){
	         if(idx != -1) return idx;
           else return hash;
	     }
	     else if(sp->flags[hash] == DELETED){
	        if(idx == -1) idx = hash;
       }
    }
    return idx;
}

// Add Element
// Expected Big O of O(1), Worst Case Big O of O(n)
// Adds an element to the array, if it does not already exist. It staggers all the following
// elements to maintain the sorted nature of the array

void addElement(SET *sp, void *elt){
    assert(sp != NULL && elt != NULL);
    bool found;
    int index = search(sp, elt, &found);
    if(sp->count == sp->length) return;
    if(found) return;
    sp->elts[index] = elt;
    sp->flags[index] = FILLED;
    sp->count++;
}

// Remove Element
// Expected Big O of O(1), Worst Case Big O of O(n)
// Removes an element from the array and staggers the elements to maintain the sorted nature

void removeElement(SET *sp, void *elt){
    assert(sp != NULL && elt != NULL);
    bool found;
    int index = search(sp, elt, &found);
    if(found){
	     sp->flags[index] = DELETED;
	     sp->count--;
    }
}

 // Find Element
 // Expected Big O of O(1), Worst Case Big O of O(n)
 // Finds and returns an element if found in the array

void *findElement(SET *sp, void *elt){
    assert(sp != NULL && elt != NULL);
    bool found;
    int index = search(sp, elt, &found);
    if(found)
      return sp->elts[index];
    return NULL;
}

 // QuickSort
 // Sorts an unsorted array using a recursive method
 // Complexity: O(nlog(n))

void quickSort(SET *sp, void **data, int lo, int hi){
    if(lo < hi){
        void *pivot =  data[(lo + hi) / 2];
        void *temp;
        int left = lo;
        int right = hi;

        // Swaps values around the center pivot
        while(left <= right){
            while((*sp->compare)(data[left], pivot) < 0) left++;
            while((*sp->compare)(data[right], pivot) > 0) right--;
            if(left <= right){
                temp = data[left];
                data[left++] = data[right];
                data[right--] = temp;
            }
        }

        // Recursively sorts the two halves
        quickSort(sp, data, lo, right);
        quickSort(sp, data, left, hi);
    }
}

 // Get Elements
 // Big O of O(n)
 // Returns the elements of the SET in a newly allocated array

void *getElements(SET *sp){
    void **copy;
    int i, j;
    assert(sp != NULL);
    copy = malloc(sizeof(void*)*sp->count);
    assert(copy != NULL);

    for(i = 0, j = 0; i < sp->length; i++){
    	 if(sp->flags[i]==FILLED)
	         copy[j++]=sp->elts[i];
    }

    quickSort(sp, copy, 0, sp->count - 1);

    return copy;
}
