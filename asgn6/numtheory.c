#include "numtheory.h"
#include <stdio.h>
#include <stdlib.h>

// Contains the implementations
// of the number theory functions

// Computes greatest common divisor of a and b
// Stores value in d
void gcd(mpz_t d, mpz_t a, mpz_t b) {
    while (b != 0) {
        // Sets d = b
        mpz_set(d, b);

        // Sets b to a mod b
        mpz_mod(b, a, b);

        // Sets a = d
        mpz_set(a, d);
    }
}

void mod_inverse(mpz_t i, mpz_t a, mpz_t n) {
    // Initializes r and r inverse
    mpz_t r;
    mpz_t r_inv;

    // Sets r = n and r inverse = a
    mpz_set(r, n);
    mpz_set(r_inv, a);

    // Sets i = zero and i inverse = one
    mpz_init(i);
    mpz_t i_inv;
    mpz_set_si(i_inv, 1);

    // Loops while r inverse is not zero
    while (mpz_cmp_d(r_inv, 0) != 0) {

        // Sets q to the floor of r/r inverse
        mpz_t q;
        mpz_fdiv_q(q, r, r_inv);

        // Sets r to r inverse
        mpz_set(r, r_inv);

        // Sets r inverse to r - q * r inverse
        mpz_t qr_inv;
        mpz_t diff_r;

        mpz_mul(qr_inv, q, r_inv);
        mpz_sub(diff_r, r, qr_inv);
        mpz_set(r_inv, diff_r);

        // Sets i to i inverse
        mpz_set(i, i_inv);

        // Sets i inverse to i - q * i inverse
        mpz_t qi_inv;
        mpz_t diff_i;

        mpz_mul(qi_inv, q, i_inv);
        mpz_sub(diff_i, i, qi_inv);
        mpz_set(i_inv, diff_i);
    }
    // Checks if r is greater than one
    if (mpz_cmp_d(r, 1) > 0) {
        // Sets i to zero
        mpz_init(i);
    }
    // Checks if i is less than zero
    if (mpz_sgn(i) == -1) {

        // Sets i to i + n
        mpz_t sum;
        mpz_add(sum, i, n);
        mpz_set(i, sum);
    }
}

#if 0
void pow_mod(mpz_t out, mpz_t base, mpz_t exponent, mpz_t modulus){
}

bool is_prime(mpz_t n, uint64_t iters) {
}

void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
}
#endif
