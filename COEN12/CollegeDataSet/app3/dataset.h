# ifndef DATASET_H
# define DATASET_H

typedef struct dataset DataSet;

extern DataSet *createDataSet(int (*compare)(), int (*getAge)(), int (*getID)());

extern void destroyDataSet(DataSet *lp);

extern int numItems(DataSet *lp);

extern void addLast(DataSet *lp, void *item);

extern void removeItem(DataSet *lp, int id);

extern void *searchID(DataSet *lp, int id);

extern void *searchAge(DataSet *lp, int age);

extern void *getItems(DataSet *lp);

extern void maxAgeGap(DataSet *lp);

# endif /* DATASET_H */
