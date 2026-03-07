#include "func.h"
#include <math.h>

double expn(double x, const void *par)
{
    const struct expn_pars *p = par;
    return p->a * exp(p->b * x + p->c) + p->d;
}

double pol(double x, const void *par)
{
    const struct pol_pars *p = par;
    double r = 0.0;

    /* схема Горнера */
    for (size_t i = p->degree; i-- > 0;)
        r = r * x + p->coeff[i];

    return r;
}

double fsin(double x, const void *par)
{
    (void)par;
    return sin(x);
}

double fcos(double x, const void *par)
{
    (void)par;
    return cos(x);
}
