#include <stdio.h>
#include <math.h>
#include "mathlib.h"

static double x;

double sqrt_newton(double x) {
        double y = 1.0;
        double z = 0.0;
        static int counter = 0;
        while (absolute(y-z) > EPSILON){
                z=y;
                y = (y+x/y)/2;
                counter++;
        }
        return y;
}

int sqrt_newton_iters() {
    	double y = 1.0;
        double z = 0.0;
        static int counter = 0;
        while (absolute(y-z) > EPSILON){
                z=y;
                y = (y+x/y)/2;
                counter++;
        }
	return counter;
}

