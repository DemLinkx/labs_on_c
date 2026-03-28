#include "func.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>  


struct expn_pars {
    double a, b, c, d;
};

struct pol_pars {
    size_t degree;
    double *coeff;  /* Копия массива */
};

expn_pars_t* expn_pars_create(double a, double b, double c, double d) {
    expn_pars_t *p = malloc(sizeof(*p));
    if (!p) return NULL;
    p->a = a; p->b = b; p->c = c; p->d = d;
    return p;
}

void expn_pars_free(expn_pars_t *p) {
    free(p);
}

pol_pars_t* pol_pars_create(size_t degree, const double *coeff) {
    pol_pars_t *p = malloc(sizeof(*p));
    if (!p) return NULL;
    p->degree = degree;
    p->coeff = malloc((degree + 1) * sizeof(double));
    if (!p->coeff) {
        free(p);
        return NULL;
    }
    memcpy(p->coeff, coeff, (degree + 1) * sizeof(double));
    return p;
}

void pol_pars_free(pol_pars_t *p) {
    if (p) {
        free(p->coeff);
        free(p);
    }
}


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
