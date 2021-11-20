
//! @file
//! @mainpage
//!
//! Meow!!!
//!

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef enum _TEST_CODE {FAILED = -1, PASSED = 0} TEST_CODE;

const double PRECISION = 1e-4;
const int INF_N_ROOTS = 3;


/**
 Function solves square root

 @param  [in]  a        x^2 coeef
 @param  [in]  b        x coeef
 @param  [in]  c        free coeef
 @param  [out] x1       pointer to 1st root
 @param  [out] x2       pointer to 2nd root

 @return Number of roots (3 = infinite)

 @note  if nroots = 2 then x1 > x2
*/

int solve_sqrt (float a, float b, float c, float* x1, float* x2);

/**
 Function testing solution

*/

TEST_CODE do_test();

/**
 Function compare with 0
 @param [in]    a   x^2 coeef
 @param [in]    b   x coeef
 @param [in]    c   free coeef
 @param [out]   True or false


*/

int cmp_double (double x1, double x2);

/**
 Function processes the test result
 @param  [in]  a        x^2 coeef
 @param  [in]  b        x coeef
 @param  [in]  c        free coeef
 @param  [in]  ca_se    true number of roots
 @param  [in]  x_1      true roots
 @param  [in]  x_2      true roots
 @param  [out] x1       pointer to 1st root
 @param  [out] x2       pointer to 2nd root

*/

int test_solve_sqrt (float  a, float b, float c, int ca_se, float x_1, float x_2);

/**
 Function solves square root

 @param  [in]  a        x^2 coeef
 @param  [in]  b        x coeef
 @param  [in]  c        free coeef
 @param  [out] x1       pointer to 1st root
 @param  [out] x2       pointer to 2nd root

 @return Number of roots (3 = infinite)

 @note  if nroots = 2 & c !=0 then x1 > x2
 @note Please enter coefficient a, b, c
*/

int main ()
    {
    if (do_test() == FAILED)
        {
        printf ("тест не пройден \n");
        return 0;
        }


    float a = NAN, b = NAN, c = NAN, x1 = NAN, x2 = NAN;

    int scan = scanf ("%f %f %f", &a, &b, &c);


    if (scan < 3) // проверка на введенные данные
        {
        printf ("Ввод данных неверный");
        }
    else
        {
        int nroots = solve_sqrt (a, b, c, &x1, &x2);
        printf ("%d \n", nroots);

        switch (nroots) // печать ответа
            {
            case 0:
                printf ("Корни уравнения отсутствуют");
                break;

            case 1:
                printf ("Корни уравнения: %0.2f",       x1);
                break;

            case 2:
                printf ("Корни уравнения: %0.2f,%0.2f", x1, x2);
                break;

            case INF_N_ROOTS:
                printf ("Бесконечное количество корней");
                break;

            default:
                printf ("невозможный случай %d", nroots) ;
                break;
             }
         }
    return 0;
    }


int cmp_double (double x1, double x2)
    {
    return (fabs (x1 - x2) < PRECISION);
    }


int solve_sqrt (float a, float b, float c, float* x1, float* x2)
    {
    assert (isfinite (a));
    assert (isfinite (b));
    assert (isfinite (c));

    assert (x1 != NULL);
    assert (x2 != NULL);
    assert (x1 != x2);

    float D = b * b - 4 * a * c;
    float sqrt_D = (float) sqrt (D);

    if (cmp_double (c, 0) && !cmp_double (a, 0) && !cmp_double (b, 0))
        {
        *x1 = 0;
        *x2 = -b/a;

        return 2;
        }


    if (cmp_double (a, 0))
        {
        if (cmp_double (b, 0))
            {
            if (cmp_double (c, 0))
                {
                return 3;
                }
            else
                {
                return 0;
                }
            }
        else
            {
            *x1 = -c / b;
            return 1;
            }

        }
    else
        {
        if (D < 0)
            {
            return 0;
            }
        else
            {
            if (cmp_double (D, 0))
                {
                *x1 = *x2 = (-b + sqrt_D) / 2 / a;
                return 1;
                }
            else
                {
                *x1 = (-b + sqrt_D) / 2 / a;
                *x2 = (-b - sqrt_D) / 2 / a;
                return 2;
                }
            }
        }
    }


TEST_CODE do_test()
    {
                      // a  b  c  nr x1 x2   nr=nroots
    if (test_solve_sqrt (0, 0, 1, 0, 0, 0))
        {
        return FAILED;
        }

    if (test_solve_sqrt (2, 1, 1000, 0, 0, 0))
        {
        return FAILED;
        }

    if (test_solve_sqrt (0, 2, 1000, 1, -500, -500))
        {
        return FAILED;
        }

    if (test_solve_sqrt (1, 2, 1, 1, -1, -1))
        {
        return FAILED;
        }

    if (test_solve_sqrt (1, 5, 4, 2, -1, -4))
        {
        return FAILED;
        }

    if (test_solve_sqrt (0, 0, 0, INF_N_ROOTS, 0, 0))
        {
        return FAILED;
        }

    return PASSED;
    }


int test_solve_sqrt (float a, float b, float c, int nroots, float Ref_x1, float Ref_x2)
    {

    float x1 = NAN, x2 = NAN;

    if (nroots == solve_sqrt (a, b, c, &x1, &x2))
        {
        switch (nroots)
            {
            case 0:
                return PASSED;
                break;

            case 1:
                if (cmp_double (x1, Ref_x1))
                    {
                    return PASSED;
                    }

                break;

            case 2:
                if (cmp_double (x1, Ref_x1) && cmp_double (x2, Ref_x2))
                    {
                    return PASSED;
                    }

                break;

            case INF_N_ROOTS:
                return PASSED;
                break;

            default:
                printf ("Такое невозможно \n");
                break;
            }
        }

    printf ("%.2f %.2f %.2f faild \n ne vernye korny : %.2f %.2f  ", a, b, c, x1, x2);

    return 1;
    }

