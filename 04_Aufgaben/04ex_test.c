#include "04ex.c"
#include "testrunner.c"
#include "canvas.h"

#define TEST_NAME "04ex_test"
#define RELATIVE_DIRECTORY_PATH "Testdata/" TEST_NAME "data/"
#define TESTS_1A 8
#define TESTS_1B 7
#define TESTS_1C 11
#define TESTS_1D 7


typedef struct TestA
{
    int x;
    int y;
    int radius;
    char *filename;
} exercise_1a_data;

typedef struct TestB
{
    int x0;
    int y0;
    int x1;
    int y1;
    int expected;
} exercise_1b_data;

typedef struct TestC
{
    int n;
    int expected;
} exercise_1c_data;

typedef struct circle_data
{
    int x;
    int y;
    int diameter;
}circle;

typedef struct TestD
{
    circle *circle_array;
    size_t number_of_circles;
    char *filename;
} exercise_1d_data;

static exercise_1a_data exercise_1a [TESTS_1A] = {
    { .x = 40, .y = 40, .radius = 1, .filename = "exercise_1a_one_expected.png" },
    { .x = 20, .y = 20, .radius = 0, .filename = "exercise_1a_zero_expected.png" },
    { .x = 103, .y = 109, .radius = 11, .filename = "exercise_1a_primes_one_expected.png" },
    { .x = 137, .y = 127, .radius = 17, .filename = "exercise_1a_primes_two_expected.png" },
    { .x = 113, .y = 97, .radius = 23, .filename = "exercise_1a_primes_three_expected.png" },
    { .x = 150, .y = 150, .radius = 200, .filename = "exercise_1a_big_circle_expected.png" },
    { .x = 0, .y = 0, .radius = 145, .filename = "exercise_1a_partial_one_expected.png" },
    { .x = -150, .y = 150, .radius = 250, .filename = "exercise_1a_partial_two_expected.png" },
};

static exercise_1b_data exercise_1b [TESTS_1B] = {
    { .x0 = 50, .y0 = 50, .x1 = 50, .y1 = 50, .expected = 0 },
    { .x0 = 0, .y0 = 0, .x1 = 42, .y1 = 0, .expected = 42 },
    { .x0 = 0, .y0 = 0, .x1 = 0, .y1 = 26, .expected = 26 },
    { .x0 = 245, .y0 = 166, .x1 = 257, .y1 = 213, .expected = 48 },
    { .x0 = 512, .y0 = 64, .x1 = 128, .y1 = 256, .expected = 429 },
    { .x0 = 128, .y0 = 256, .x1 = 512, .y1 = 32, .expected = 444 },
    { .x0 = -52, .y0 = -52, .x1 = 365, .y1 = 365, .expected = 589 },
};

static exercise_1c_data exercise_1c [TESTS_1C] = {
    { .n = 64, .expected = 8 },
    { .n = 25, .expected = 5 },
    { .n = 9, .expected = 3 },
    { .n = 2, .expected = 1 },
    { .n = 1, .expected = 1 },
    { .n = 0, .expected = 0 },
    { .n = 90, .expected = 9 },
    { .n = 80, .expected = 8 },
    { .n = 60, .expected = 7 },
    { .n = 40, .expected = 6 },
    { .n = 30, .expected = 5 },
};

static struct circle_data exercise_1d_cd1[] = {
        { .x = 80, .y = 80, .diameter = 43 },
};
static struct circle_data exercise_1d_cd2[] = {
        { .x = 157, .y = 242, .diameter = 21 },
};
static struct circle_data exercise_1d_cd3[] = {
        { .x = 346, .y = 373, .diameter = 10 },
};
static struct circle_data exercise_1d_cd4[] = {
        { .x = 195, .y = 203, .diameter = 98 },
};
static struct circle_data exercise_1d_cd5[] = {
        { .x = 200, .y = 200, .diameter = 1 },
        { .x = 175, .y = 175, .diameter = 2 },
        { .x = 225, .y = 175, .diameter = 3 },
};
static struct circle_data exercise_1d_cd6[] = {
        { .x = 25, .y = -25, .diameter = 350 },
};
static struct circle_data exercise_1d_cd7[] = {
        { .x = 170, .y = 230, .diameter = 7 },
        { .x = 240, .y = 180, .diameter = 20 },
        { .x = 260, .y = 80, .diameter = 37 },
        { .x = 210, .y = -30, .diameter = 50 },
        { .x = -30, .y = -10, .diameter = 71 },
        { .x = -10, .y = 135, .diameter = 94 },
};
static exercise_1d_data exercise_1d [TESTS_1D] = {
    { .circle_array = exercise_1d_cd1, .number_of_circles = 1, .filename = "exercise_1d_odd_one_expected.png" },
    { .circle_array = exercise_1d_cd2, .number_of_circles = 1, .filename = "exercise_1d_odd_two_expected.png" },
    { .circle_array = exercise_1d_cd3, .number_of_circles = 1, .filename = "exercise_1d_even_one_expected.png" },
    { .circle_array = exercise_1d_cd4, .number_of_circles = 1, .filename = "exercise_1d_even_two_expected.png" },
    { .circle_array = exercise_1d_cd5, .number_of_circles = 3, .filename = "exercise_1d_small_expected.png" },
    { .circle_array = exercise_1d_cd6, .number_of_circles = 1, .filename = "exercise_1d_over_edge_expected.png" },
    { .circle_array = exercise_1d_cd7, .number_of_circles = 6, .filename = "exercise_1d_collage_expected.png" },
};

