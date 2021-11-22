#include "numtheory.h"
#include "randstate.h"
#include "rsa.h"

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

// Contains the implementation and
// main() function for the decrypt program

#define OPTIONS "i:o:n:vh"

int main(int argc, char **argv) {

    int opt = 0;

    FILE *fi = stdin;
    FILE *fout = stdout;
    bool v_flag = false;
    mpz_t n, e, d;
    mpz_inits(n, e, d, NULL);
    FILE *fp = NULL;

    // Parses through command line options
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i':
            fi = fopen(optarg, "r");
            if (fi == NULL) {
                printf("error opening infile for reading\n");
                goto exit;
            }
            break;
        case 'o':
            fout = fopen(optarg, "w");
            if (fout == NULL) {
                printf("error opening outfile for writing\n");
                goto exit;
            }
            break;
        case 'n':
            fp = fopen(optarg, "r");
            if (fp == NULL) {
                printf("error opening private key file");
                goto exit;
            }
            break;
        case 'v': v_flag = true; break;
        case 'h':
            printf("SYNOPSIS\n   Encrypts data using RSA encryption.\n");
            printf("   Encrypted data is decrypted by the decrypt program.\n\n");
            printf("USAGE\n   ./encrypt [-hv] [-i infile] [-o outfile] -n pubkey -d privkey\n\n");
            printf("OPTIONS\n");
            printf("   -h              Display program help and usage.\n");
            printf("   -v              Display verbose program output.\n");
            printf("   -i infile       Input file of data to encrypt (default: stdin).\n");
            printf("   -o outfile      Output file for encrypted data (default: stdout).\n");
            printf("   -n pbfile       Public key file (default: rsa.priv).\n");
            break;
        }
    }

    // Opens private key file
    if (fp == NULL) {
        fp = fopen("rsa.priv", "r");
        if (fp == NULL) {
            printf("file rsa.priv not found\n");
            goto exit;
        }
    }

    // Reads private key file
    rsa_read_priv(n, d, fp);

    // If verbose is enabled, prints values
    if (v_flag) {
        gmp_printf("n (%d bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_printf("e (%d bits) = %Zd\n", mpz_sizeinbase(e, 2), e);
    }

    // Decrypts file
    rsa_decrypt_file(fi, fout, n, d);

exit:
    fclose(fp);
    if (fi != stdin) {
        fclose(fi);
    }
    if (fout != stdout) {
        fclose(fout);
    }
    mpz_clears(n, e, d, NULL);

    return 0;
}
