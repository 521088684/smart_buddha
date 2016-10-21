void butter_lowpass(double * a, double * b, double Co, double Fs, int order);
void lfilter(double * y, double * x, int w_size , double * a, double * b, int f_size);
int mark_peak(bool * label, double * x, int n);
