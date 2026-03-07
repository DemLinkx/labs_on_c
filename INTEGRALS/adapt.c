#include "adapt.h"
#include <math.h>

double quad_adapt(fnc_t f, const void *par,
                  double a, double b, double eps,
                  quad_t qf)
{
    size_t n = 2;
    double prev = qf(f, par, a, b, n);
    double curr;

    while (1)
    {
        n *= 2;
        curr = qf(f, par, a, b, n);

        if (fabs(curr - prev) / fabs(curr) < eps)
            return curr;

        prev = curr;
    }
}
