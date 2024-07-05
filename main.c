#include <stdio.h>
#include <stdlib.h>

#define SIG_LEN     (320)

#include "waveforms.h"

double mean = 0.0;
double variance = 0.0;

double calc_signal_mean(const double sig_src_arr[], const size_t sig_len);
double calc_signal_variance(const double sig_src_arr[], const size_t sig_src_len, const double sig_mean);
void convolution(
                 const double sig_src_arr[], 
                 const size_t sig_src_len, 
                 const double kernel_arr[], 
                 const size_t kernel_len, 
                 double* output_arr);

FILE* store_signal(const double sig_src_arr[], const size_t sig_src_len, const char* filename)
{
    FILE* sig_src_fptr;
    sig_src_fptr = fopen(filename, "w");
    for (size_t n = 0; n < sig_src_len; n++)
    {
        fprintf(sig_src_fptr, "%.10lf\n", sig_src_arr[n]);
    }
    fclose(sig_src_fptr);

    return sig_src_fptr;
}

int main(void)
{
   store_signal(InputSignal_f32_1kHz_15kHz, SIG_LEN, "input_signal.txt");


   mean     =  calc_signal_mean(InputSignal_f32_1kHz_15kHz, SIG_LEN);
   variance =  calc_signal_variance(InputSignal_f32_1kHz_15kHz, SIG_LEN, mean);
   printf("mean = %lf\r\n",  mean);
   printf("variance = %lf\r\n",  variance);

    return 0;
}

double calc_signal_mean(const double sig_src_arr[], const size_t sig_len)
{
    double mean = 0.0;
    for(size_t i = 0; i < sig_len; i++)
    {
        mean += sig_src_arr[i]; // may cause overflow
    }
    mean /= (double)sig_len;
    return mean;
}

double calc_signal_variance(const double sig_src_arr[], const size_t sig_src_len, const double sig_mean)
{
    double variance = 0.0;
    double tmp = 0.0;
    for(size_t i = 0; i < sig_src_len; i++)
    {
        tmp = (sig_src_arr[i] - sig_mean);
        variance += tmp * tmp;
    }
    variance /= (double)sig_src_len - 1;
    return variance;
}


void convolution(
                 const double sig_src_arr[], 
                 const size_t sig_src_len, 
                 const double kernel_arr[], 
                 const size_t kernel_len, 
                 double* output_arr) 
{

    const size_t output_len = sig_src_len + kernel_len;

    // Initialize the output array with zeros
    for (size_t n = 0; n < output_len; n++) 
    {
        output_arr[n] = 0.0;
    }

    // Perform the convolution O(N^2)
    for (size_t n = 0; n < sig_src_len; n++) 
    {
        for (size_t k = 0; k < kernel_len; k++) 
        {
           output_arr[n + k] +=  sig_src_arr[n] * kernel_arr[k];
        }
    }
}