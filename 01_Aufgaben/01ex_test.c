#include "01ex.c"
#include "testrunner.c"
#include "canvas.h"

#define RELATIVE_DIRECTORY_PATH "Testdata/"
#define TEST_NAME "01ex_test"

#define TESTS_1B 8
#define TESTS_2A 5
#define TESTS_3A 5
#define TESTS_3B 5
#define TESTS_4A 8
#define TESTS_4B 8


typedef struct Test1
{
    int x;
    int y;
    int result;
} exercises1_data;

typedef struct Test2
{
    int a;
    int b;
    int c;
    int result;
} exercises2_data;

typedef struct Test3_and_4
{
    int n;
    int result;
} exercises3_and_4_data;

static exercises1_data exercise_1b [TESTS_1B] = {
        { .x = 0, .y = 0, .result = 0 },
        { .x = 1, .y = 1, .result = 0 },
        { .x = 12, .y = 11, .result = 1 },
        { .x = 87, .y = 101, .result = 196 },
        { .x = 14, .y = 6, .result = 64 },
        { .x = 6, .y = 14, .result = 64 },
        { .x = 33, .y = 6, .result = 729 },
        { .x = 177, .y = 45, .result = 17424 },
};
static exercises2_data exercise_2a [TESTS_2A] = {
        { .a = 0, .b = 3, .c = 7, .result = 7 },
        { .a = 1, .b = 2, .c = 3, .result = 3 },
        { .a = 0, .b = 0, .c = 0, .result = 0 },
        { .a = 178, .b = 112, .c = 245, .result = 245 },
        { .a = 100, .b = 10, .c = 1, .result = 100 },
};
static exercises3_and_4_data exercise_3a [TESTS_3A] = {
        { .n = 5, .result = 120 },
        { .n = 1, .result = 1 },
        { .n = 10, .result = 3628800 },
        { .n = 12, .result = 479001600 },
        { .n = 2, .result = 2 },

};
static exercises3_and_4_data exercise_3b [TESTS_3B] = {
        { .n = 4, .result = 24 },
        { .n = 1, .result = 1 },
        { .n = 8, .result = 40320 },
        { .n = 11, .result = 39916800 },
        { .n = 6, .result = 720 },
};
static exercises3_and_4_data exercise_4a [TESTS_4A] = {
        { .n = 4321, .result = 1 },
        { .n = 12, .result = 2 },
        { .n = 0, .result = 0 },
        { .n = 266, .result = 6 },
        { .n = 17, .result = 7 },
        { .n = 91, .result = 1 },
        { .n = 2023, .result = 3 },
        { .n = 631842, .result = 2 },
};
static exercises3_and_4_data exercise_4b [TESTS_4B] = {
        { .n = 1234, .result = 3 },
        { .n = 10, .result = 1 },
        { .n = 0, .result = 0 },
        { .n = 133, .result = 3 },
        { .n = 17, .result = 1 },
        { .n = 91, .result = 9 },
        { .n = 2023, .result = 2 },
        { .n = 123456, .result = 5 },
};

char* render_exercise_1b(exercises1_data testcase)
{
    const char *x = format_int(testcase.x);
    const char *y = format_int(testcase.y);
    int len = strlen("x = ") + strlen(x) + strlen(" und y = ") + strlen(y) + 1;
    char *str = malloc(len);
    snprintf(str, len, "x = %s und y = %s", x, y);
    free((char*) x);
    free((char*) y);
    return str;
}

