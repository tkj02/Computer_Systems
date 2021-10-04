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
    int players = 2;
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
    int64_t seed_value = 2021;
    printf("Random seed: ");
    scanf("%ld", &seed_value);
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
    // Set to hold max number of players (if less than max, higher indexes are ignored)
    int points[10] = { 0 };

    // Simulates pig roll
    // Each player, starting with the first and until the last, takes turns
    // rolling the pig (where its positions are represented by random() % seven).
    // Players keep rolling until they roll SIDE (which starts the next
    // player's turn) or until they reach a hundred or more points (where
    // they win and end the game).
    srandom(seed_value);
    int current_player = 0;
    while (current_player < players) {
        printf("%s rolls the pig...", names[current_player]);
        int roll = (random() % 7);
        while (pig[roll] != SIDE) {
            if (pig[roll] == JOWLER) {
                printf(" pig lands on ear");
                points[current_player] += 5;
            } else if (pig[roll] == RAZORBACK) {
                printf(" pig lands on back");
                points[current_player] += 10;
            } else if (pig[roll] == TROTTER) {
                printf(" pig lands upright");
                points[current_player] += 10;
            } else if (pig[roll] == SNOUTER) {
                printf(" pig lands on snout");
                points[current_player] += 15;
            }
            if (points[current_player] >= 100) {
                break;
            }
            roll = (random() % 7);
        }
        if (points[current_player] >= 100) {
            printf("\n%s wins with %d points!\n", names[current_player], points[current_player]);
            break;
        }
        if (pig[roll] == SIDE) {
            printf(" pig lands on side\n");
            if (current_player == players - 1) {
                current_player = 0;
            } else {
                current_player += 1;
            }
        }
    }
}
