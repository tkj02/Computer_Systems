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

    int opt = 0;
    uint64_t iters = 50;
    bool v_flag = false;
    uint64_t bits = 16;
    unsigned long seed = time(NULL);

    // Parses through command line options
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'b': bits = atoi(optarg); break;
        case 'c': iters = atoi(optarg); break;
        case 'n': break;
        case 'd': break;
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
    randstate_init(seed);
    mpz_t p, q, e, n, d;
    mpz_inits(p, q, e, n, d, NULL);

    rsa_make_pub(p, q, n, e, bits, iters);
    printf("key\n");
    //rsa_make_priv(d, e, p, q);
    (void) d;

    // Freeing memory
    mpz_clears(p, q, e, n, d, NULL);
    randstate_clear();

    return 0;
}
