#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "feature.h"
#include "f.h"

void getfeature(double * y, double * x, int x_size, int num_sample)
{
    if (x[0] > x[x_size - 1])
    {
        y[0] = x[0];
        y[1] = x[x_size - 1];
    } else
    {
        y[0] = x[x_size - 1];
        y[1] = x[0];
    }
    y[2] = x[0] + x[x_size - 1];    //mean
    y[3] = 0.0;     //std
    y[4] = 0.0;     //peakmaxnum
    y[5] = 0.0;     //peakminnum
    for (int i = 1; i < x_size - 1; ++i)
    {
        if (y[0] < x[i]) y[0] = x[i];
        if (y[1] > x[i]) y[1] = x[i];
        y[2] += x[i];
        if (x[i] > x[i - 1] && x[i] >= x[i + 1]) y[4]++;
        if (x[i] < x[i - 1] && x[i] <= x[i + 1]) y[5]++;
    }
    y[2] /= x_size;
    double tmp = 0.0;
    for (int i = 0; i < x_size; ++i)
        tmp += pow(x[i] - y[2], 2.0);
    y[3] = My_Sqrt(tmp / x_size);
    for (int i = 6; i < 6 + num_sample; ++i)
        y[i] = x[My_Div(My_Mul(x_size, i - 6), num_sample)];
}

void my_feature(double * feature, double * acclist, double * gyrolist, double * acclist_smoothed, double * gyrolist_smoothed, int list_size, int peakstep, int num_sample)
{
    double curpeakgyroval = gyrolist_smoothed[0];
    double curpeakaccval = acclist_smoothed[0];
    double peakspace = (double) list_size / peakstep;
    double peakdiffsquare = pow(gyrolist_smoothed[0] - gyrolist_smoothed[list_size], 2.0);
    const int featureUnit_size = 6 + num_sample;
    feature[0] = curpeakgyroval;
    feature[1] = curpeakaccval;
    feature[2] = peakspace;
    feature[3] = peakdiffsquare;
    getfeature(& feature[4], & gyrolist_smoothed[0], list_size, num_sample);
    getfeature(& feature[4 + featureUnit_size], & acclist_smoothed[0], list_size, num_sample);
    getfeature(& feature[4 + featureUnit_size * 2], & gyrolist[0], list_size, num_sample);
    getfeature(& feature[4 + featureUnit_size * 3], & acclist[0], list_size, num_sample);
}
