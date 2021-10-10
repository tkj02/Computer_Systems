#include "mathlib.h"

#include <stdio.h>

static int counter = 0;

double pi_viete(void) {
    double first_term = 1;
    double second_term = 0;
    double numerator = 0;
    counter = 0;
    while (absolute(first_term - second_term) > EPSILON) {
        second_term = first_term;
        numerator = sqrt_newton(numerator + 2);
        first_term *= numerator / 2;
        counter++;
    }
    return 2.0 / first_term;
}

int pi_viete_factors(void) {
    return counter;
}
