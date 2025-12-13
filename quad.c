#include "quad.h"

double quad_lrect(fnc_t f, const void *par,
                  double a, double b, size_t n)
{
    double h = (b - a) / n;
    double r = 0.0;

    for (size_t i = 0; i < n; ++i)
        r += f(a + i * h, par);

    return r * h;
}

double quad_midrect(fnc_t f, const void *par,
                    double a, double b, size_t n)
{
    double h = (b - a) / n;
    double r = 0.0;

    for (size_t i = 0; i < n; ++i)
        r += f(a + (i + 0.5) * h, par);

    return r * h;
}

double quad_trap(fnc_t f, const void *par,
                 double a, double b, size_t n)
{
    double h = (b - a) / n;
    double r = 0.5 * (f(a, par) + f(b, par));

    for (size_t i = 1; i < n; ++i)
        r += f(a + i * h, par);

    return r * h;
}

double quad_simpson(fnc_t f, const void *par,
                    double a, double b, size_t n)
{
    if (n % 2 != 0) n++;

    double h = (b - a) / n;
    double r = f(a, par) + f(b, par);

    for (size_t i = 1; i < n; ++i)
    {
        double x = a + i * h;
        r += (i % 2 ? 4.0 : 2.0) * f(x, par);
    }

    return r * h / 3.0;
}
