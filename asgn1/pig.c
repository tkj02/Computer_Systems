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
		fprintf(stderr, "Invalid random seed. Using 2021 instead.\n");
		seedValue = 2021;
	}	
	if (seedValue > (signed)UINT_MAX){
		fprintf(stderr, "Invalid random seed. Using 2021 instead.\n");
		seedValue = 2021;
	}
	

	// Enumerating Positions
	typedef enum {SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER} Position;

	// Forming pig array
        const Position pig[7] = {SIDE, SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER, JOWLER};
	
	// Forming players array
	int players[] = {0, 1};
	for (int i = 2; i < k; i += 1){
		players[i] = i;
		i += 1;
	}

	// Forming points array
	int points[] = {0, 0};
	for (int j = 2; j < k; j += 1){
	       points[j] = 0;
	       j += 1;
	}

	// Simulating pig roll
	for (int p = 0; p < k; p += 1){
		printf("%s rolls the pig\n", names[p]);
		srandom(seedValue);
		int roll = (random() % 7);
		while (pig[roll] != SIDE){
			if (pig[roll] == JOWLER){
				points[p] += 5;
				if (points[p] >= 100){
					break;
				}
				else{
					continue;
				}
			}
			if (pig[roll] == RAZORBACK){
                        	points[p] += 10;
                        	if (points[p] >= 100){
                                	break;
                       		}
                        	else{
                                	continue;
                        	}
			}
			if (pig[roll] == TROTTER){
                        	points[p] += 10;
                        	if (points[p] >= 100){
                                	break;
                        	}
                        	else{
                                	continue;
                        	}
			}
			if (pig[roll] == SNOUTER){
                        	points[p] += 15;
                        	if (points[p] >= 100){
                                	break;
                        	}
                        	else{	
                                	continue;
                        	}
			}
		}
                if (pig[roll] == SIDE){
                        if (p == k-1){
                                p = 0;
                        }
                        else{
                                p += 1;
                        }
                        continue;
                }
        }


	// Ending game
	// Will print name of winner and their points


}
