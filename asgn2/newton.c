#include <stdio.h>
#include <math.h>
#include "mathlib.h"

double absolute_func(double value) {
    if(value < 0){
        value = -value;
    }
    return value;
}

int counter = 0;

double sqrt_newton(double x) {
        double y = 1.0;
        double z = 0.0;
        //int counter = 0;
        while (absolute_func(y-z) > EPSILON){
                z=y;
                y = 0.5 * (y+x/y);
                counter++;
        }
        return y;
}

int sqrt_newton_iters() {
    double x;
    sqrt_newton(x);
    return counter;
}

