#ifndef funcsglobaloffensive
#define funcsglobaloffensive

#include "types.h"
#include <stddef.h>


// обязательная
double expn(double x, const void *par);


expn_pars_t* expn_pars_create(double a, double b, double c, double d);
void expn_pars_free(expn_pars_t *p);

pol_pars_t* pol_pars_create(size_t degree, const double *coeff);
void pol_pars_free(pol_pars_t *p);

/*
 * degree — степень полинома
 * coeff  — массив коэффициентов длины degree + 1
 * Коэффициенты хранятся в следующем порядке:
 * coeff[0] — коэффициент при x^0 
 * ...
 *coeff[degree] — коэффициент при x^degree
 */


//обязательная
double pol(double x, const void *par);


/*
 * Функция sin(x).
 * Эта функция не имеет дополнительных параметров.
 * Принимает:
 *   - x   - точка вычисления
 *   - par — не используется 
 * Возвращает:
 *   - sin(x)
 */

double fsin(double x, const void *par);


/*
 * Функция cos(x).
 * Эта функция не имеет дополнительных параметров.
 * Принимает:
 *   - x   — точка вычисления
 *   - par — не используется (должен быть NULL)
 * Возвращает:
 *   - cos(x)
 */

double fcos(double x, const void *par);

#endif
