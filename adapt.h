#ifndef adaptato
#define adaptato
#include "quad.h"

typedef double (*fnc_t)(double x, const void *par);

typedef double (*quad_t)(fnc_t f, const void *par,
                         double a, double b, size_t n);

double quad_adapt(fnc_t f, const void *par,
                  double a, double b, double eps,
                  quad_t qf);

#endif
