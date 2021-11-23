#include "numtheory.h"
#include "randstate.h"
#include <stdio.h>
#include <stdlib.h>

// Contains the implementations
// of the number theory functions

void gcd(mpz_t d, mpz_t a, mpz_t b) {
    // Loops while b is not zero
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
    mpz_set_ui(i, 0);
    mpz_t i_inv;
    mpz_init(i_inv);
    mpz_set_ui(i_inv, 1);

    // Initializes other variables
    mpz_t q, qr_inv, qi_inv;
    mpz_inits(q, qr_inv, qi_inv, NULL);
    mpz_t temp_r, temp_i;
    mpz_inits(temp_r, temp_i, NULL);

    // Loops while r inverse is not zero
    while (mpz_cmp_d(r_inv, 0) != 0) {
        // Sets q to floor of r/r inverse
        mpz_fdiv_q(q, r, r_inv);

        // Creates temp value that stores current r
        mpz_set(temp_r, r);

        // Sets r to r inverse
        mpz_set(r, r_inv);

        // Sets r inverse to r - q * r inverse
        mpz_mul(qr_inv, q, r_inv);
        mpz_sub(r_inv, temp_r, qr_inv);

        // Creates temp value that stores current i
        mpz_set(temp_i, i);

        // Sets i to i inverse
        mpz_set(i, i_inv);

        // Sets i inverse to i - q * i inverse
        mpz_mul(qi_inv, q, i_inv);
        mpz_sub(i_inv, temp_i, qi_inv);
    }

    // Checks if r is greater than one
    if (mpz_cmp_d(r, 1) > 0) {
        // Sets i to zero
        mpz_set_ui(i, 0);
    }

    // Checks if i is less than zero
    if (mpz_cmp_d(i, 0) < 0) {
        // Sets i to i + n
        mpz_add(i, i, n);
    }
    // Frees variables
    mpz_clears(r, r_inv, NULL);
    mpz_clear(i_inv);
    mpz_clears(q, qr_inv, qi_inv, NULL);
    mpz_clears(temp_r, temp_i, NULL);
}

void pow_mod(mpz_t out, mpz_t base, mpz_t exponent, mpz_t modulus) {
    // Sets out to one and p to base
    mpz_t v, p;
    mpz_init_set_str(v, "1", 10);
    mpz_init(p);
    mpz_set(p, base);
    mpz_t exp;
    mpz_init(exp);
    mpz_set(exp, exponent);

    // Initializes other variables
    mpz_t outp, pp;
    mpz_inits(outp, pp, NULL);

    // Loops while exponent is greater than zero
    while (1) {
        // Checks if exponent is odd
        if (mpz_odd_p(exp) != 0) {
            // Sets out to out * p mod modulus
            mpz_mul(outp, v, p);
            mpz_mod(v, outp, modulus);
        }
        // Sets p to p * p mod modulus
        mpz_mul(pp, p, p);
        mpz_mod(p, pp, modulus);

        // Sets exponent to floor of exponent/two
        if (mpz_cmp_d(exp, 1) == 0) {
            break;
        }
        // Sets d to floor of d/two
        mpz_fdiv_q_ui(exp, exp, 2);
    }
    // Frees memory
    mpz_add_ui(out, v, 0);
    mpz_clears(v, p, NULL);
    mpz_clears(outp, pp, exp, NULL);
}

gmp_randstate_t state;

bool is_prime(mpz_t n, uint64_t iters) {
    // Creates variables for future use
    // sub = n - one
    // subs = s - one
    // subn = s - three
    bool prime_flag = true;
    mpz_t y, a, j, s, r;
    mpz_t sub, subs, subn;
    mpz_t exponent;

    //
    if (mpz_cmp_d(n, 2) == 0 || mpz_cmp_d(n, 3) == 0) {
        return true;
    }

    // Checks if n is even (and therefore not prime)
    // Returns false if so
    if (mpz_even_p(n) != 0) {
        return false;
    }

    // Writes n-one = two^s * r
    // s starts at zero and r at n-one
    mpz_init(s);
    mpz_init(sub);
    mpz_init(r);

    // Sets sub = n - one
    mpz_sub_ui(sub, n, 1);
    mpz_set(r, sub);

    // Sets subs = s - one
    mpz_inits(subs, subn, a, y, j, exponent, NULL);
    mpz_sub_ui(subs, s, 1);

    // Sets subn = n - three
    mpz_sub_ui(subn, n, 3);

#if 1
    // Loops while r is even
    // Determines s and r values
    while (mpz_even_p(r) != 0) {
        // Increments s by one and divides r by two until valid r
        mpz_add_ui(s, s, 1);
        mpz_divexact_ui(r, r, 2);
    }
#else

    mpz_set(s, n);
    int is_odd = mpz_odd_p(s);
    if (is_odd) {
        mpz_sub_ui(s, s, 1);
    }
    uint64_t rr;
    rr = mpz_scan1(n, *(mp_bitcnt_t[]) { 0 });
    mpz_fdiv_q_2exp(s, s, rr);
    mpz_set_ui(r, rr);

#endif

    // Conducts Miller-Rabin test
    for (uint64_t i = 0; i < iters; i++) {

        // Sets a to a random value between two and n-two
        mpz_urandomm(a, state, subn);
        mpz_add_ui(a, a, 2);

        // Calls pow_mod and stores value in y
        pow_mod(y, a, r, n);

        // For debugging:
        //     gmp_printf("i = %d iter = %d s = %Zd y = %Zd a = %Zd r = %Zd n = %Zd\n", i, iters, s, y, a, r, n);

        // Checks if y does not = one and does not = n-one
        if (mpz_cmp_d(y, 1) != 0 && mpz_cmp(y, sub) != 0) {

            // Sets j to one
            mpz_set_d(j, 1);

            // For debugging:
            //     gmp_printf("before loop j = %Zd subs = %Zd sub = %Zd\n", j, subs, sub);

            // Sets flag to false to break later if needed
            prime_flag = false;

            // Loops while j is less than or equal to s
            while (mpz_cmp(j, s) <= 0) {

                // Calls pow_mod to set y
                mpz_set_d(exponent, 2);
                pow_mod(y, y, exponent, n);

                // If y = one, breaks out of while loop
                if (mpz_cmp_d(y, 1) == 0) {
                    break;
                }

                // If y = n-one, prime found
                // Breaks out of while loop
                if (mpz_cmp(y, sub) == 0) {
                    prime_flag = true;
                    break;
                }

                // Increments j for next loop
                mpz_add_ui(j, j, 1);
            }

            // Checks again for primality
            // Breaks if not a prime
            if (!prime_flag) {
                break;
            }
        }
    }

    // Frees memory
    mpz_clears(y, a, j, s, r, NULL);
    mpz_clears(sub, subs, subn, NULL);
    mpz_clear(exponent);

    // Returns status of primality
    // Returns true if prime and false if not
    return prime_flag;
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
}
