Assignment 6 - Public Key Encryption

Purpose: The purpose of this assignment is to implement encryptors and decryptors that can manipulate public and private RSA keys, which are generated in this assignment as well. numtheory.c contains the implementation of modular math functions that will be used for this purpose. randstate.c generates the state needed to create the large values for the keys and the values they need to be calculated. rsa.c reads and writes from/to files and encrypts and decrypts the keys to their respective files, which will be used a lot in the main test files. keygen.c creates these keys, encrypt.c writes the public key to the outfile, and decrypt.c writes the private key to the outfile. All three of these files can run with command line options as described below.

Build and Run: To compile the main test harnesses keygen.c, encrypt.c, and decrypt.c and create the executable files keygen, encrypt, and decrypt, run `$ make` or `$ make all`. Next, run `$ ./keygen` with any combination of the command line arguments b, i, n, d, s, v, and h. The first five options can take on values from the user. Then, run `$ ./encrypt` with any of the options i, o, n, v, and h. The first three options can take on user values. Finally, run `$ ./decrypt` with any of the same options as encrypt for the same purposes.

Files:
- randstate.h specifies the interface for initializing and clearing the random state
- randstate.c contains the implementation of the random state interface for the RSA library and number theory functions
- numtheory.h specifies the interface for the number theory functions
- numtheory.c contains the implementations of the number theory functions
- rsa.h specifies the interface for the RSA library
- rsa.c contains the implementation of the RSA library
- keygen.c contains the implementation and main() function for the keygen program
- encrypt.c contains the implementation and main() function for the encrypt program
- decrypt.c contains the implementation and main() function for the decrypt program
- Makefile contains information for compiling, formatting, and removing object files and executables
- README.md describes program and Makefile
- DESIGN.pdf includes design/design process, pseudocode, and explanations

Command Line Arguments (for keygen):
- -b : specifies the minimum bits needed for the public modulus n 
- -c : specifies the number of Miller-Rabin iterations for testing primes, or the confidence of the primality (default: 50)
- -n pbfile : specifies the public key file (default: rsa.pub)
- -d pvfile : specifies the private key file (default: rsa.priv)
- -s : specifies the random seed for the random state initialization (default: the seconds since the UNIX epoch, given by time(NULL))
- -v : enables verbose output (prints the username, s, p, q, n, e, and d)
- -h : displays program synopsis and usage

Command Line Arguments (for both encrypt and decrypt):
- -i : specifies the input file to encrypt (default: stdin)
- -o : specifies the output file to encrypt (default: stdout)
- -n : specifies the file containing the public key (default: rsa.pub)
- -v : enables verbose output (prints the username, s, n, and e for encrypt and prints n and d for decrypt)
- -h : displays program synopsis and usage

Assistance:

- Read https://gmplib.org/manual/ and referred to it a lot
    -     https://gmplib.org/manual/Formatted-Output-Functions
    -     https://gmplib.org/manual/Initializing-Integers
    -     https://gmplib.org/manual/Assigning-Integers
    -     https://gmplib.org/manual/Integer-Arithmetic
    -     https://gmplib.org/manual/Integer-Division
    -     https://gmplib.org/manual/Integer-Comparisons
    -     https://gmplib.org/manual/Integer-Division
    -     https://gmplib.org/manual/Converting-Integers
    -     https://gmplib.org/manual/Integer-Random-Numbers
    -     https://gmplib.org/manual/Miscellaneous-Integer-Functions
    -     https://gmplib.org/manual/Integer-Import-and-Export

- Read about stdin and stdout at https://user-web.icecube.wisc.edu/~dglo/c_class/stdio.html
- Rewatched class lecture on cryptography and looked over lecture slides
- Watch both of Eugene’s recorded sections on YuJa (learned about the assignment overall, how encryption and decryption work, how to write r as an odd number in Miller-Rabin, and how to go about doing rsa.c)
- Watched Christian’s recorded section on YuJa (learned to navigate the gmp library and about the different kinds of variables and ways to complete arithmetic operations)
- Learned about what UNIX epoch time is and how it works from my dad
- Referred to my assignment five and four files, especially for reading/writing files and setting default files as they were similar to what I needed to do here for this assignment
- Referred to class discussions on ed (especially on when to call rsa_decrypt and how to debug certain issues)

Citations:
- Assignment document: I followed the pseudocode provided on the assignment document for the following portions of my code:
    - pow_mod (page 8)
    - is_prime (page 10)
    - gcd (page 11)
    - mod_inverse (page 12)

There are no known errors according to scan-build, but it does raise warnings on "Result of 'malloc' is converted to a pointer of type 'uint8_t,' which is incompatible with sizeof operand type 'size_t". This results from me allocating a uint8_t pointer block of sizeof(k), where k is size_t, but my code still allocates memory and this block is still valid.
