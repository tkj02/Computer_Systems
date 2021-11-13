#include "ranstate.h"
#include <stdio.h>
#include <stdlib.h>

// Contains the implementation of the
// random state interface for
// the RSA library and number theory functions

// Initializes state using seed
void randstate_init(uint64_t seed) {
	gmp_randinit_mt(state);
	gmp_randseed_ui(state, seed);
}

// Clears and frees memory used by state
void randstate_clear(void) {
	 gmp_randclear(state);
}
