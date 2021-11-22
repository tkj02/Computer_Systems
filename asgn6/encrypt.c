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
// main() function for the encrypt program

#define OPTIONS "i:o:n:vh"

int main(int argc, char **argv) {

#if 0
    mpz_t nn;
    mpz_init(nn);
    for (int i = 10; i < 100; i++) {

        int num = i;
        mpz_set_ui(nn, num);
        //	gmp_printf("%Zd\n", nn);
        uint64_t iter = 30;

        bool flag = false;
        flag = is_prime(nn, iter);

        printf("%d %s\n", num, flag ? "true" : "false");
    }
    return 0;
#endif

    // Initializes variables
    int opt = 0;

    FILE *fi = stdin;
    FILE *fout = stdout;
    bool v_flag = false;
    mpz_t n, e, s;
    mpz_inits(n, e, s, NULL);
    char username[256];
    FILE *fp;
    const char *fpub = "rsa.pub";

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
            fp = fopen(optarg, "r"); //fpub
            if (fpub == NULL) {
                printf("error opening public key file");
                goto exit;
            }
            //	    fpub = optarg;
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
            printf("   -n pbfile       Public key file (default: rsa.pub).\n");
            break;
        }
    }

    // Opens public key file
    // Prints error message if opening fails
    fp = fopen(fpub, "r");
    if (fpub == NULL) {
        printf("error opening public key file");
        goto exit;
    }

    // Reads public key file
    rsa_read_pub(n, e, s, username, fp);

    // If verbose is enabled, prints values
    if (v_flag) {
        printf("user = %s\n", username);
        printf("s (%zu bits) = %lu\n", mpz_sizeinbase(s, 2), mpz_get_ui(s));
        printf("n (%zu bits) = %lu\n", mpz_sizeinbase(n, 2), mpz_get_ui(n));
        printf("e (%zu bits) = %lu\n", mpz_sizeinbase(e, 2), mpz_get_ui(e));
    }

    // Converts username to mpz_t
    mpz_t user;
    mpz_init(user);
    mpz_set_str(user, username, 5);
    // check third parameter        ^

    // Verifies signature
    bool stat = rsa_verify(user, s, e, n);
    if (stat == false) {
        printf("error verifying signature");
        goto exit;
    }

    // Encrypts file
    rsa_encrypt_file(fi, fout, n, e);

exit:
    fclose(fp);
    if (fi != stdin) {
        fclose(fi);
    }
    if (fout != stdout) {
        fclose(fout);
    }
    mpz_clears(n, e, s, user, NULL);

    return 0;
}
