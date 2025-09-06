#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h>

#define EPSILON 0.000001
typedef double (*func)(double);
extern func funcs[];
double idx(double x);

#ifdef TEST_MODE
double test_f1(double x);
double test_f2(double x);
double test_f3(double x);
double test_df1(double x);
double test_df2(double x);
double test_df3(double x);
double test_f4(double x);
double test_df4(double x);

#else
extern double _f1(double x);
extern double _f2(double x);
extern double _f3(double x);
extern double _df1(double x);
extern double _df2(double x);
extern double _df3(double x);


#endif

double root(func f, func g, func df, func dg, double a, double b, double eps);
double integral(func f, double a, double b, double eps);
double simpson(func f, double a, double b, int n);
void calc_intersection(double *x1, double *x2, double *x3);
int root_iterations;
void test_root(int f1_num, int f2_num, double a, double b, double eps, double expected);
void test_integral(int f_num, double a, double b, double eps, double expected);

#endif