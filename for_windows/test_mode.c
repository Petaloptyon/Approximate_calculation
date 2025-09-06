#include "functions.h"
double idx(double x)  {return 3;}
func funcs[] = {idx, _f1, _f2, _f3, _df1, _df2, _df3};
// Function to compute the three intersection points of f1,f2,f3 on predefined intervals
void calc_intersection(double *x1, double *x2, double *x3) {
    // Pre-known intervals where the intersection points are located
    *x1 = root(_f1, _f3, _df1, _df3, -1.9, -0.2, EPSILON);
    *x2 = root(_f2, _f3, _df2, _df3, -1.0, -0.1, EPSILON);
    *x3 = root(_f1, _f2, _df1, _df2, 0.1,  1.0, EPSILON);
}
// ----------------------------------------------------------------------------------
//                                    main
// ----------------------------------------------------------------------------------
int main(int argc, char *argv[]) {
    int opt;
    struct option long_opts[] = {
        {"help", no_argument, 0, 'h'},
        {"root", no_argument, 0, 'r'},
        {"iterations", no_argument, 0, 'i'},
        {"test-root", required_argument, 0, 'R'},
        {"test-integral", required_argument, 0, 'I'},
        {0,0,0,0}
    };
    double x1, x2, x3;
    // Parse command-line options via getopt_long
    while ((opt = getopt_long(argc, argv, "hriR:I:", long_opts, NULL)) != -1) {
        switch (opt) {
            case 'h':
                // Print usage help
                printf("Usage:\n"
                       "  -h, --help              Show this help message\n"
                       "  -r, --root              Compute intersections of f1,f2,f3\n"
                       "  -i, --iterations        Display number of iterations used in last root search\n"
                       "  -R, --test-root=...     Test root (format f1:f2:a:b:eps:expected)\n"
                       "  -I, --test-integral=... Test integral (format f:a:b:eps:expected)\n");
                break;
            case 'r':
                // Compute the three intersection points and print them
                calc_intersection(&x1, &x2, &x3);
                printf("    functions    \tx  \ty\n");
                printf("between f1 and f2 %.6lf, %.6lf\n", x3, _f1(x3));
                printf("between f2 and f3 %.6lf, %.6lf\n", x2, _f2(x2));
                printf("between f1 and f3 %.6lf, %.6lf\n", x1, _f1(x1));
                break;
            case 'i':
                // First compute intersections, then show the iteration counter
                calc_intersection(&x1, &x2, &x3);
                printf("root_iterations=%d\n", root_iterations);
                break;
            case 'R': {
                // Root-finding test with given parameters
                int f1, f2;
                double a, b, eps, expval;
                sscanf(optarg, "%d:%d:%lf:%lf:%lf:%lf", &f1, &f2, &a, &b, &eps, &expval);
                test_root(f1, f2, a, b, eps, expval);
                break;
            }
            case 'I': {
                // Integral test with given parameters
                int f;
                double a, b, eps, expval;
                sscanf(optarg, "%d:%lf:%lf:%lf:%lf", &f, &a, &b, &eps, &expval);
                test_integral(f, a, b, eps, expval);
                break;
            }
            default:
                fprintf(stderr, "Unknown option\n");
                return 1;
        }
    }
    // If the program is run without arguments, compute the area of the figure:
    if (argc == 1) {
        calc_intersection(&x1, &x2, &x3);
        double area = 0.0;
        // Area = integral (f1-f3) on [x1,x2] + integral (f2-f3) on [x2,x3]
        area += integral(_f1, x1, x2, EPSILON) - integral(_f3, x1, x2, EPSILON);
        area += integral(_f2, x2, x3, EPSILON) - integral(_f3, x2, x3, EPSILON);
        printf("area = %.6f\n", fabs(area));
    }
    return 0;
}
