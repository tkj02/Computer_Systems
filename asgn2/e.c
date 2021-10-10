#include "mathlib.h"

#include <stdio.h>

static int counter = 0;

double e(void) {
    int first_term = 1;
    int second_term = 0;
    int factorial = 0;
    int counter = 0;
    while (absolute(first_term - second_term) > EPSILON) {
        if (factorial == 0) {
            factorial = 1;
        } else {
            second_term = first_term;
            first_term += (1 / factorial);
            counter++;
        }
    }
    return first_term;
}

int e_terms(void) {
    return counter;
}
