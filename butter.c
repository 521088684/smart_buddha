#include <stdio.h>
#include <complex.h>
#include <math.h>
#include <string.h>
#define MAX_SIZE 40

void zeros2coeffs(double _Complex * zeros, double _Complex * coeffs, int size)
{
    int * b = new int[size + 1];
    memset(b, 0, sizeof(int) * (size + 1));
    int i = 0;
    while (!b[size])
    {
        i = 0;
        while (b[i])
            b[i++] = 0;
        b[i] = 1;
        int subset_size = 0;
        double _Complex summand = 1.0;
        for (i = 0; i < size; ++i)
        {
            if (b[i])
            {
                summand *= zeros[i];
                ++subset_size;
            }
        }
        coeffs[size - subset_size] += summand;
    }
    delete [] b;
    for (int i = (size + 1) % 2; i < size; i += 2)
    {
        coeffs[i] = -coeffs[i];
    }
    coeffs[size] = 1.0;
}

double warp_freq(double freq, double Fs)
{
    return Fs * tan(M_PI * freq / Fs) / M_PI;
}

void butterworth_poles(double _Complex * poles, int order, double cutoff)
{
    double arg;
    for (int i = 0; i < order; ++i)
    {
        arg = M_PI * (2 * i + order + 1) / 2 / order;
        poles[i] = cos(arg) + sin(arg) * I;
        poles[i] *= 2 * M_PI * cutoff;
    }
}

void p2z(double _Complex * p, double _Complex * z, int size, double Fs)
{
    for (int i = 0; i < size; ++i)
    {
        double _Complex tmp = 2 * Fs;
        z[i] = (tmp + p[i]) / (tmp - p[i]);
    }
}

void butterworth_z_zeros(double _Complex * zeros, int order)
{
    for (int i = 0; i < order; ++i)
    {
        zeros[i] = -1.0;
    }
}

void butter(double * a, double * b, int order, double Fs)
{
    double _Complex p_poles[MAX_SIZE];
    double _Complex z_poles[MAX_SIZE];

    double _Complex a_coeffs[MAX_SIZE];
    double _Complex b_coeffs[MAX_SIZE];

    double _Complex z_zeros[MAX_SIZE];

    double analog_cutoff = 1.33;//analog freq
    double cutoff = warp_freq(analog_cutoff, Fs);//corresponding digital freq

    butterworth_poles(p_poles, order, cutoff);
    p2z(p_poles, z_poles, order, Fs);
    zeros2coeffs(z_poles, b_coeffs, order);
    butterworth_z_zeros(z_zeros, order);
    zeros2coeffs(z_zeros, a_coeffs, order);
    double k0_numer=0.0;
    double k0_denom=0.0;
    for(int i=0; i<order+1; ++i){
        k0_numer += creal(a_coeffs[i]);
        k0_denom += creal(b_coeffs[i]);
    }
    for (int i = 0; i < order + 1; ++i)
    {
        a[i] = creal(a_coeffs[i]) / k0_numer * k0_denom;
        b[i] = creal(b_coeffs[i]);
    }
}


void lfilter(double * y, double * x, int w_size , double * a, double * b, int f_size)
{
    for (int i = 0; i < w_size; ++i)
    {
        y[i] = 0.0;
        int tmp_size = f_size;
        if (i < tmp_size)
            tmp_size = i;
        for (int j = 0; j < tmp_size; ++j)
        {
            y[i] += b[j] * x[i - j];
        }
        for (int j = 1; j < tmp_size; ++j)
        {
            y[i] -= a[f_size - 1 - j] * y[i - j];
        }
    }
    return;
}
