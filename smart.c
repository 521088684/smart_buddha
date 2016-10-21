#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <complex.h>
#include "smart.h"
#include "f.h"
#include "feature.h"

void my_count(double * acc_list, double * gyro_list)
{
    double feature[4 + 8 * 4] = {0.0};
    my_feature(feature, 4 + 8 * 4, acc_list, gyro_list, FREQUENCY * ROUND, FREQUENCY);
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
    if (array_index == FREQUENCY * ROUND)
    {
        my_count(acc, gyro);
        array_index = 0;
        memset(abcdef, 0, sizeof(abcdef));
    }
}

int main()
{
    printf("Hello world!\n");

    my_count(acc, gyro);

/*    int a, b, c, d, e, f;
    while(1)
    {
        scanf("%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);
        my_main(a, b, c, d, e, f);
    }*/

    printf("Bye world!\n");
    return 0;
}
