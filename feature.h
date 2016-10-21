#define ORDER 6
#define CUTOFF 1.33
#define PEAKSTEP 2
#define NUM_SAMPLE 2
void getfeature(double * y, double * x, int x_size, int num_sample);
void my_feature(double * feature, int f_size, double * acclist, double * gyrolist, int w_size, double frequency);
