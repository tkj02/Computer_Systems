#include <stdio.h>
#include "mathlib.h"

static int counter = 0;

double sqrt_newton(double x) {
        double y = 1.0;
        double z = 0.0;
        counter = 0;
        while (absolute(y-z) > EPSILON){
                z=y;
                y = (y+x/y)/2;
                counter++;
        }
        return y;
}

int sqrt_newton_iters() {
	return counter;
}

