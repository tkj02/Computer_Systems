#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(void){
	int k = 0;
	printf("How many players? ");
	scanf("%d", &k);
	if (k < 2){
		 fprintf(stderr, "Invalid number of players. Using 2 instead.\n");
	}
	if (k > 10){
                 fprintf(stderr, "Invalid number of players. Using 2 instead.\n");
        }

	int seedValue = 0;
	printf("Random seed: ");
	scanf("%u", &seedValue);
	if (seedValue > UINT_MAX){
		fprintf(stderr, "Invalid random seed. Using 2021 instead.\n");
	}







}
