#include "rsa.h"
#include "numtheory.h"
#include "randstate.h"
#include <stdio.h>
#include <stdlib.h>

// Contains the implementation of the RSA library

void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters) {
    // Creates variables for future use
    uint64_t p_bits;
    uint64_t q_bits;
    mpz_t totient;
    mpz_t etotient_gcd;

    // Creates lower and upper bounds for number of bits for p (p_bits)
    uint64_t lower_bound = nbits / 4;
    uint64_t upper_bound = (nbits * 3) / 4;

    // Sets p_bits value is generated
    p_bits = (rand() % (upper_bound - lower_bound) + lower_bound);

    // Sets q_bits value
    q_bits = nbits - p_bits;

    // Creates primes p and q by calling make_prime
    make_prime(p, p_bits, iters);
    make_prime(q, q_bits, iters);

    // Sets n to p * q
    mpz_mul(n, p, q);

    // Sets totient (of n) to p-one * q-one
    mpz_mul(totient, p - 1, q - 1);

    // Finding public exponent e
    while (1) {
        // Generates random number
        mpz_urandomb(e, state, (mp_bitcnt_t) nbits);

        // Calculates gcd of e and totient
        gcd(etotient_gcd, e, totient);

        // Breaks loop if gcd = one (valid e found)
        if (mpz_cmp_d(etotient_gcd, 1) == 0) {
            break;
        }
    }
}

void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    // Writes n, e, and s as hexstrings to pbfile
    gmp_fprintf(pbfile, "%Zx\n", n);
    gmp_fprintf(pbfile, "%Zx\n", e);
    gmp_fprintf(pbfile, "%Zx\n", s);

    // Writes username as string to pbfile
    gmp_fprintf(pbfile, "%s\n", username);
}

void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    // Reads n, e, and s as hexstrings from pbfile
    gmp_fscanf(pbfile, "%Zx\n", n);
    gmp_fscanf(pbfile, "%Zx\n", e);
    gmp_fscanf(pbfile, "%Zx\n", s);

    // Reads username as string from pbfile
    fscanf(pbfile, "%s\n", username);
}

void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q) {
    // Creates variables for future use
    mpz_t n;
    mpz_t totient;

    // Sets n to p * q
    mpz_mul(n, p, q);

    // Sets totient of n to p-one * q-one
    mpz_mul(totient, p - 1, q - 1);

    // Calls mod_inverse and stores inverse e mod totient in d
    mod_inverse(d, e, totient);
}

void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    // Writes n and d as hexstrings to pvfile
    gmp_fprintf(pvfile, "%Zx\n", n);
    gmp_fprintf(pvfile, "%Zx\n", d);
}

void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    // Reads n and d as hexstrings from pvfile
    gmp_fscanf(pvfile, "%Zx\n", n);
    gmp_fscanf(pvfile, "%Zx\n", d);
}

void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n) {
    // Calls pow_mod to compute ciphertext and store in c
    // m is the message (base)
    // e is the public exponent (exponent)
    // n is the public modulus
    pow_mod(c, m, e, n);
}

#if 0
void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e) {
	// Calculates block size k
	size_t k = (mpz_sizeinbase(n, 2)-1)/8;

	// Allocates block array that can hold k bytes
	uint8_t *block = malloc(sizeof(k));

	// Prepends workaround byte
	block[0] = 0xFF;

	// Loops while there are unprocessed bytes in infile
	uint8_t processed = 0;
	uint8_t j = 0;
	while (j < processed){
		j = fread(&block[1], 8, k-1, infile);

	}


}
#endif

void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n) {
    // Calls pow_mod to compute message and store in m
    // c is the ciphertext (base)
    // d is the private key (exponent)
    // n is the public modulus
    pow_mod(m, c, d, n);
}

#if 0
void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d) {
	// Calculates block size k
        size_t k = (mpz_sizeinbase(n, 2)-1)/8;

        // Allocates block array that can hold k bytes
        uint8_t *block = malloc(sizeof(k));
}
#endif

void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n) {
    // Calls pow_mod to produce signature and store in s
    // m is the message (base)
    // d is the private key (exponent)
    // n is the public modulus
    pow_mod(s, m, d, n);
}

bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n) {
    // Creates variable for storing verification
    mpz_t t;

    // Computes verification of signature
    pow_mod(t, s, e, n);

    // Returns true if signature is verified and false otherwise
    if (mpz_cmp(t, m) == 0) {
        return true;
    }
    return false;
}
