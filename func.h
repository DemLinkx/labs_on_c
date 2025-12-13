#ifndef funcsglobaloffensive
#define funcsglobaloffensive

#include <stddef.h>

struct expn_pars
{
    double a, b, c, d;
};


// обязательная
double expn(double x, const void *par);


struct pol_pars
{
    size_t degree;
    const double *coeff;
};


//обязательная
double pol(double x, const void *par);


// моя дополнительная
double fsin(double x, const void *par);


// моя дополнительная
double fcos(double x, const void *par);

#endif
