#include "mathlib.h"

#include <stdio.h>

static int counter = 0;

double pi_euler(void) {
    double x = 0;
    int y = 0;
    int k = 1;
    counter = 0;
    while (absolute(y-x) > EPSILON) {
        x = y;
	x = (1 / (k * k));
        k++;
        counter++;
    }
    return sqrt_newton(6 * y);
}

int pi_euler_terms(void) {
    return counter;
}
