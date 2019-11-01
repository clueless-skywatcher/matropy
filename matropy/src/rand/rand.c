#include <time.h>
#include <stdio.h>
#include <stdlib.h>

long *lcg(int size, long upper){
    long *series;
    series = malloc(size * sizeof(long));
    long seed = (long) time(NULL);
    long modulus = 12387409;
    long multiplier = 11234345;
    long increment = 7569;
    int i;
    long next_num = (long)(seed * multiplier + increment) % modulus;
    series[0] = next_num % upper;
    if (series[i] < 0){
        series[i] = -series[i];
    }
    for (i = 1; i < size; i++){
        next_num = (long)(series[i - 1] * multiplier + increment) % modulus;
        series[i] = next_num % upper;
        if (series[i] < 0){
            series[i] = -series[i];
        }
    }
    return series;
}

int main() {
    /* code */
    long *series = lcg(1, 25);
    printf("%ld\n", series[0]);
    return 0;
}
