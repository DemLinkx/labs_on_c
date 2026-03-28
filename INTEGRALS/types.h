#ifndef type_krytoi_da
#define type_krytoi_da

#include <stddef.h>

typedef double (*fnc_t)(double x, const void *par);
typedef double (*quad_t)(fnc_t f, const void *par,
                         double a, double b, size_t n);

typedef struct expn_pars expn_pars_t;
typedef struct pol_pars pol_pars_t;

#endif