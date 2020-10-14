# ifndef DATASET_H
# define DATASET_H

typedef struct dataset DataSet;

extern DataSet *createDataSet(int (*getID)(), int maxElts);

extern void destroyDataSet(DataSet *sp);

extern int numItems(DataSet *sp);

extern void addElt(DataSet *sp, void *item);

extern void removeElt(DataSet *sp, int id);

extern void *searchID(DataSet *sp, int id);

extern void *getItems(DataSet *sp);

# endif /* DataSet_H */
