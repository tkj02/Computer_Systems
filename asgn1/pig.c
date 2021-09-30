#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "names.h"

// Implementation of a game of Pass the Pigs

int main(void){
	
	// Prompting user for number of players 
	int k;
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
	int seedValue;
	printf("Random seed: ");
	scanf("%d", &seedValue);
	if (seedValue < 0){
		fprintf(stderr, "Invalid random seed. Using 2021 instead.\n");
		seedValue = 2021;
	}	
	if ((long)seedValue > UINT_MAX){
		fprintf(stderr, "Invalid random seed. Using 2021 instead.\n");
		seedValue = 2021;
	}
	

	// Enumerating Positions
	typedef enum {SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER} Position;

	// Forming pig array
        const Position pig[7] = {SIDE, SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER, JOWLER};

	// Forming points array
	int points[] = {0, 0};
	for (int j = 2; j <= k-1; j += 1){
	       points[j] = 0;
	       j += 1;
	}

	// Simulating pig roll
	for (int p = 0; p <= k-1; p += 1){
		printf("%s rolls the pig... ", names[p]);
		srandom(seedValue);
		int roll = (random() % 7);
		while (pig[roll] != SIDE){
			if (pig[roll] == JOWLER){
				printf("pig lands on jowler ");
				points[p] += 5;
				if (points[p] >= 100){
				}
			}
			if (pig[roll] == RAZORBACK){
				printf("pig lands on razorback ");
                        	points[p] += 10;
                        	if (points[p] >= 100){
                                	break;
                       		}
			}
			if (pig[roll] == TROTTER){
				printf("pig lands on trotter ");
                        	points[p] += 10;
                        	if (points[p] >= 100){
                                	break;
                        	}
			}
			if (pig[roll] == SNOUTER){
				printf("pig lands on snouter ");
                        	points[p] += 15;
                      		if (points[p] >= 100){
                               		break;
				}
			}
		if (pig[roll] == SIDE){
			printf("pig lands on side\n");
                        if (p == k-1){
                                p = 0;
                        }
                        else{
                                p += 1;
                        }
		}
		}
	}


	// Ending game
	//printf("__ wins with ___ points!", names[_], points[])
	// Will print name of winner and their points


}
