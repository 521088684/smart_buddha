#include <stdio.h>
#include "predict.h"

int my_predict(double * feature, int f_size, double * model, double thredshold)
{
    int label;

    double sum = 0.0;
    for (int i = 0; i < f_size; i++)
    {
        sum += model[i] * feature[i];
    }
    if (sum >= thredshold)
        label = 1;
    else
        label = 0;

    return label;
}
