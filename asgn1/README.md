Assignment 1 - Pass the Pigs

Purpose: This C program is an implementation of the game “Pass the Pigs." This is where 2 to 10 (both inclusive) players take turns “rolling” a pig. The position that the pig lands in once rolled has an established amount of points. Five points are awarded if the pig lands on its jowler, ten points for its razorback, ten points for its trotters, and 15 points for its snouter. If any of these four positions are rolled, the player can roll again. A turn ends when a player rolls a sideways pig, in which case no points are awarded and the pig must be given to the next player. The first player to reach a hundred or more points wins and ends the game.

Build and Run: To compile pig.c and create the executable file pig, run `$ make all`. Then run `$ ./pig` to play the game.

Files:
- pig.c           Contains code and comments
- names.h         Contains names array that is used in pig.c
- Makefile        Contains information for compiling, formatting, and removing pig and pig.o
- DESIGN.pdf      Contains game breakdown, pseudocode, explanations, and a diagram
- README.md       Contains summary of this assignment

Assistance:
- Attended Eugene’s section on September 28 (learned to use Makefile and srandom()/random())
- Attended Sloan’s office hours on October 1 (noticed a flaw in my pig rolling loops and suggested that I restructure my outermost loop)
- Read chapter three of The C Programming Language by Kernighan & Ritchie (learned about loops and conditions)

There are no known bugs/errors according to scan-build, and the program outputs the correct content and format in comparison to the example pig file under resources.
