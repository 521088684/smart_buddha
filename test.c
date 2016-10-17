#include <stdio.h>
#include <string.h>
#include <math.h>
#include "test.h"
#include "f.c"


void my_main(int accX, int accY, int accZ, int gyroX, int gyroY, int gyroZ)
{
    abcdef[array_index][0] = accX;
    abcdef[array_index][1] = accY;
    abcdef[array_index][2] = accZ;
    abcdef[array_index][3] = gyroX;
    abcdef[array_index][4] = gyroY;
    abcdef[array_index][5] = gyroZ;

    acc[array_index] = My_Sqrt(float(My_Add(My_Mul(accZ, accZ), My_Add(My_Mul(accX, accX), My_Mul(accY, accY)))));
    gyro[array_index] = My_Sqrt(float(My_Add(My_Mul(gyroZ, gyroZ), My_Add(My_Mul(gyroX, gyroX), My_Mul(gyroY, gyroY)))));

    array_index++;
    for (int i = 0; i < FREQUENCY; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            printf("%d ", abcdef[i][j]);
        }
        printf("-------------");
        printf("\n");
    }
    for (int i = 0; i < 6; i++)
    {
        printf("%f", acc[i]);
    }
    printf("\n-------------\n");
    for (int i = 0; i < 6; i++)
    {
        printf("%f", gyro[i]);
    }
    printf("\n-------------\n");
    if (array_index == FREQUENCY)
    {

        array_index = 0;
        memset(abcdef, 0, sizeof(abcdef));
    }
    return;
}

int main()
{
    printf("Hello world!\n");

    int a, b, c, d, e, f;
    while(1)
    {
        scanf("%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);
        my_main(a, b, c, d, e, f);
    }

    printf("Bye world!\n");
    return 0;
}