char* render_exercise_2a(exercises2_data testcase, int s_a, int s_b, int s_c, int state)
{
    const char *a = format_int(testcase.a);
    const char *b = format_int(testcase.b);
    const char *c = format_int(testcase.c);
    const char *got_a = format_int(s_a);
    const char *got_b = format_int(s_b);
    const char *got_c = format_int(s_c);
    char* warning_a = "\n" TESTRUNNER_LABEL "Für a:";
    char* warning_b = "\n" TESTRUNNER_LABEL "Für b:";
    char* warning_c = "\n" TESTRUNNER_LABEL "Für c:";
    char* warning = (state == 1 ? warning_a : (state == 2 ? warning_b : warning_c));
    int len = strlen("Eingabe: a = ") + strlen(a) + strlen(", b = ") + strlen(b) + strlen(" und c = ") + strlen(c) +
              strlen("\n\n") + strlen(TESTRUNNER_LABEL) + strlen("Erwartet: a = ") + strlen(b) + strlen(", b = ") +
              strlen(c) + strlen(" und c = ") + strlen(a) + strlen("\n") + strlen(TESTRUNNER_LABEL) +
              strlen("Erhielt: a = ") + strlen(got_a) + strlen(", b = ") + strlen(got_b) + strlen(" und c = ") +
              strlen(got_c) + strlen("\n") + strlen(warning) + 1;
    char *str = malloc(len);
    snprintf(str, len, "Eingabe: a = %s, b = %s und c = %s\n\n" TESTRUNNER_LABEL "Erwartet: a = %s, b = %s und c = %s\n"
    TESTRUNNER_LABEL "Erhielt: a = %s, b = %s und c = %s\n%s", a, b, c, b, c, a, got_a, got_b, got_c, warning);
    free((char*) a);
    free((char*) b);
    free((char*) c);
    free((char*) got_a);
    free((char*) got_b);
    free((char*) got_c);
    return str;
}
char* render_exercises_3ab4abcd(exercises3_and_4_data testcase)
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

    Tester tester = tester_new(argc - 1, argv[1], argv[2],
                               "cc -std=c11 -g -Wall "TEST_NAME".c -o "TEST_NAME".o -lm && ./"TEST_NAME".o");

    /* Aufgabe 1a */
    if(begin_exercise(&tester, "simple_assignment", "Aufgabe 1a: Einführung in die Testumgebung."))
    {
        if(begin_testcase(&tester))
        {
            if (tester.successful)
            {
                assert_int(&tester,91 , simple_assignment(7,13),
                           "Willkommen im Programmierkurs! Mit dieser Testumgebung können Sie Ihren eigenen "
                           "Code überprüfen.\n" TESTRUNNER_LABEL "Wenn unsere Tests unerwartete Ergebnisse in Ihrem Code "
                           "finden, gibt es eine Rückmeldung wie diese.\n" TESTRUNNER_LABEL "Die Meldung verrät immer, "
                           "welche Eingaben zu einem unerwarteten Ergebnis geführt haben, welches\n" TESTRUNNER_LABEL
                           "Ergebnis Ihr Code produziert hat, und welches Ergebnis erwartet wurde.\n" TESTRUNNER_LABEL
                           "Für diese Aufgabe sollen a und b nicht summiert sondern multipliziert werden.\n"
                           TESTRUNNER_LABEL "In C ist der Operator dafür '*' (statt '+' für eine Summe).\n\n"
                           TESTRUNNER_LABEL "a = 7 und b = 13");
            }
        }
    }
    /* Aufgabe 1b */
    if(begin_exercise(&tester, "nested_expressions", "Aufgabe 1b: Das Quadrat der Differenz zwischen x und y."))
    {
        for (int i = 0; i < TESTS_1B; i++)
        {
            if(begin_testcase(&tester))
            {
                if (tester.successful)
                {
                    char *args = render_exercise_1b(exercise_1b[i]);
                    assert_int(&tester, exercise_1b[i].result, nested_expressions(exercise_1b[i].x, exercise_1b[i].y),
                               args);
                    free(args);
                }
            }
        }
    }
    /* Aufgabe 2a */
    if(begin_exercise(&tester, "rotation", "Aufgabe 2a: Rotieren von Variablen-Werten."))
    {
        for (int i = 0; i < TESTS_2A; i++)
        {
            if(begin_testcase(&tester))
            {
                if (tester.successful)
                {
                    int compiled_res = rotation(exercise_2a[i].a, exercise_2a[i].b, exercise_2a[i].c);
                    int got_a = compiled_res & 255;
                    int got_b = (compiled_res / 256) & 255;
                    int got_c = compiled_res / (256 * 256);

                    char *args = render_exercise_2a(exercise_2a[i], got_a, got_b, got_c, 1);
                    assert_int(&tester, exercise_2a[i].b, got_a, args);
                    free(args);
                    args = render_exercise_2a(exercise_2a[i], got_a, got_b, got_c, 2);
                    assert_int(&tester, exercise_2a[i].c, got_b, args);
                    free(args);
                    args = render_exercise_2a(exercise_2a[i], got_a, got_b, got_c, 3);
                    assert_int(&tester, exercise_2a[i].a, got_c, args);
                    free(args);
                }
            }
        }
    }
    /* Aufgabe 3a */
    if(begin_exercise(&tester, "while_loop", "Aufgabe 3a: Produkt von n Zahlen per While-Loop."))
    {
        for (int i = 0; i < TESTS_3A; i++)
        {
            if(begin_testcase(&tester))
            {
                if (tester.successful)
                {
                    char *args = render_exercises_3ab4abcd(exercise_3a[i]);
                    assert_int(&tester, exercise_3a[i].result, while_loop(exercise_3a[i].n), args);
                    free(args);
                }
            }
        }
    }
    /* Aufgabe 3b */
    if(begin_exercise(&tester, "for_loop", "Aufgabe 3b: Produkt von n Zahlen per For-Loop."))
    {
        for (int i = 0; i < TESTS_3B; i++)
        {
            if(begin_testcase(&tester))
            {
                if (tester.successful)
                {
                    char *args = render_exercises_3ab4abcd(exercise_3b[i]);
                    assert_int(&tester, exercise_3b[i].result, for_loop(exercise_3b[i].n), args);
                    free(args);
                }
            }
        }
    }
    /* Aufgabe 4a */
    if(begin_exercise(&tester, "ones_place", "Aufgabe 4a: Die Einerstelle einer Zahl ausgeben."))
    {
        for (int i = 0; i < TESTS_4A; i++)
        {
            if(begin_testcase(&tester))
            {
                if (tester.successful)
                {
                    char *args = render_exercises_3ab4abcd(exercise_4a[i]);
                    assert_int(&tester, exercise_4a[i].result, ones_place(exercise_4a[i].n), args);
                    free(args);
                }
            }
        }
    }
    /* Aufgabe 4b */
    if(begin_exercise(&tester, "tens_place", "Aufgabe 4b: Die Zehnerstelle einer Zahl ausgeben."))
    {
        for (int i = 0; i < TESTS_4B; i++)
        {
            if(begin_testcase(&tester))
            {
                if (tester.successful)
                {
                    char *args = render_exercises_3ab4abcd(exercise_4b[i]);
                    assert_int(&tester, exercise_4b[i].result, tens_place(exercise_4b[i].n), args);
                    free(args);
                }
            }
        }
    }
    /* Aufgabe 5a */
    if(begin_exercise(&tester, "fine_print1", "Aufgabe 5a: Wichtige Informationen zur Bearbeitung."))
    {
        if(begin_testcase(&tester))
        {
            if (tester.successful)
            {
                assert_int(&tester, 8, fine_print1(), "Bitte lesen Sie den Text der Aufgabenstellung "
                                                      "sorgfältig.");
            }
        }
    }
    /* Aufgabe 5b */
    if(begin_exercise(&tester, "fine_print2", "Aufgabe 5b: Wichtige Informationen zu Aufgabenstellungen."))
    {
        if(begin_testcase(&tester))
        {
            if (tester.successful)
            {
                assert_int(&tester, 7, fine_print2(), "Bitte lesen Sie den Text der Aufgabenstellung "
                                                      "sorgfältig.");
            }
        }
    }
    /* Aufgabe 5c */
    if(begin_exercise(&tester, "fine_print3", "Aufgabe 5c: Wichtige Informationen zur Benotung."))
    {
        if(begin_testcase(&tester))
        {
            if (tester.successful)
            {
                assert_int(&tester, 6174, fine_print3(), "Bitte lesen Sie den Text der Aufgabenstellung "
                                                         "sorgfältig.");
            }
        }
    }

    return wrap_up(&tester);
}