#include "mathlib.h"

#include <stdio.h>

static int counter = 0;

double pi_bbp(void) {
    double first_term = 0;
    double second_term = 0;
    //double fraction = 0;
    double coeff = 0;
    double f_coeff = 0;
    counter = 0;
    while (counter < 2 || absolute(first_term - second_term) > EPSILON) {
        second_term = first_term;
        double fraction = (4.0 / (8 * counter + 1)) - (2.0 / (8 * counter + 4))
                          - (1.0 / (8 * counter + 5)) - (1.0 / (8 * counter + 6));
        if (counter == 0) {
            coeff = 1;
            f_coeff = 1;
        } else {
            coeff *= 16;
            f_coeff = 1 / coeff;
        }
        counter++;
        first_term += f_coeff * fraction;
    }
    return first_term;
}

int pi_bbp_terms(void) {
    return counter;
}
