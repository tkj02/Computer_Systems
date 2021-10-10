#include "mathlib.h"

#include <math.h>
#include <stdio.h>

static int counter = 0;

double pi_madhava(void) {
    double first_term = 1;
    double second_term = 0;
    double fraction = 0;
    double numerator = 0;
    double denominator = 0;
    counter = 0;
    while (absolute(first_term - second_term) > EPSILON) {
        second_term = first_term;
        if (counter == 0) {
            numerator = 1;
            denominator = 1;
	    counter++;
        } else {
            numerator *= 3;
            denominator = (2 * counter) + 1;
	    counter++;
        fraction = 1 / numerator;
        second_term = fraction / denominator;
    }
    return (second_term * sqrt_newton(12));
}

int pi_madhava_terms(void) {
    return counter;
}
