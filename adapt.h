#ifndef adaptato
#define adaptato
#include "quad.h"


double quad_adapt(fnc_t f, const void *par,
                  double a, double b, double eps,
                  quad_t qf);

#endif
