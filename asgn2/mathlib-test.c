#include "mathlib.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define OPTIONS "aebmrvnsh"

int main(int argc, char **argv) {
    int opt = 0;

    bool test_e = false;
    bool test_bbp = false;
    bool test_madhava = false;
    bool test_euler = false;
    bool test_viete = false;
    bool test_newton = false;
    bool test_stats = false;
    bool test_help = false;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a': 
		test_e = test_bbp = test_madhava = test_euler = test_viete = test_newton = test_stats = test_help = true;
		break;
        case 'e':
		test_e = true;
		break;
        case 'b':
		test_bbp = true;
		break;
        case 'm':
		test_madhava = true;
		break;
        case 'r':
		test_euler = true;
		break;
	case 'v':
		test_viete = true;
		break;
        case 'n':
		test_newton = true;
		break;
        case 's':
		test_stats = true;
		break;
	case 'h':
		test_help = true;
		break;
        }
    }

    if (test_e){}

    if (test_bbp){
	    double pi = M_PI;
	    printf("%16.15lf", pi);
    }

    if (test_madhava){
	    double pi = M_PI;
            printf("%16.15lf", pi);
    }

    if (test_euler){
            double pi = M_PI;
            printf("%16.15lf", pi);
    }

    if (test_viete){
            double pi = M_PI;
            printf("%16.15lf", pi);
    }

    if (test_newton){}

    if (test_stats){

    }

    if (test_help){
            printf("SYNPOSIS\n\tA test harness for the small numberical library.\n");
            printf("USEAGE\n\t./mathlib-test [-aebmrvnsh]\n");
            printf("OPTIONS\n\t");
            printf("-a\tRun all tests.\n");
            printf("-e\tRuns e test.\n");
            printf("-b\tRuns BBP pi test.\n");
            printf("-m\tRuns Madhava pi test.\n");
            printf("-r\tRuns Euler pi test.\n");
            printf("-v\tRuns Viete pi test.\n");
            printf("-n\tRuns Newton square root tests.\n");
            printf("-s\tPrint verbose statistics.\n");
            printf("-h\tDisplay program synopsis and useage.");
    }

    return 0;
}

