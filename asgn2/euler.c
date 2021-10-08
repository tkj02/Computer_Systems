#include <stdio.h>
#include <math.h>
#include "mathlib.h"

double pi_euler(void){
    int k = 1;
    double x = 0;
    int y = 0;
    int counter = 0;
    while ((1/(k*k)) > EPSILON){
        x = (1/(k*k));
        y += x;
        k++;
        counter++;
    }
    return sqrt(6*y);
}

int pi_euler_terms(void){
    int counter = 0;
    pi_euler();
    return counter;
}
