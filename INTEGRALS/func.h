#ifndef funcsglobaloffensive
#define funcsglobaloffensive

#include <stddef.h>

struct expn_pars
{
    double a, b, c, d;
};


// обязательная
double expn(double x, const void *par);


/*
 * degree — степень полинома
 * coeff  — массив коэффициентов длины degree + 1
 * Коэффициенты хранятся в следующем порядке:
 * coeff[0] — коэффициент при x^0 
 * ...
 *coeff[degree] — коэффициент при x^degree
 */

struct pol_pars
{
    size_t degree;
    const double *coeff;
};


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
