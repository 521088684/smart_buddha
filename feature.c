#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "butter.c"
#include "f.c"
#include "feature.h"


void my_feature(double * feature, int f_size, double * acclist, double * gyrolist, int w_size, double frequency)
{
    double * acclist_smoothed = (double *) malloc (w_size * sizeof(double));;
    double * gyrolist_smoothed = (double *) malloc (w_size * sizeof(double));;

    double a[ORDER + 1] = {0.0};
    double b[ORDER + 1] = {0.0};
    butter_lowpass(a, b, ORDER, frequency);
    for (int i = 0; i < ORDER + 1; i++)
    {
        printf("%lf %lf\n", a[i], b[i]);
    }
    printf("%d\n", w_size);
    acclist[0] = 1.0;
    acclist[1] = 2.0;
    acclist[2] = 1.0;
    acclist[3] = 3.0;
    acclist[4] = 2.0;
    acclist[5] = 2.0;
    acclist[6] = 1.0;
    acclist[7] = 2.0;
    acclist[8] = 1.0;
    acclist[9] = 1.0;

    lfilter(acclist_smoothed, acclist, w_size, a, b, ORDER + 1);
    lfilter(gyrolist_smoothed, gyrolist, w_size, a, b, ORDER + 1);
    for (int i = 0; i < 10; i++)
        printf("%lf\n", acclist_smoothed[i]);

    bool * peakLabel = (bool *) malloc (w_size * sizeof(double));
    int peakCount = mark_peak(peakLabel, gyrolist_smoothed, w_size);
    //if (peanCount <= 10)
    //  return NULL;
    int * peaks = (int *) malloc (peakCount * sizeof(int));
    int index_tmp = 0;
    for (int i = 0; i < w_size; ++i)
        if (peakLabel[i])
            peaks[index_tmp++] = i;
    for (int i = 0; i < peakCount; ++i)
    {
        double curpeakgyroval = gyrolist_smoothed[peaks[i]];
        double curpeakaccval = acclist_smoothed[peaks[i]];
        double peakspace = (peaks[i + PEAKSTEP] - peaks[i]) / PEAKSTEP;
        double peakdiffsquare = pow(gyrolist_smoothed[peaks[i]] - gyrolist_smoothed[peaks[i + PEAKSTEP]], 2.0);
        int indexstart = peaks[i];
        int indexend = peaks[i + PEAKSTEP];


    }


    free(acclist_smoothed);
    free(gyrolist_smoothed);
    free(peakLabel);
    free(peaks);
}
