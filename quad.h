#ifndef quadadada
#define quadadada

#include <stddef.h>

typedef double (*fnc_t)(double x, const void *par);

double quad_midrect(fnc_t f, const void *par,
                    double a, double b, size_t n);

double quad_lrect(fnc_t f, const void *par,
                  double a, double b, size_t n);

double quad_trap(fnc_t f, const void *par,
                 double a, double b, size_t n);

double quad_simpson(fnc_t f, const void *par,
                    double a, double b, size_t n);

#endif
