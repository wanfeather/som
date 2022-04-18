#include"som.h"

#include<stdlib.h>
#include<stdio.h>
#include<float.h>
#include<math.h>

struct _som
{
    int row, col;
    Vec **weight;
};


SOM *new_Model(int r, int c, int l)
{
    SOM *model = (SOM *)malloc(sizeof(SOM));
    int counter_1, counter_2;

    model->row = r;
    model->col = c;
    model->weight = (Vec **)malloc(r * c * sizeof(Vec *));

    for(counter_1 = 0; counter_1 < r*c; counter_1++)
    {
        model->weight[counter_1] = new_Vec(l);
        for(counter_2 = 0; counter_2 < l; counter_2++)
            set_element(model->weight[counter_1], counter_2, 6*(rand()/(RAND_MAX+1.0)) -1);
    }

    return model;
}

void Print_SOM(SOM *model)
{
    int counter;

    for(counter = 0; counter < model->row*model->col; counter++)
        Print_Vec(model->weight[counter]);
}

int forward(SOM *model, Vec *data)
{
    int counter, min_index;
    double min = DBL_MAX, value;
    Vec *temp = new_Vec(get_Vec_len(data));

    for(counter = 0; counter < model->row*model->col; counter++)
    {
        vec_subtraction(temp, model->weight[counter], data);
        value = Two_Norm(temp);
        if(value < min)
        {
            min_index = counter;
            min = value;
        }
    }

    return min_index;
}

double update(SOM *model, Vec *data, int max_index, double lr, double sigma)
{
    int counter, len = model->row * model->col;
    int max_row = max_index / model->col, max_col = max_index % model->col;
    double distance, loss = 0.0;
    Vec *temp = new_Vec(get_Vec_len(data));

    for(counter = 0; counter < len; counter++)
    {
        vec_subtraction(temp, data, model->weight[counter]);
        distance = (double)abs(max_row - counter / model->col) + (double)abs(max_col - counter % model->col);
        distance = distance * distance;
        distance /= sigma;
        distance = exp(-distance);
        distance *= lr;
        scaler_product(distance, temp);
        loss += Two_Norm(temp);
        vec_addition(model->weight[counter], model->weight[counter], temp);
    }

    free(temp);

    return loss;
}

void save_Weight(SOM *model, char *file_name)
{
    int counter_1, counter_2;
    FILE *fp = fopen(file_name, "w");

    //fprintf(fp, "%d %d\n", model->row, model->col);
    for(counter_1 = 0; counter_1 < model->row*model->col; counter_1++)
    {
	fprintf(fp, "%d ", counter_1);
        for(counter_2 = 0; counter_2 < get_Vec_len(model->weight[counter_1]); counter_2++)
            fprintf(fp, "%lf ", get_element(model->weight[counter_1], counter_2));
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void delete_Model(SOM *model)
{
    int counter;

    for(counter = 0; counter < model->row*model->col; counter++)
        delete_Vec(model->weight[counter]);
    free(model->weight);
    free(model);
}