Canvas canvas_from_file(char *filename)
{
    int path_size = strlen(filename) + strlen(RELATIVE_DIRECTORY_PATH) +1;
    char* path = (char *)malloc(path_size);
    snprintf(path, path_size, "%s%s", RELATIVE_DIRECTORY_PATH, filename);

    Canvas c = canvas_load_image(path);
    free(path);
    return c;
}

char* render_exercise_1a(Canvas t, exercise_1a_data testcase)
{
    const char *width = format_int(t->width);
    const char *height = format_int(t->height);
    const char *x = format_int(testcase.x);
    const char *y = format_int(testcase.y);
    const char *radius = format_int(testcase.radius);


    int len = strlen("Wir testen auf einem ") + strlen(width) + strlen("x") + strlen(height) +
              strlen(" Pixel Canvas. Der Mittelpixel liegt bei: (") + strlen(x) + strlen(",") +
              strlen(y) + strlen(") und der Radius ist") + strlen(radius) + strlen(".") + 1;
    char *str = malloc(len);
    snprintf(str, len, "Wir testen auf einem %sx%s Pixel Canvas. Der Mittelpixel liegt bei: (%s,%s) und der Radius "
                       "ist %s.", width, height, x, y, radius);
    free((char*) width);
    free((char*) height);
    free((char*) x);
    free((char*) y);
    free((char*) radius);
    return str;
}
char* render_exercise_1b(exercise_1b_data testcase)
{
    const char *x0 = format_int(testcase.x0);
    const char *y0 = format_int(testcase.y0);
    const char *x1 = format_int(testcase.x1);
    const char *y1 = format_int(testcase.y1);

    int len = strlen("Punkt 1 = (")+ strlen(x0) + strlen(",") + strlen(y0) + strlen(") | Punkt 1 = (") + strlen(x1) +
              strlen(",") + strlen(y0) + strlen(")") + 1;
    char *str = malloc(len);
    snprintf(str, len, "Punkt 0 = (%s,%s) | Punkt 1 = (%s,%s)", x0, y0, x1, y1);
    free((char*) x0);
    free((char*) y0);
    free((char*) x1);
    free((char*) y1);
    return str;
}
char* render_exercise_1c(exercise_1c_data testcase)
{
    const char *n = format_int(testcase.n);
    int len = strlen("n = ") + strlen(n) + 1;
    char *str = malloc(len);
    snprintf(str, len, "n = %s", n);
    free((char*) n);
    return str;
}
char* render_exercise_1d(Canvas t, exercise_1d_data testcase)
{
    const char *width = format_int(t->width);
    const char *height = format_int(t->height);

    char* full_input_string = calloc(125, testcase.number_of_circles * sizeof(char));
    size_t counter = 1;
    for(int i = 0; i < testcase.number_of_circles; i++){
        char* temp_string = calloc(130, sizeof(char));
        snprintf(temp_string,130,TESTRUNNER_LABEL "\t\t%lu. x-Koordinate der linkesten Pixel = %d, "
                                                  "y-Koordinate der untersten Pixel = %d \n"
                                                  TESTRUNNER_LABEL "\t\tund Durchmesser = %d\n",
                 counter, testcase.circle_array[i].x, testcase.circle_array[i].y, testcase.circle_array[i].diameter );
        counter++;
        strncat(full_input_string,temp_string,strlen(temp_string));
        free(temp_string);
    }

    int len = strlen("Wir testen auf einem ") + strlen(width) + strlen("x") + strlen(height) +
              strlen(" Pixel Canvas mit folgenden Kreisen:\n") + strlen(full_input_string) + 1;
    char *str = malloc(len);
    snprintf(str, len, "Wir testen auf einem %sx%s Pixel Canvas mit folgenden Kreisen:\n%s",
             width, height, full_input_string);
    free((char*) width);
    free((char*) height);
    free(full_input_string);
    return str;
}

