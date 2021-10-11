Assignment 2 - A Little Slice of Pi

Purpose: The purpose of this assignment is to implement means of approximating mathematical values and determining their accuracy. There are six files (e.c, madhava.c, euler.c, bbp.c, viete.c, and newton.c) contained in this repository, where the first one approximates e, the next four approximate pi, and the last on approximates the square root of [0, 10, +0.1]. mathlib-test.c can use the code contained in each file to then display the approximations, the actual values from the math.h library, and their differences.

Build and Run: To compile mathlib-test.c and create the executable file mathlib-test, run `$ make all`. Then run `$ ./mathlib-test` with any combination of the command line arguments a, e, b, m, r, v, n, s, and h (example, `$ ./mathlib-test -e -b -s`).

Files:
- e.c                   Contains e() and e_terms(). Uses Taylor Series for computation
- madhava.c             Contains pi_madhava() and pi_madhava_terms(). Uses the Madhava Series for computation
- euler.c               Contains pi_euler() and pi_euler_terms(). Uses Euler’s solution to Basel problem
- bbp.c                 Contains pi_bbp() and pi_bbp_terms(). Uses the Bailey-Borwein-Plouffe formula
- viete.c               Contains pi_viete() and pi_viete_factors(). Uses the Viete formula
- newton.c              Contains sqrt_newton() and sqrt_newton_iters(). Uses the Newton-Raphson method
- mathlib-test.c        Contains the main test harness for implemented math library
- mathlib.h             Contains the definition of epsilon and all functions
- Makefile              Contains  information for compiling, formatting, and removing .o files and executables
- DESIGN.pdf            Contains a detailed explanation of the files, all pseudocode, and notes
- WRITEUP.pdf           Contains graphs comparing the approximations to their actual values
- README.md             Contains a summary of this assignment

Assistance:
- Watch Eugene’s recorded section on YuJa (learned about the assignment overall and how gnuplot works)
- Attended Sloan’s office hours on October 8 (learned about using static variables)
- Attended Chrtisian’s office hours on October 8 (learned about implementing exponents and how to use the absolute condition in my while loops)
- Attended Brian’s section on October 8 (learned about a method to implement viete.c)

There are no known bugs/errors according to scan-build, and the program outputs the correct content and format in comparison to the example mathlib-test file under resources.
