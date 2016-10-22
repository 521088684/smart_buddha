#include <stdlib.h>

#define FREQUENCY 10
#define ORDER 6
#define CUTOFF 1.33
#define PEAKSTEP 2
#define NUM_SAMPLE 8
#define SKIPPEAKS 3
#define NUM_OF_PEAKS_BEFORE 5
#define NUM_OF_PEAKS_AFTER 5
#define QUEUE_SIZE 5936

const static int FEATURE_SIZE = (6 + NUM_SAMPLE << 2) + 4;
static int step_num = 0;
static int hand_num = 0;

static int array_index = 0;
static int abcdef[QUEUE_SIZE][6];
static double acc[QUEUE_SIZE];
static double gyro[QUEUE_SIZE];
