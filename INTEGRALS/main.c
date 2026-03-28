#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "quad.h"
#include "adapt.h"
#include "func.h"

int main(void) {
    fnc_t f = NULL;
    quad_t qf = NULL;
    void *par = NULL;
    int fchoice;
    
    printf("Функция:\n");
    printf("1 - exp\n2 - полином\n3 - sin\n4 - cos\n> ");
    scanf("%d", &fchoice);
    
    double *coeff = NULL;
    
    if (fchoice == 1) {
        f = expn;
        double a, b, c, d;
        printf("Введите a b c d: ");
        scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
        par = expn_pars_create(a, b, c, d);  /* ✅ Через фабрику */
    }
    else if (fchoice == 2) {
        f = pol;
        size_t degree;
        printf("Степень полинома: ");
        scanf("%zu", &degree);
        coeff = malloc((degree + 1) * sizeof(double));
        for (size_t i = 0; i <= degree; ++i) {
            printf("coeff[%zu] = ", i);
            scanf("%lf", &coeff[i]);
        }
        par = pol_pars_create(degree, coeff);  /* ✅ Через фабрику */
        free(coeff);
    }
    else if (fchoice == 3) f = fsin;
    else if (fchoice == 4) f = fcos;
    
    double a, b;
    printf("Введите a b: ");
    scanf("%lf %lf", &a, &b);
    
    int qchoice;
    printf("Квадратурная формула:\n");
    printf("1 - лев. прямоуг.\n2 - средние\n3 - трапеции\n4 - Симпсон\n> ");
    scanf("%d", &qchoice);
    
    if      (qchoice == 1) qf = quad_lrect;
    else if (qchoice == 2) qf = quad_midrect;
    else if (qchoice == 3) qf = quad_trap;
    else if (qchoice == 4) qf = quad_simpson;
    
    int mchoice;
    printf("Метод:\n1 - простой\n2 - адаптивный\n> ");
    scanf("%d", &mchoice);
    
    double res;
    if (mchoice == 1) {
        size_t n;
        printf("Введите n: ");
        scanf("%zu", &n);
        res = qf(f, par, a, b, n);
    }
    else {
        double eps;
        printf("Введите eps: ");
        scanf("%lf", &eps);
        res = quad_adapt(f, par, a, b, eps, qf);
    }
    
    printf("Результат интегрирования: %.10lf\n", res);
    
    if (fchoice == 1) expn_pars_free(par);
    else if (fchoice == 2) pol_pars_free(par);
    
    return 0;
}