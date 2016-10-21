#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "feature.h"
#include "butter.h"
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

void my_feature(double * feature, int f_size, double * acclist, double * gyrolist, int w_size, double frequency)
{
    printf("%d\n", f_size);
    double * acclist_smoothed = (double *) malloc (My_Mul(w_size, sizeof(double)));;
    double * gyrolist_smoothed = (double *) malloc (My_Mul(w_size, sizeof(double)));;

    double a[ORDER + 1] = {0.0};
    double b[ORDER + 1] = {0.0};
    butter_lowpass(b, a, CUTOFF, frequency, ORDER);

    lfilter(acclist_smoothed, acclist, w_size, a, b, ORDER + 1);
    lfilter(gyrolist_smoothed, gyrolist, w_size, a, b, ORDER + 1);
    bool * peakLabel = (bool *) malloc (My_Mul(w_size, sizeof(double)));
    int peakCount = mark_peak(peakLabel, gyrolist_smoothed, w_size);
    //if (peanCount <= 10)
    //  return NULL;
    int * peaks = (int *) malloc (My_Mul(peakCount, sizeof(int)));
    int index_tmp = 0;
    for (int i = 0; i < w_size; ++i)
        if (peakLabel[i])
            peaks[index_tmp++] = i;
    for (int i = 0; i < peakCount - PEAKSTEP + 1; ++i)
    {
        double curpeakgyroval = gyrolist_smoothed[peaks[i]];
        double curpeakaccval = acclist_smoothed[peaks[i]];
        double peakspace = (peaks[i + PEAKSTEP] - peaks[i]) / PEAKSTEP;
        double peakdiffsquare = pow(gyrolist_smoothed[peaks[i]] - gyrolist_smoothed[peaks[i + PEAKSTEP]], 2.0);
        int indexstart = peaks[i];
        int indexend = peaks[i + PEAKSTEP];
        const int featureUnit_size = 6 + NUM_SAMPLE;
        feature[0] = curpeakgyroval;
        feature[1] = curpeakaccval;
        feature[2] = peakspace;
        feature[3] = peakdiffsquare;
        getfeature(& feature[4], & gyrolist_smoothed[indexstart], indexend - indexstart, NUM_SAMPLE);
        getfeature(& feature[4 + featureUnit_size], & acclist_smoothed[indexstart], indexend - indexstart, NUM_SAMPLE);
        getfeature(& feature[4 + featureUnit_size * 2], & gyrolist[indexstart], indexend - indexstart, NUM_SAMPLE);
        getfeature(& feature[4 + featureUnit_size * 3], & acclist[indexstart], indexend - indexstart, NUM_SAMPLE);
    }
    free(acclist_smoothed);
    free(gyrolist_smoothed);
    free(peakLabel);
    free(peaks);
}
