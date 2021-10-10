#include "mathlib.h"

#include <stdio.h>

static int counter;

double e(void) {
    double first_term = 1.0;
    double second_term = 0.0;
    double factorial = 1.0;
    counter = 1;
    while (absolute(first_term - second_term) > EPSILON) {
        second_term = first_term;
        factorial *= counter;
        first_term += 1 / factorial;
        counter++;
    }
    return first_term;
}

int e_terms(void) {
    return counter;
}
