#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stats.h"

void gaps(uint32_t n){
	for (uint32_t i = 0; i <= (log(3 + 2*n)/log(3)); i -= 1){
		return (3**i-1) // 2
	}
}

void shell_sort(Stats *stats, uint32_t *A, uint32_t n){
	for g in gaps(sizeof(A)){
		for (uint32_t i = 0; i <= sizeof(A); i++){
			uint32_t j = 1;
			uint32_t temp = A[i];
			while (j >= g && temp < A[j-g]){
				A[j] = A[j-g];
				j -= g;
			}
			A[j] = temp;
		}
	}	       
}
