#include "names.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

// This program is an implementation of the game Pass the Pigs.
// The user will be asked to input the number of players and a random seed.
// The program will then output the progression of the game (each player's turn and
// what they roll) and then print the name of the winner along with their points.

int main(void) {

    // Prompts user for the number of players and checks if the input is valid
    int players;
    printf("How many players? ");
    scanf("%d", &players);
    if (players < 2) {
        fprintf(stderr, "Invalid number of players. Using 2 instead.\n");
        players = 2;
    } else if (players > 10) {
        fprintf(stderr, "Invalid number of players. Using 2 instead.\n");
        players = 2;
    }

    // Prompts user for a seed value and checks if the input is valid
    int seed_value;
    printf("Random seed: ");
    scanf("%d", &seed_value);
    if (seed_value < 0) {
        fprintf(stderr, "Invalid random seed. Using 2021 instead.\n");
        seed_value = 2021;
    } else if ((long) seed_value > UINT_MAX) {
        fprintf(stderr, "Invalid random seed. Using 2021 instead.\n");
        seed_value = 2021;
    }

    // Defines type Positions and enumerates positions
    typedef enum { SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER } Position;

    // Forms pig array (reflects the probability of each of the rolls)
    const Position pig[7] = { SIDE, SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER, JOWLER };

    // Forms points array (reflects each player's initial points)
    int points[10];
    for (int j = 2; j < players; j += 1) {
        points[j] = 0;
    }

    // Simulates pig roll
    // Each player, starting with the first and until the last, takes turns
    // rolling the pig (where its positions are represented by random() % seven).
    // Players keep rolling until they roll SIDE (which starts the next
    // player's turn) or until they reach a hundred or more points (where
    // they win and end the game).
    srandom(seed_value);
    int p = 0;
    while (p < players) {
        printf("%s rolls the pig...", names[p]);
        int roll = (random() % 7);
        while (pig[roll] != SIDE) {
            if (pig[roll] == JOWLER) {
                printf(" pig lands on ear");
                points[p] += 5;
            } else if (pig[roll] == RAZORBACK) {
                printf(" pig lands on back");
                points[p] += 10;
            } else if (pig[roll] == TROTTER) {
                printf(" pig lands upright");
                points[p] += 10;
            } else if (pig[roll] == SNOUTER) {
                printf(" pig lands on snout");
                points[p] += 15;
            }
            if (points[p] >= 100) {
                break;
            }
            roll = (random() % 7);
        }
        if (points[p] >= 100) {
            break;
        }
        if (pig[roll] == SIDE) {
            printf(" pig lands on side");
            if (p == players - 1) {
                p = 0;
            } else {
                p += 1;
            }
        }
    }

    // Finds winner and prints their name and amount of points
    for (int i = 0; i < players; i += 1) {
        if (points[i] >= 100) {
            printf("\n%s wins with %d points!", names[i], points[i]);
            break;
        }
    }
}
