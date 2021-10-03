#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "names.h"

// This program is an implementation of the game "Pass the Pigs"
// This game involves between 2 to 10 players taking turns rolling a pig.
// Each position the pig can land in has a corresponding number of points.
// The first player to gain 100 or more points wins and ends the game.

// Enumerating Positions
typedef enum {SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER} Position;

int main(void){

        // Prompting user for number of players (stored in k)
        int k;
        printf("How many players? ");
        scanf("%d", &k);
	if (k < 2 || k > 10){
            fprintf(stderr, "Invalid number of players. Using 2 instead.\n");
            k = 2;
        }

        // Prompting user for a seed value (stored in seed_value)
        int seed_value;
        printf("Random seed: ");
        scanf("%d", &seed_value);
        if (seed_value < 0){
                fprintf(stderr, "Invalid random seed. Using 2021 instead.\n");
                seed_value = 2021;
        }
        if ((long)seed_value > UINT_MAX){
                fprintf(stderr, "Invalid random seed. Using 2021 instead.\n");
                seed_value = 2021;
        }

        // Forming pig array
        const Position pig[7] = {SIDE, SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER, JOWLER};

        // Forming points array
        int points[10];
        for (int j = 2; j < k; j += 1){
               points[j] = 0;
        }

        // Simulating pig roll
        srandom(seed_value);
	int p = 0;
	while (p < k){
		printf("%s rolls the pig... ", names[p]);
                int roll = (random() % 7);
                while (pig[roll] != SIDE){
                        if (pig[roll] == JOWLER){
                                printf("pig lands on ear ");
                                points[p] += 5;
                        }
                        if (pig[roll] == RAZORBACK){
                                printf("pig lands on back ");
                                points[p] += 10;
                        }
                        if (pig[roll] == TROTTER){
                                printf("pig lands upright ");
                                points[p] += 10;
                        }
                        if (pig[roll] == SNOUTER){
                                printf("pig lands on snout ");
                                points[p] += 15;
                        }
                        if (points[p] >= 100){
                                 break;
                        }
                        roll = (random()%7);
                }
		if (points[p] >= 100){
                                 break;
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

        // Ending game
	for (int i = 0; i <= k-1; i += 1){
	       	if (points[i] >= 100){
			printf("\n%s wins with %d points!\n", names[i], points[i]);
	       		break;
		}
	}
}
