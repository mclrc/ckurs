#include "02ex.c"
#include "testrunner.c"
#include "canvas.h"


#define TEST_NAME "02ex_test"

#define TESTS_1ABC 13
#define TESTS_2A 13
#define TESTS_2B 9
#define TESTS_2C 6
#define TESTS_3A 17
#define TESTS_3B 13

typedef struct Test1 {
    int n;
    int expected_both;
    int expected_or;
    int expected_either;
} exercises_1_data;

typedef struct Test2ab
{
    int x;
    int expected;
} exercises_2ab_data;

typedef struct Test2c
{
    int a;
    int b;
    int c;
    int result;
} exercise_2c_data;

typedef struct Test3
{
    int n;
    int expected;
} exercises_3_data;


static exercises_1_data exercises_1abc [TESTS_1ABC] = {
        { .n = 0, .expected_both = 0, .expected_or = 0, .expected_either = 0 },
        { .n = 6, .expected_both = 0, .expected_or = 0, .expected_either = 0 },
        { .n = 7, .expected_both = 0, .expected_or = 7, .expected_either = 7 },
        { .n = 9, .expected_both = 0, .expected_or = 7, .expected_either = 7 },
        { .n = 13, .expected_both = 0, .expected_or = 20, .expected_either = 20 },
        { .n = 14, .expected_both = 0, .expected_or = 34, .expected_either = 34 },
        { .n = 17, .expected_both = 0, .expected_or = 34, .expected_either = 34 },
        { .n = 65, .expected_both = 0, .expected_or = 510, .expected_either = 510 },
        { .n = 91, .expected_both = 91, .expected_or = 910, .expected_either = 819 },
        { .n = 100, .expected_both = 91, .expected_or = 1008, .expected_either = 917 },
        { .n = 200, .expected_both = 273, .expected_or = 4129, .expected_either = 3856 },
        { .n = 500, .expected_both = 1365, .expected_or = 26160, .expected_either = 24795 },
        { .n = 12345, .expected_both = 835380, .expected_or = 15909457, .expected_either = 15074077 },
};

static exercises_2ab_data exercise_2a[TESTS_2A] = {
        { .x = 1, .expected = 1 },
        { .x = 0, .expected = 0 },
        { .x = -1, .expected = -1 },
        { .x = 13, .expected = 1 },
        { .x = 57, .expected = 1 },
        { .x = -45, .expected = -1 },
        { .x = -633, .expected = -1 },
        { .x = 12345, .expected = 1 },
        { .x = 135163, .expected = 1 },
        { .x = -12345, .expected = -1 },
        { .x = -432462, .expected = -1 },
        { .x = 2147483647, .expected = 1 },
        { .x = -2147483648, .expected = -1 },
};
static exercises_2ab_data exercise_2b[TESTS_2B] = {
        {.x = -1, .expected = 0},
        {.x = 0, .expected = 1},
        {.x = 1, .expected = 0},
        {.x = 4, .expected = 1},
        {.x = 5, .expected = 0},
        {.x = 200, .expected = 0},
        {.x = 1600, .expected = 1},
        {.x = 2023, .expected = 0},
        {.x = 2024, .expected = 1},
};
static exercise_2c_data exercise_2c [TESTS_2C] = {
        { .a = 0, .b = 7, .c = 3, .result = 7 },
        { .a = 1, .b = 2, .c = 3, .result = 3 },
        { .a = 0, .b = 0, .c = 0, .result = 0 },
        { .a = 178, .b = 112, .c = 245, .result = 245 },
        { .a = 100, .b = 10, .c = 1, .result = 100 },
        { .a = 3, .b = 9, .c = 6, .result = 9 },
};

static exercises_3_data exercise_3a[TESTS_3A] = {
        { .n = 0, .expected = 0 },
        { .n = 2, .expected = 1 },
        { .n = 1, .expected = 0 },
        { .n = 55, .expected = 0 },
        { .n = 10, .expected = 0 },
        { .n = 23, .expected = 1 },
        { .n = 3, .expected = 1 },
        { .n = 121, .expected = 0 },
        { .n = 777, .expected = 0 },
        { .n = 443, .expected = 1 },
        { .n = 42, .expected = 0 },
        { .n = 79, .expected = 1 },
        { .n = 1008, .expected = 0 },
        { .n = 1009, .expected = 1 },
        { .n = 9649, .expected = 1 },
        { .n = 2023, .expected = 0 },
        { .n = 17, .expected = 1 },
};
static exercises_3_data exercise_3b[TESTS_3B] = {
        { .n = 1, .expected = 2 },
        { .n = 4, .expected = 17 },
        { .n = 0, .expected = 0 },
        { .n = 10, .expected = 129 },
        { .n = 17, .expected = 440 },
        { .n = 16, .expected = 381 },
        { .n = 3, .expected = 10 },
        { .n = 6, .expected = 41 },
        { .n = 9, .expected = 100 },
        { .n = 25, .expected = 1060 },
        { .n = 42, .expected = 3447 },
        { .n = 7, .expected = 58 },
        { .n = 1024, .expected = 3875933 },
};

