#include "mathlib.h"

#include <math.h>
#include <stdio.h>

static int counter = 0;

double pi_madhava(void) {
    double first_term = 1.0;
    double second_term = 0.0;
    double fraction = 0.0;
    double numerator = 0.0;
    double denominator = 0.0;
    counter = 0;
    while (counter < 2 || absolute(first_term - second_term) > EPSILON) {
        second_term = first_term;
        if (counter == 0) {
            numerator = 1.0;
            denominator = 1.0;
        } else {
            numerator *= -3.0;
            denominator = (2.0 * counter) + 1.0;
            fraction = 1.0 / numerator;
            first_term += fraction / denominator;
        }
        counter++;
    }
    return (first_term * sqrt_newton(12));
}

int pi_madhava_terms(void) {
    return counter;
}
