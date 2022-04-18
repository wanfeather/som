#include"vector.h"
#include"som.h"

#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<math.h>

#define Data_Length 579
#define Num_Epoch 1250

int main()
{
    srand(time(NULL));

    FILE *fp;
    Vec **input;
    int counter_1, counter_2, data, max_index;
    double input_data[2];
    const double lr_init = 0.5, sigma_init = 1.0;
    double time_coe, lr, sigma, total_loss;
    SOM *model = new_Model(5, 5, 2);

    save_Weight(model, "weights_1.txt");

    fp = fopen("579.txt", "r");
    input = (Vec **)malloc(Data_Length * sizeof(Vec *));
    for(counter_1 = 0; counter_1 < Data_Length; counter_1++)
    {
        input[counter_1] = new_Vec(2);
        fscanf(fp, "%lf %lf %d\n", input_data, input_data + 1, &data);
        for(counter_2 = 0;counter_2 < 2; counter_2++)
            set_element(input[counter_1], counter_2, input_data[counter_2]);
    }
    fclose(fp);

    fp = fopen("loss.csv", "w");
    for(counter_1 = 0; counter_1 < Num_Epoch; counter_1++)
    {
        total_loss = 0.0;
	    time_coe = exp(-(double)counter_1/200);
        lr = lr_init * time_coe;
        sigma = sigma_init * time_coe;
        sigma = 2 * sigma * sigma;
        for(counter_2 = 0; counter_2 < Data_Length; counter_2++)
        {
            max_index = forward(model, input[counter_2]);
            total_loss += update(model, input[counter_2], max_index, lr, sigma);
        }
        fprintf(fp, "%d,%lf\n", counter_1, total_loss);
    }
    fclose(fp);

    save_Weight(model, "weights_end.txt");

    for(counter_1 = 0; counter_1 < Data_Length; counter_1++)
        delete_Vec(input[counter_1]);
    free(input);
    delete_Model(model);

    return 0;
}
