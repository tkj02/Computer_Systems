#include "mathlib.h"

#include <stdio.h>

static int counter = 0;

double sqrt_newton(double x) {
    double first_term = 1.0;
    double second_term = 0.0;
    while (absolute(first_term - second_term) > EPSILON) {
        second_term = first_term;
        first_term = (second_term + x / second_term) / 2;
        counter++;
    }
    return first_term;
}

int sqrt_newton_iters() {
    return counter;
}
