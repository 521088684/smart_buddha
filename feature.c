#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "butter.c"
#include "f.c"
#include "feature.h"


void my_feature(double * feature, f_size, double * acclist, double * gyrolist, int w_size, double frequency)
{
    double * acclist_smoothed = (double *) malloc (w_size * sizeof(double));;
    double * gyrolist_smoothed = (double *) malloc (w_size * sizeof(double));;

    double a[ORDER + 1] = {0.0};
    double b[ORDER + 1] = {0.0};
    butter_lowpass(a, b, ORDER, frequency);
    lfilter(acclist_smoothed, acclist, w_size, a, b, ORDER + 1);
    lfilter(gyrolist_smoothed, gyrolist, w_size, a, b, ORDER + 1);
    bool * peakLabel = (bool *) malloc (w_size * sizeof(double));
    int peakCount = mark_peak(peakLabel, gyrolist_smoothed, w_size);
    int * peaks = (int *) malloc (peakCount * sizeof(int));
    int index_tmp = 0;
    for (int i = 0; i < w_size; ++i)
        if (peakLabel[i])
            peaks[index_tmp++] = i;


    free(acclist_smoothed);
    free(gyrolist_smoothed);
    free(peakLabel);
    free(peaks);
}
