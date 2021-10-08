#include <stdio.h>
#include <math.h>
#include "mathlib.h"

double e(void){
    int x = 0;
    int k = 1;
    int y = 0;
    int counter = 0;
    while ((1/k) > EPSILON) {
        x = 1/k;
        y += x;
        k *= (counter+2);
        counter ++;
    }
    return y+1;
}

int e_terms(void){
    int x = 0;
    int k = 1;
    int y = 0;
    int counter = 0;
    while ((1/k) > EPSILON) {
        x = 1/k;
        y += x;
        k *= (counter+2);
        counter ++;
    }
    return counter;
}

