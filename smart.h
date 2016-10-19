#define FREQUENCY 10.0
#define ROUND 1

static int step_num = 0;
static int hand_num = 0;

static int array_index = 0;
static int abcdef[FREQUENCY * ROUND][6] = {0};
static double acc[FREQUENCY * ROUND] = {0};
static double gyro[FREQUENCY * ROUND] = {0};
