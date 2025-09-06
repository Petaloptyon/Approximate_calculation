#include "functions.h"
// ----------------------------------------------------------------------------------
//                              Testing functions
// ----------------------------------------------------------------------------------
// Root testing function: compares the result with the expected value and prints the error
void test_root(int f1_num, int f2_num, double a, double b, double eps, double expected) {
    int sdvg = funcs[0](0);
    double res = root(funcs[f1_num], funcs[f2_num], funcs[f1_num + sdvg], funcs[f2_num + sdvg], a, b, eps);
    double err = fabs(res - expected);
    double rel_err;
    if (expected - res < 0.000001 && expected - res > -0.000001) {
        rel_err = 0;
    } else {
        rel_err = err / fabs(expected) * 100.0;
    }
    printf("root=%.4f, error=%.4f (%.2f%%)\n", res, err, rel_err);
}
// Integral testing function: similarly, with relative error calculation
void test_integral(int f_num, double a, double b, double eps, double expected) {
    double res = integral(funcs[f_num], a, b, eps);
    double err = fabs(res - expected);
    double rel_err;
    if (expected - res < 0.000001 && expected - res > -0.000001) {
        rel_err = 0;
    } else {
        rel_err = err / fabs(expected) * 100.0;
    }
    printf("integral=%.4f, error=%.4f (%.2f%%)\n", res, err, rel_err);
}
// ----------------------------------------------------------------------------------
//                             Root finding (root)
// ----------------------------------------------------------------------------------
int root_iterations = 0;  // Iteration counter (global, for the --iterations option)
/*
Combined method for finding the root of the equation F(x)=f(x)-g(x)=0
The method combines the secant method and Newton's method for efficient root finding.
At each step:
1. The midpoint of the interval and the derivatives at this point are computed
2. Depending on the signs of the derivatives, an update scheme for the boundaries is chosen
3. The secant method is applied to one boundary and Newton's method to the other
4. The process repeats until the specified accuracy is achieved
*/
double root(func f, func g, func df, func dg, double a, double b, double eps) {
    // Reset the iteration counter on each call
    if (a > b) {
        double tmp = a;
        a = b;
        b = tmp;
    }
    double fa = f(a) - g(a);
    double fb = f(b) - g(b);
    // Check for a root at the boundary points
    if (fa <= 0.000001 && fa > -0.000001) return a;
    if (fb <= 0.000001 && fb > -0.000001) return b;
    // Verify the condition for the existence of a root on the interval
    if (fa * fb > 0) {
        printf("No root on interval [%.6f, %.6f]\n", a, b);
        exit(1);
    }
    // Variables for midpoint, and first and second derivatives of F
    double mid, Fp, Fpp;
    int case_num;
    // Main loop: narrow the segment until its length > eps
    do {
        root_iterations++;
        // 1) Curvature estimation: find mid = (a+b)/2 and compute F'(mid), F''(mid)
        mid = 0.5 * (a + b);
        Fp = df(mid) - dg(mid);
        
        // Compute the second derivative numerically
        double h = (b - a) * 0.01; // Small shift
        double Fp_left = df(mid - h) - dg(mid - h);
        double Fp_right = df(mid + h) - dg(mid + h);
        Fpp = (Fp_right - Fp_left) / (2 * h);
        // 2) Scheme selection: if F'(mid) and F''(mid) have the same sign → case 1, otherwise case 2
        case_num = (Fp * Fpp > 0) ? 1 : 2;
        // 3) Secant step (chord) on the current interval [a,b]
        //    secant formula: x = (a*F(b) - b*F(a)) / (F(b) - F(a))
        double c_chord = (a * fb - b * fa) / (fb - fa);
        // 4) Newton step (tangent) from the point d = (case==1 ? b : a)
        double d  = (case_num == 1 ? b : a);
        double Fd = f(d) - g(d);
        double Fpd = df(d) - dg(d);
        double c_newt = d - Fd / Fpd;
        // 5) Update the boundaries:
        //    - case 1: [a,b] → [c_chord, c_newt]
        //    - case 2: [a,b] → [c_newt, c_chord]
        if (case_num == 1) {
            a = c_chord;
            b = c_newt;
        } else {
            a = c_newt;
            b = c_chord;
        }
        // 6) Compute new F(a), F(b) for the next iteration
        fa = f(a) - g(a);
        fb = f(b) - g(b);
    } while (fabs(b - a) > eps);
    // Return the midpoint of the last segment as the root approximation
    return 0.5 * (a + b);
}
// ----------------------------------------------------------------------------------
//                          Simpson's method (integral)
// ----------------------------------------------------------------------------------
/*
Simpson's formula: I ≈ (h/3)[f(a) + 4f(a+h) + 2f(a+2h) + 4f(a+3h) + ... + f(b)]
*/
double simpson(func f, double a, double b, int n) {
    if (n % 2 != 0) {
        fprintf(stderr, "Error: n must be even\n");
        exit(1);
    }
    double h = (b - a) / n;
    double sum = f(a) + f(b); // Endpoints
    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += (i % 2 == 0) ? 2 * f(x) : 4 * f(x);
    }
    return (h / 3.0) * sum;
}
// Simpson's method using repeated summation
double integral(func f, double a, double b, double eps2) {
    const double p = 1.0 / 15.0; // Runge coefficient for Simpson's method
    int n = 2; // initial (minimum) even number of subintervals
    const int max_n = 5000000; // safeguard against infinite loop
    double fa = f(a), fb = f(b);
    double h = (b - a) / n;
    // initial "odd" point and first approximation
    double sum_odd = f(a + h);
    double I_n = (h / 3.0) * (fa + 4.0 * sum_odd + fb);
    while (1) {
        int n2 = n * 2;
        double h2 = (b - a) / n2;
        // sum f at the new "odd" points of the 2n-grid
        double sum_new_odd = 0.0;
        for (int i = 1; i < n2; i += 2) {
            // here i = 1,3,5,... — all odd nodes of the new grid
            sum_new_odd += f(a + i * h2);
        }
        // recompute I for 2n subintervals:
        // the old "odd" nodes become "even" (coefficient 2),
        // the new ones remain "odd" (coefficient 4)
        double I_2n = (h2 / 3.0) * (fa + fb + 2.0 * sum_odd + 4.0 * sum_new_odd);
        // check using Runge's rule
        if (p * fabs(I_n - I_2n) < eps2) {
            return I_2n;
        }
        // prepare for the next iteration
        sum_odd += sum_new_odd;  // all "odd" for 2n are now in sum_odd
        I_n = I_2n;
        n = n2;
        if (n > max_n) {
            fprintf(stderr, "Error: maximum number of intervals exceeded (%d)\n", max_n);
            return I_2n;
        }
    }
}
