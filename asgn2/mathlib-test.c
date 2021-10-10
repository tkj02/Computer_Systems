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
            test_e = test_bbp = test_madhava = test_euler = test_viete = test_newton = test_stats
                = test_help = true;
            break;
        case 'e': test_e = true; break;
        case 'b': test_bbp = true; break;
        case 'm': test_madhava = true; break;
        case 'r': test_euler = true; break;
        case 'v': test_viete = true; break;
        case 'n': test_newton = true; break;
        case 's': test_stats = true; break;
        case 'h': test_help = true; break;
        }
    }

    //  if (test_e){
    //	    double e = M_E;
    //          double my_e = e();
    //        double diff = absolute(e-my_e);
    //      printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf", my_e, e, diff);
    // }

    if (test_bbp) {
        double pi = M_PI;
        double my_bbp = pi_bbp();
        double diff = absolute(pi - my_bbp);
        printf("pi_bbp() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf", my_bbp, pi, diff);
    }

    if (test_madhava) {
        double pi = M_PI;
        double my_madhava = pi_madhava();
        double diff = absolute(pi - my_madhava);
        printf("pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf", my_madhava, pi, diff);
    }

    if (test_euler) {
        double pi = M_PI;
        double my_euler = pi_euler();
        double diff = absolute(pi - my_euler);
        printf("pi_euler() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf", my_euler, pi, diff);
    }

    if (test_viete) {
        double pi = M_PI;
        double my_viete = pi_viete();
        double diff = absolute(pi - my_viete);
        printf("pi_viete() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf", my_viete, pi, diff);
    }

    if (test_newton) {
        for (double i = 0.000000; i < 10.000000; i += 0.100000) {
            double my_sqrt = sqrt_newton(i);
            double m_sqrt = sqrt(i);
            double diff = absolute(my_sqrt - m_sqrt);
            printf("sqrt_newton(%16.6lf) = %16.15lf, sqrt(%16.6lf) = %16.15lf, diff = %16.15lf\n",
                i, my_sqrt, i, m_sqrt, diff);
        }
    }

    if (test_stats) {
    }

    if (test_help) {
        printf("SYNOPSIS\n   A test harness for the small numberical library.\n\n");
        printf("USAGE\n   ./mathlib-test [-aebmrvnsh]\n\n");
        printf("OPTIONS\n");
        printf("  -a   Run all tests.\n");
        printf("  -e   Runs e test.\n");
        printf("  -b   Runs BBP pi test.\n");
        printf("  -m   Runs Madhava pi test.\n");
        printf("  -r   Runs Euler pi test.\n");
        printf("  -v   Runs Viete pi test.\n");
        printf("  -n   Runs Newton square root tests.\n");
        printf("  -s   Print verbose statistics.\n");
        printf("  -h   Display program synopsis and useage.\n");
    }

    return 0;
}
