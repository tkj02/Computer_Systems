#include "numtheory.h"
#include "randstate.h"
#include "rsa.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

// Contains the implementation and
// main() function for the keygen program

#define OPTIONS "b:c:n:d:s:vh"

int main(int argc, char **argv) {

    // Initializes variables for future use
    int opt = 0;
    uint64_t iters = 50;
    bool v_flag = false;
    uint64_t bits = 256;
    FILE *pubfile = NULL;
    FILE *privfile = NULL;
    unsigned long seed = time(NULL);

    // Parses through command line options
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'b': bits = atoi(optarg); break;
        case 'c': iters = atoi(optarg); break;
        case 'n': pubfile = fopen(optarg, "w"); break;
        case 'd': privfile = fopen(optarg, "w"); break;
        case 's': seed = time(NULL); break;
        case 'v': v_flag = true; break;
        case 'h':
            printf("SYNOPSIS\n   Generates an RSA public/private key pair.\n\n");
            printf("USAGE\n   ./keygen [-hv] [-b bits] -n pbfile -d pvfile\n\n");
            printf("OPTIONS\n");
            printf("   -h              Display program help and usage.\n");
            printf("   -v              Display verbose program output.\n");
            printf("   -b bits         Minimum bits needed for public key n.\n");
            printf(
                "   -c confidence   Miller-Rabin iterations for testing primes (default: 50).\n");
            printf("   -n pbfile       Public key file (default: rsa.pub).\n");
            printf("   -d pvfile       Private key file (default: rsa.priv).\n");
            printf("   -s seed         Random seed for testing.\n");
            break;
        }
    }
    // Opens public key file
    if (pubfile == NULL) {
        pubfile = fopen("rsa.pub", "w");
    }

    // Opens private key file
    if (privfile == NULL) {
        privfile = fopen("rsa.priv", "w");

        // Sets file permissions
        int fd = fileno(privfile);
        // fstat(fd, &fileStat);
        fchmod(fd, S_IRUSR | S_IWUSR);
    }

    // Initializes randstate with specified seed
    randstate_init(seed);

    // Initializes mpz_t variables
    mpz_t m, s, p, q, e, n, d;
    mpz_inits(m, s, p, q, e, n, d, NULL);

    // Makes public key and private key
    rsa_make_pub(p, q, n, e, bits, iters);
    rsa_make_priv(d, e, p, q);

    // Gets username
    char *user = getenv("USER");

    // Converts username to mpz_t variable
    mpz_init_set_str(m, user, 62);

    // Computes signature of username
    rsa_sign(s, m, d, n);

    // Writes public key to public file
    rsa_write_pub(n, e, s, user, pubfile);

    // Writes private key to private file
    rsa_write_priv(n, d, privfile);

    // Checks verbose flag
    if (v_flag) {
        printf("user = %s\n", user);
        gmp_printf("s (%d bits) = %Zd\n", mpz_sizeinbase(s, 2), s);
        gmp_printf("p (%d bits) = %Zd\n", mpz_sizeinbase(p, 2), p);
        gmp_printf("q (%d bits) = %Zd\n", mpz_sizeinbase(q, 2), q);
        gmp_printf("n (%d bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_printf("e (%d bits) = %Zd\n", mpz_sizeinbase(e, 2), e);
        gmp_printf("d (%d bits) = %Zd\n", mpz_sizeinbase(d, 2), d);
    }

    // Closes files
    fclose(pubfile);
    fclose(privfile);

    // Frees memory
    mpz_clears(m, s, p, q, e, n, d, NULL);
    randstate_clear();

    return 0;
}
