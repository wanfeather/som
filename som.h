#ifndef SOM_H
#define SOM_H

#include"vector.h"

typedef struct _som SOM;

SOM *new_Model(int, int, int);
void Print_SOM(SOM *);
int forward(SOM *, Vec *);
double update(SOM *, Vec *, int, double, double);
void save_Weight(SOM *, char *);
void delete_Model(SOM *);

#endif
