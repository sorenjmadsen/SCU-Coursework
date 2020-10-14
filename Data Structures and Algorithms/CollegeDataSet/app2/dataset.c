/* Soren Madsen
 * Application 2
 * 8 June 2018
 * Implements an ADT, DataSet, using a ciruclar doubly linked DataSet of generic types
 * and functions to manipulate the DataSet.
*/
# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <stdbool.h>
# include "dataset.h"

struct dataset
{
  int count;
  int maxCapacity;
  int (*getID)();
  void **elts;
};

 // Create DataSet
 // Allocates memory for a DataSet and initiaizes the array.
 // Complexity: O(1)

DataSet *createDataSet(int (*getID)(), int maxElts)
{
  DataSet *sp;
  sp= malloc(sizeof(DataSet));
  assert(sp != NULL);

  sp->count = 0;
  sp->maxCapacity = maxElts;
  sp->elts = malloc(sizeof(void *) * maxElts);
  sp->getID = getID;

  return sp;
}

 // Destroy DataSet
 // Frees the memory allocated for the DataSet.
 // Complexity: O(m)

void destroyDataSet(DataSet *sp)
{
  assert(sp != NULL);
  assert(sp->elts != NULL);

  for(int i = 0; i < sp->maxCapacity; i++)
  {
    if(sp->elts[i]) free(sp->elts[i]);
  }
  free(sp->elts);
  free(sp);
}

 // Number of Items
 // Returns how many items are in the DataSet.
 // Complexity: O(1)

int numItems(DataSet *sp)
{
  assert(sp != NULL);
  return sp->count;
}

 // Add Item
 // Adds an item to the DataSet.
 // Complexity: O(1)

void addElt(DataSet *sp, void *item)
{
  assert(sp != NULL && item != NULL);
  int i = (*sp->getID)(item);
  if(!sp->elts[i])
  {
    sp->elts[i] = item;
  }
  else printf("Student ID: %d already exists. Try another ID.", i);
  sp->count++;
}

 // Remove Item
 // Removes an item from the DataSet, if it is contained in the DataSet.
 // Complexity: O(1)

void removeElt(DataSet *sp, int id)
{
  assert(sp != NULL);

  printf("Attempting to remove sudent with ID: %d\n", id);

  if(sp->elts[id])
  {
    printf("Student successfully removed.\n");
    sp->elts[id] = NULL;                    // Freeing the spot in memory didn't work so setting to NULL was the solution
    sp->count--;
    return;
  }

  printf("Failed to remove. Student not found.\n");
  return;
}

 // Search ID
 // Finds an item based on ID and returns it if it is found.
 // Complexity: O(1)

void *searchID(DataSet *sp, int id)
{
  assert(sp != NULL);

  printf("Searching for ID: %d\n", id);

  if(id < sp->maxCapacity)
  {
    if(sp->elts[id] != NULL)
    {
      printf("Found successfully.\n");
      return sp->elts[id];
    } 
  }

  printf("Failed to find.\n");
  return NULL;
}

 // Get Items
 // Returns an array of all the items in the DataSet.
 // Complexity: O(m)

void *getItems(DataSet *sp){
  assert(sp != NULL);
  void **list;
  int track = 0;
  list = malloc(sizeof(void *) * sp->count);

  for(int i = 0; i < sp->maxCapacity; i++)
  {
    if(sp->elts[i] != NULL) list[track++] = sp->elts[i];
  }

  return list;
}