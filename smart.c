#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <complex.h>
#include "smart.h"
#include "f.h"
#include "butter.h"
#include "feature.h"

void my_count(double * acc_list, double * gyro_list, int w_size)
{
    double * acc_list_smoothed = (double *) malloc (My_Mul(w_size, sizeof(double)));
    double * gyro_list_smoothed = (double *) malloc (My_Mul(w_size, sizeof(double)));
    double a[ORDER + 1];
    double b[ORDER + 1];
    butter_lowpass(b, a, CUTOFF, FREQUENCY, ORDER);
    lfilter(acc_list_smoothed, acc_list, w_size, a, b, ORDER + 1);
    lfilter(gyro_list_smoothed, gyro_list, w_size, a, b, ORDER + 1);
    bool * peakLabel = (bool *) malloc (My_Mul(w_size, sizeof(bool)));
    int peakCount = mark_peak(peakLabel, gyro_list_smoothed, w_size);
    int * peaks = (int *) malloc (My_Mul(peakCount, sizeof(int)));
    int index_tmp = 0;

    for (int i = 0; i < w_size; ++i)
        if (peakLabel[i])
            peaks[index_tmp++] = i;
    for (int i = NUM_OF_PEAKS_BEFORE; i < peakCount - NUM_OF_PEAKS_AFTER; i = i + SKIPPEAKS)
    {
        double * feature = (double *) malloc (My_Mul(FEATURE_SIZE, sizeof(double)));
        my_feature(feature, & acc_list[peaks[i]], & gyro_list[peaks[i]], & acc_list_smoothed[peaks[i]], & gyro_list_smoothed[peaks[i]], peaks[i + PEAKSTEP] - peaks[i], PEAKSTEP, NUM_SAMPLE);
        int label = my_predict(feature, FEATURE_SIZE);
        free(feature);
    }
    free(acc_list_smoothed);
    free(gyro_list_smoothed);
    free(peakLabel);
    free(peaks);
}

void my_main(int accX, int accY, int accZ, int gyroX, int gyroY, int gyroZ)
{
    abcdef[array_index][0] = accX;
    abcdef[array_index][1] = accY;
    abcdef[array_index][2] = accZ;
    abcdef[array_index][3] = gyroX;
    abcdef[array_index][4] = gyroY;
    abcdef[array_index][5] = gyroZ;

    acc[array_index] = My_Sqrt((double) My_Add(My_Mul(accZ, accZ), My_Add(My_Mul(accX, accX), My_Mul(accY, accY))));
    gyro[array_index] = My_Sqrt((double) My_Add(My_Mul(gyroZ, gyroZ), My_Add(My_Mul(gyroX, gyroX), My_Mul(gyroY, gyroY))));

    array_index++;
    if (array_index == QUEUE_SIZE)
    {
        my_count(acc, gyro, QUEUE_SIZE);
        array_index = 0;
        memset(abcdef, 0, sizeof(abcdef));
    }
}

int main()
{
    printf("Hello world!\n");

    int a, b, c, d, e, f;

    for (int i = 0; i < QUEUE_SIZE; i++)
    {
        scanf("%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);
        my_main(a, b, c, d, e, f);
    }

    printf("Bye world!\n");
    return 0;
}