char* render_exercises_1abc(exercises_1_data testcase)
{
    const char *n = format_int(testcase.n);
    int len = strlen("n = ") + strlen(n) + 1;
    char *str = malloc(len);
    snprintf(str, len, "n = %s", n);
    free((char*) n);
    return str;
}
char* render_exercise_2a(exercises_2ab_data testcase)
{
    const char *x = format_int(testcase.x);
    int len = strlen("x = ") + strlen(x) + 1;
    char *str = malloc(len);
    snprintf(str, len, "x = %s", x);
    free((char*) x);
    return str;
}
char* render_exercise_2b(exercises_2ab_data testcase)
{
    const char *year = format_int(testcase.x);
    int len = strlen("year = ") + strlen(year) + 1;
    char *str = malloc(len);
    snprintf(str, len, "year = %s", year);
    free((char*) year);
    return str;
}
char* render_exercise_2c(exercise_2c_data testcase)
{
    const char *a = format_int(testcase.a);
    const char *b = format_int(testcase.b);
    const char *c = format_int(testcase.c);
    int len = strlen("a = ") + strlen(a) + strlen(", b = ") + strlen(b) + strlen(" und c = ") + strlen(c) + 1;
    char *str = malloc(len);
    snprintf(str, len, "a = %s, b = %s und c = %s", a, b, c);
    free((char*) a);
    free((char*) b);
    free((char*) c);
    return str;
}
char* render_exercises_3abc(exercises_3_data testcase)
{
    const char *n = format_int(testcase.n);
    int len = strlen("n = ") + strlen(n) + 1;
    char *str = malloc(len);
    snprintf(str, len, "n = %s", n);
    free((char*) n);
    return str;
}

int main(int argc, char const *argv[])
{
    Tester tester = tester_new(argc-1,argv[1], argv[2],
                               "cc -std=c11 -g -Wall "TEST_NAME".c -o "TEST_NAME".o -lm && ./"TEST_NAME".o");
    /* Aufgabe 1a */
    if(begin_exercise(&tester, "sum_divisible_both", "Aufgabe 1a: Summe der Vielfachen von 7 *und* 13."))
    {
        for (int i = 0; i < TESTS_1ABC; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercises_1abc(exercises_1abc[i]);
                assert_uint(&tester, exercises_1abc[i].expected_both, sum_divisible_both(exercises_1abc[i].n), args);
                free(args);
            }
        }
    }
    /* Aufgabe 1b */
    if(begin_exercise(&tester, "sum_divisible_or", "Aufgabe 1b: Summe der Vielfachen von 7 *oder* 13."))
    {
        for (int i = 0; i < TESTS_1ABC; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercises_1abc(exercises_1abc[i]);
                assert_uint(&tester, exercises_1abc[i].expected_or, sum_divisible_or(exercises_1abc[i].n), args);
                free(args);
            }
        }
    }
    /* Aufgabe 1c */
    if(begin_exercise(&tester, "sum_divisible_either", "Aufgabe 1c: Summe der Vielfachen von *entweder* 7 oder 13."))
    {
        for (int i = 0; i < TESTS_1ABC; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercises_1abc(exercises_1abc[i]);
                assert_uint(&tester, exercises_1abc[i].expected_either, sum_divisible_either(exercises_1abc[i].n),
                            args);
                free(args);
            }
        }
    }
    /* Aufgabe 2a*/
    if(begin_exercise(&tester, "signum", "Aufgabe 2a: Vorzeichenbestimmung ganzer Zahlen mit signum."))
    {
        for (int i = 0; i < TESTS_2A; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercise_2a(exercise_2a[i]);
                assert_int(&tester, exercise_2a[i].expected, signum(exercise_2a[i].x), args);
                free(args);
            }
        }
    }
    /* Aufgabe 2b*/
    if(begin_exercise(&tester, "is_leapyear", "Aufgabe 2b: Berechnung von Schaltjahren."))
    {
        for (int i = 0; i < TESTS_2B; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercise_2b(exercise_2b[i]);
                assert_int(&tester, exercise_2b[i].expected, is_leapyear(exercise_2b[i].x), args);
                free(args);
            }
        }
    }
     /* Aufgabe 2c */
     if(begin_exercise(&tester, "greatest_of_three", "Aufgabe 2c: Vergleichen und heraussuchen des größten Werts."))
     {
         for (int i = 0; i < TESTS_2C; i++)
         {
             if(begin_testcase(&tester))
             {
                 if (tester.successful)
                 {
                     char *args = render_exercise_2c(exercise_2c[i]);
                     int compiled_res = greatest_of_three(exercise_2c[i].a, exercise_2c[i].b, exercise_2c[i].c);
                     assert_int(&tester, exercise_2c[i].result, compiled_res, args);
                     free(args);
                 }
             }
         }
     }
    /* Aufgabe 3a */
    if(begin_exercise(&tester, "is_prime", "Aufgabe 3a: Zurückgeben ob eine Zahl eine Primzahl ist oder nicht."))
    {
        for (int i = 0; i < TESTS_3A; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercises_3abc(exercise_3a[i]);
                assert_int(&tester, exercise_3a[i].expected, is_prime(exercise_3a[i].n), args);
                free(args);
            }
        }
    }
    /* Aufgabe 3b */
    if(begin_exercise(&tester, "sum_first_primes", "Aufgabe 3b: Summe der ersten n Primzahlen ausrechnen."))
    {
        for (int i = 0; i < TESTS_3B; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercises_3abc(exercise_3b[i]);
                assert_int(&tester, exercise_3b[i].expected, sum_first_primes(exercise_3b[i].n), args);
                free(args);
            }
        }
    }

    return wrap_up(&tester);
}