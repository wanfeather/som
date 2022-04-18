#include"vector.h"

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct _vector
{
    int length;
    double *element;
};


int get_Vec_len(Vec *v)
{
    return v->length;
}

Vec *new_Vec(int len)
{
    int counter;
    Vec *v = (Vec *)malloc(sizeof(Vec));

    v->length = len;
    v->element = (double *)malloc(len * sizeof(double));

    for(counter = 0; counter < len; counter++)
        v->element[counter] = 1.0;
    
    return v;
}

void Print_Vec(Vec *v)
{
    int counter;

    for(counter = 0; counter < v->length; counter++)
        printf("%lf\t", v->element[counter]);
    printf("\n");
}

double Two_Norm(Vec *v)
{
    int counter;
    double sum = 0.0;

    for(counter = 0; counter < v->length; counter++)
        sum += v->element[counter] * v->element[counter];
    sum = sqrt(sum);

    return sum;
}

double Dot_Product(Vec *v1, Vec *v2)
{
    int counter;
    double sum = 0.0;

    for(counter = 0; counter < v1->length; counter++)
        sum += v1->element[counter] * v2->element[counter];

    return sum;
}

void set_element(Vec *v, int index, double value)
{
    v->element[index] = value;
}

double get_element(Vec *v, int index)
{
    return v->element[index];
}

void vec_addition(Vec *output, Vec *v1, Vec *v2)
{
    int counter;

    for(counter = 0; counter < output->length; counter++)
        output->element[counter] = v1->element[counter] + v2->element[counter];
}

void vec_subtraction(Vec *output, Vec *v1, Vec *v2)
{
    int counter;

    for(counter = 0; counter < output->length; counter++)
        output->element[counter] = v1->element[counter] - v2->element[counter];
}

void scaler_product(double value, Vec *v)
{
    int counter;

    for(counter = 0; counter < v->length; counter++)
        v->element[counter] *= value;
}

void delete_Vec(Vec *v)
{
    free(v->element);
    free(v);
}
