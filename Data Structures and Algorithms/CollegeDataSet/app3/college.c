/* Soren Madsen
 * Application 3
 * 8 June 2018
 * Completes the steps outlined in Application 3
*/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <math.h>
# include <assert.h>
# include <time.h>
# include "dataset.h"

 // Random Number Generator
 // Generates a random number between 1 and 2
 // Complexity: O(1)

int randNumGen(){
  return 1 + (rand() % 2);
}

struct student{
  int id;
  int age;
};

 // Create Student
 // Creates a student data type that stores ID and Age.
 // Complexity: O(1)

struct student *createStudent(int id, int age){
  struct student *stP;
  stP = malloc(sizeof(struct student));
  assert(stP != NULL);
  stP->id = id;
  stP->age = age;

  return stP;
};

 // Get Age
 // Returns the age of a student
 // Complexity: O(1)

int getAge(struct student *sp){
  assert(sp != NULL);
  return sp->age;
}

 // Get ID
 // Returns the ID of the student
 // Complexity: O(1)

int getID(struct student *sp){
  assert(sp != NULL);
  return sp->id;
}

 // Student Compare
 // Compares students by their ID
 // Complexity: O(1)

int studentCompareID(struct student *sp1, int id){
  assert(sp1 != NULL);
  return (sp1->id < id) ? -1 : (sp1->id > id);
}

 // Main Function
 // Completes the steps outlined for Application 3

int main(int argc, char const *argv[]) {

  // Creates the DataSet
  DataSet *app3;
  app3 = createDataSet(studentCompareID, getAge, getID);

  // Generates student IDs and the ages and inserts the students in the list
  int age, id = 0;
  srand(time(0));

  for(int i = 0; i < 1000; i++){
    age = 18 + (rand() % 13);
    id += randNumGen();
    addLast(app3, createStudent(id, age));
  }

  // Finds the maximum age gap for the student body
  maxAgeGap(app3);

  // Creates a random student ID and attempts to remove that record based on the ID.
  int randID = rand() % 2000;
  if(searchID(app3, randID))
    removeItem(app3, randID);
  else
    printf("Cannot be removed. \n");

  // Destroys the list
  destroyDataSet(app3);

  return 0;
}