int main(int argc, char const *argv[]) {
    Tester tester = tester_new(argc - 1, argv[1], argv[2],
                               "cc -std=c11 -g -Wall "TEST_NAME".c 04ex_helpers.c -o "TEST_NAME".o -lm && ./"TEST_NAME".o");

    /* Aufgabe 1a*/
    if(begin_exercise(&tester,"draw_odd_circle","Aufgabe 1a: Kreise mit ungeradem Durchmesser zeichnen."))
    {
        for(int i = 0; i < TESTS_1A; i++)
        {
            if(begin_testcase(&tester))
            {
                Canvas expected = canvas_from_file(exercise_1a[i].filename);
                Canvas got = canvas_new(expected->width, expected->height, "draw_odd_circle");

                char *args = render_exercise_1a(expected, exercise_1a[i]);
                assert_canvas(&tester, expected, draw_odd_circle(got, exercise_1a[i].x, exercise_1a[i].y,
                                                                 exercise_1a[i].radius), args);
                free(args);

                canvas_free(got);
                canvas_free(expected);
            }
        }
    }
    /* Aufgabe 1b*/
    if(begin_exercise(&tester, "my_distance", "Aufgabe 1b: Berechnung des abgerundeten Abstands zweier Punkte."))
    {
        for (int i = 0; i < TESTS_1B; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercise_1b(exercise_1b[i]);
                assert_int(&tester, exercise_1b[i].expected, my_distance(exercise_1b[i].x0, exercise_1b[i].y0,
                                                                         exercise_1b[i].x1, exercise_1b[i].y1), args);
                free(args);
            }
        }
    }
    /* Aufgabe 1c*/
    if(begin_exercise(&tester, "my_squareroot", "Aufgabe 1c: Berechnung von abgerundeten Quadratwurzeln."))
    {
        for (int i = 0; i < TESTS_1C; i++)
        {

            if(begin_testcase(&tester))
            {
                char *args = render_exercise_1c(exercise_1c[i]);
                assert_int(&tester, exercise_1c[i].expected, my_squareroot(exercise_1c[i].n), args);
                free(args);
            }
        }
    }
    /* Aufgabe 1d*/
    if(begin_exercise(&tester,"draw_circle","Aufgabe 1d: Kreise verschiedener Durchmesser zeichnen."))
    {
        for(int i = 0; i < TESTS_1D; i++)
        {
            if(begin_testcase(&tester))
            {
                Canvas expected = canvas_from_file(exercise_1d[i].filename);
                Canvas got = canvas_new(expected->width, expected->height, "draw_circle");

                for(int z = 0; z < exercise_1d[i].number_of_circles; z++)
                {
                    draw_circle(got, exercise_1d[i].circle_array[z].x, exercise_1d[i].circle_array[z].y,
                                exercise_1d[i].circle_array[z].diameter);
                }

                char *args = render_exercise_1d(expected, exercise_1d[i]);
                assert_canvas(&tester, expected, got, args);
                free(args);

                canvas_free(got);
                canvas_free(expected);
            }
        }
    }
    /* Aufgabe 1e */
    if (begin_exercise(&tester, "high_five", "Aufgabe 1e: High Five.")) {
        if (begin_testcase(&tester)) {
            assert_int(&tester, 5, high_five(), "^_^/ Lass den Testrunner nicht hängen!");
        }
        if(tester.successful) printf(TESTRUNNER_LABEL "( ^o^)Ʌ(^-^ )\n");
    }
    /* Aufgabe 2a */
    if (begin_exercise(&tester, "hailstone", "Aufgabe 2a: Berechnung der Hailstone-Nummer.")) {
        if (begin_testcase(&tester)) {
            printf(TESTRUNNER_LABEL "Für Aufgabe 2a gibt es keine Tests von uns! Für mehr Details lesen Sie bitte "
                                    "Aufgabe 2b.\n");
        }
    }
    /* Aufgabe 2b */
    if (begin_exercise(&tester, "bring_your_own_tests", "Aufgabe 2b: Informationen zu 2a.")) {
        if (begin_testcase(&tester)) {
            assert_int(&tester, 99, bring_your_own_tests(), "Bitte lesen Sie den Text der "
                                                            "Aufgabenstellung sorgfältig.");
        }
    }

    return wrap_up(&tester);
}
