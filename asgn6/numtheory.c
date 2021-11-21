#include "numtheory.h"
#include "randstate.h"
#include <stdio.h>
#include <stdlib.h>

// Contains the implementations
// of the number theory functions

// Computes greatest common divisor of a and b
// Stores value in d
void gcd(mpz_t d, mpz_t a, mpz_t b) {
    while (mpz_cmp_d(b, 0) != 0) {
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
    mpz_t r, r_inv;
    mpz_inits(r, r_inv, NULL);

    // Sets r = n and r inverse = a
    mpz_set(r, n);
    mpz_set(r_inv, a);

    // Sets i = zero and i inverse = one
    mpz_init(i);
    mpz_t i_inv;
    mpz_init(i_inv);
    mpz_set_si(i_inv, 1);

    // Initializes other variables
    mpz_t q, qr_inv, qi_inv;
    mpz_inits(q, qr_inv, qi_inv, NULL);

    // Loops while r inverse is not zero
    while (mpz_cmp_d(r_inv, 0) != 0) {
        // Sets q to floor of r/r inverse
        mpz_fdiv_q(q, r, r_inv);

        // Sets r to r inverse
        mpz_set(r, r_inv);

        // Sets r inverse to r - q * r inverse
        mpz_mul(qr_inv, q, r_inv);
        mpz_sub(r_inv, r, qr_inv);

        // Sets i to i inverse
        mpz_set(i, i_inv);

        // Sets i inverse to i - q * i inverse
        mpz_mul(qi_inv, q, i_inv);
        mpz_sub(i_inv, i, qi_inv);
    }

    // Checks if r is greater than one
    if (mpz_cmp_d(r, 1) > 0) {
        // Sets i to zero
        mpz_set_si(i, 0);
    }

    // Checks if i is less than zero
    if (mpz_cmp_d(i, 0) < 0) {
        // Sets i to i + n
        mpz_add(i, i, n);
    }
    // Freeing variables
    mpz_clears(r, r_inv, NULL);
    mpz_clear(i_inv);
    mpz_clears(q, qr_inv, qi_inv, NULL);
}

void pow_mod(mpz_t out, mpz_t base, mpz_t exponent, mpz_t modulus) {
    // Sets out to one and p to base
    mpz_set_si(out, 1);
    mpz_t p;
    mpz_set(p, base);

    // Initializes other variables
    mpz_t outp, pp;

    // Loops while exponent is greater than zero
    while (mpz_cmp_d(exponent, 0) > 0) {
        // Checks if exponent is odd
        if (mpz_odd_p(exponent) != 0) {
            // Sets out to out * p mod modulus
            mpz_mul(outp, out, p);
            mpz_mod(out, outp, modulus);
        }
        // Sets p to p * p mod modulus
        mpz_mul(pp, p, p);
        mpz_mod(p, pp, modulus);

        // Sets exponent to floor of exponent/two
        mpz_fdiv_q_ui(exponent, exponent, 2);
    }
    mpz_clear(p);
    mpz_clears(outp, pp, NULL);
}

gmp_randstate_t state;

bool is_prime(mpz_t n, uint64_t iters) {
    // Creates variables for future use
    // sub = n - one
    // subs = s - one
    // subn = s - three
    mpz_t y, a, j, s, r;
    mpz_t sub, subs, subn;
    mpz_t exponent;

    // Checks if n is even (and therefore not prime)
    // Returns false if so
    if (mpz_even_p(n) != 0 && mpz_cmp_d(n, 2) != 0) {
        return false;
    }
    // Writes n-one = two^s * r
    // s starts at zero and r at n-one
    mpz_init(s);
    mpz_sub_ui(sub, n, 1);
    mpz_set(r, sub);

    // Sets subs = s - one
    mpz_sub_ui(subs, s, 1);

    // Sets subn = n - three
    mpz_sub_ui(subn, n, 3);

    // Loops while r is even
    // Determines s and r values
    while (mpz_even_p(r) != 0) {
        // Increments s by one and divides r by two until valid r
        mpz_add_ui(s, s, 1);
        mpz_divexact_ui(r, r, 2);
    }
    // Conducts Miller-Rabin test
    for (uint64_t i = 0; i < iters; i++) {
        // Sets a to a random value between two and n-two
        mpz_urandomm(a, state, subn);
        mpz_add_ui(a, a, 2);

        // Calls pow_mod and stores value in y
        pow_mod(y, a, r, n);
        randstate_clear();
        //mpz_powm

        // Checks if y does not = one and does not = n-one
        if (mpz_cmp_d(y, 1) != 0 && mpz_cmp(y, sub) != 0) {

            // Sets j to one
            mpz_set_d(j, 1);

            // Loops while j is less than or equal to s-one
            // and y does not equal to n-one
            while (mpz_cmp(j, subs) <= 0 && mpz_cmp(y, sub) != 0) {
                // Calls pow_mod and stores value in y
                mpz_set_d(exponent, 2);
                pow_mod(y, y, exponent, n);

                // Returns false if y is one
                if (mpz_cmp_d(y, 1) == 0) {
                    mpz_clears(y, a, j, s, r, NULL);
                    mpz_clears(sub, subs, subn, NULL);
                    mpz_clear(exponent);
                    return false;
                }
                // Increments j by one
                mpz_add_ui(j, j, 1);
            }
            // Returns false if y does not equal n-one
            if (mpz_cmp(y, sub) != 0) {
                mpz_clears(y, a, j, s, r, NULL);
                mpz_clears(sub, subs, subn, NULL);
                mpz_clear(exponent);
                return false;
            }
        }
    }
    mpz_clears(y, a, j, s, r, NULL);
    mpz_clears(sub, subs, subn, NULL);
    mpz_clear(exponent);
    return true;
}

void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
    // Loops until p is prime
    while (1) {
        // Generates random int of length bits
        mpz_urandomb(p, state, bits);

        // Checks if p is prime and breaks if so
        if (is_prime(p, iters)) {
            break;
        }
    }
    randstate_clear();
}
