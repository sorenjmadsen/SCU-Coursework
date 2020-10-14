/* Soren Madsen
 * Application 3
 * 8 June 2018
 * Implements an ADT, DataSet, using a ciruclar doubly linked list of generic types
 * and functions to manipulate the DataSet.
*/
# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <stdbool.h>
# include "dataset.h"

struct dataset{
  int count;
  struct node *head;
  int (*compare)();
  int (*getAge)();
  int (*getID)();
};

struct node{
  void *data;
  struct node *next;
  struct node *prev;
};

 // Create DataSet
 // Allocates memory for a DataSet and initiaizes the sentinel node.
 // Complexity: O(1)

DataSet *createDataSet(int (*compare)(), int (*getAge)(), int (*getID)()){
  DataSet *lp;
  lp = malloc(sizeof(DataSet));
  assert(lp != NULL);

  lp->compare = compare;
  lp->getAge = getAge;
  lp->getID = getID;

  struct node *hp;
  hp = malloc(sizeof(struct node));
  assert(hp != NULL);
  hp->data = NULL;
  hp->next = hp;
  hp->prev = hp;

  lp->head = hp;

  return lp;
}

 // Destroy DataSet
 // Frees the memory allocated for the DataSet.
 // Complexity: O(n)

void destroyDataSet(DataSet *lp){
  assert(lp != NULL);
  struct node *pDel;
  pDel = lp->head->next;                // Skips over lp->head because it doesn't need to be freed yet

  struct node *pNext = pDel;            // Compiler warned that I should initialize the pointer of pNext
  while (pNext != lp->head){            // Using NULL meant that the while loop condition was not met
    pNext = pDel->next;
    free(pDel);
    pDel = pNext;
  }
  free(lp);
}

 // Number of Items
 // Returns how many items are in the DataSet.
 // Complexity: O(1)

int numItems(DataSet *lp){
  assert(lp != NULL);
  return lp->count;
}

 // Add Last
 // Adds an item to the end of the DataSet.
 // Complexity: O(1)

void addLast(DataSet *lp, void *item){
  assert(lp != NULL && item != NULL);
  struct node *toAdd;
  toAdd = malloc(sizeof(struct node));
  toAdd->data = item;

  lp->head->prev->next = toAdd;
  toAdd->next = lp->head;
  toAdd->prev = lp->head->prev;
  lp->head->prev = toAdd;

  lp->count++;
}

 // Remove Item
 // Removes an item from the DataSet, if it is contained in the DataSet.
 // Complexity: O(n)

void removeItem(DataSet *lp, int id){
  assert(lp != NULL);
  struct node *pTarg;

  printf("Attempting to remove sudent with ID: %d\n", id);

  pTarg = lp->head->next;
  while(pTarg != lp->head){
    if((*lp->compare)(pTarg->data, id) == 0){
      pTarg->prev->next = pTarg->next;
      pTarg->next->prev = pTarg->prev;
      free(pTarg);
      printf("Successfully removed.\n");
      return;
    }
    pTarg = pTarg->next;
  }
  printf("Failed to remove. Student not found.\n");
  return;
}

 // Search ID
 // Finds an item based on ID and returns it if it is found.
 // Complexity: O(n)

void *searchID(DataSet *lp, int id){
  assert(lp != NULL);
  struct node *pTarg;
  struct node *pHelp;

  printf("Searching for ID: %d\n", id);

  pTarg = lp->head->next;
  while(pTarg != lp->head){
    if((*lp->compare)(pTarg->data, id) == 0){
      printf("Found successfully.\n");
      return pTarg->data;
    }
    pHelp = pTarg->next;
    pTarg = pHelp;
  }
  printf("Failed to find.\n");
  return NULL;
}

 // Search Age
 // Finds an item based on age and returns the first occurence if it is found.
 // Complexity: O(n)

void *searchAge(DataSet *lp, int age){
  assert(lp != NULL);
  struct node *pTarg;
  struct node *pHelp;

  printf("Searching for Age: %d\n", age);

  pTarg = lp->head->next;
  while(pTarg != lp->head){
    if((*lp->getAge)(pTarg->data) == age){
      printf("Found successfully.\n");
      return pTarg->data;
    }
    pHelp = pTarg->next;
    pTarg = pHelp;
  }
  printf("Failed to find.\n");
  return NULL;
}

 // Get Items
 // Returns an array of all the items in the DataSet.
 // Complexity: O(n)

void *getItems(DataSet *lp){
  assert(lp != NULL);
  void **list;
  int track = 0;
  list = malloc(sizeof(void *) * lp->count);
  struct node *pTarg;

  pTarg = lp->head->next;
  while(pTarg != lp->head){
    list[track] = pTarg->data;
    pTarg = pTarg->next;
    track++;
  }
  return list;
}

 // Max Age Gap
 // Returns the maximum age gap of the student body
 // Complexity: O(n)

void maxAgeGap(DataSet *lp){
  assert(lp != NULL);
  void **elts = getItems(lp);
  int max = 0, min = 100;

  for(int i = 0; i < lp->count; i++){
    if((*lp->getAge)(elts[i]) > max) max = (*lp->getAge)(elts[i]);
    if((*lp->getAge)(elts[i]) < min) min = (*lp->getAge)(elts[i]);
  }

  int x = max - min;
  printf("Maximum Age Gap: %d\n", x);
}
