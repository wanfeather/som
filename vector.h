#ifndef VECTOR_H
#define VECTOR_H

typedef struct _vector Vec;

int get_Vec_len(Vec *);
Vec *new_Vec(int);
void Print_Vec(Vec *);
double Two_Norm(Vec *);
double Dot_Product(Vec *, Vec *);
void set_element(Vec *, int, double);
double get_element(Vec *, int);
void vec_addition(Vec *, Vec *, Vec *);
void vec_subtraction(Vec *, Vec *, Vec *);
void scaler_product(double, Vec *);
void delete_Vec(Vec *);

#endif
