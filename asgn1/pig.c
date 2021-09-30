#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "names.h"

int main(void){
	
	// Prompting user for number of players 
	int k = 0;
	printf("How many players? ");
	scanf("%d", &k);
	if (k < 2){
		 fprintf(stderr, "Invalid number of players. Using 2 instead.\n");
		 k = 2;
	}
	if (k > 10){
                 fprintf(stderr, "Invalid number of players. Using 2 instead.\n");
		 k = 2;
	}

	// Prompting user for a seed value
	int seedValue = 0;
	printf("Random seed: ");
	scanf("%d", &seedValue);
	if (seedValue < 0){
	       fprintf(stderr, "Invalid random seed. Using 2021 instead.\n");}	
	//if (seedValue > int(4294967295)){
		//fprintf(stderr, "Invalid random seed. Using 2021 instead.\n");}
	

	// Enumerating Positions
	typedef enum {SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER} Position;

	// Forming arrays for players and pig
	// players array
	int players[] = {0, 1};
	for (int i = 2; i < k; i += 1){
		players[i] = i;
		i += 1;
	}	

	// pig array
	const Position pig[7] = {SIDE, SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER, JOWLER};

	return 0;


}
