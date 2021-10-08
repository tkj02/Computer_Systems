#include <stdio.h>
#include "mathlib.h"

static int counter = 0;

double pi_euler(void){
    int k = 1;
    double x = 0;
    int y = 0;
    counter = 0;
    while ((1/(k*k)) > EPSILON){
        x = (1/(k*k));
        y += x;
        k++;
        counter++;
    }
    return sqrt_newton(6*y);
}

int pi_euler_terms(void){
    return counter;
}
