#include "mathlib.h"

#include <stdio.h>

static unsigned long counter = 0;

double pi_euler(void) {
    double first_term = 0.0;
    double second_term = 0.0;
    counter = 1;
    while (counter < 2 || (absolute(first_term - second_term) > EPSILON)) {
        second_term = first_term;
        first_term += (1.0 / (counter * counter));
        counter++;
    }
    return sqrt_newton(6 * first_term);
}

int pi_euler_terms(void) {
    return (counter - 1);
}
