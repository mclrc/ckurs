#include "03ex.c"
#include "testrunner.c"
#include "canvas.h"


#define TEST_NAME "03ex_test"
#define RELATIVE_DIRECTORY_PATH "Testdata/" TEST_NAME "data/"

#define TESTS_1A 12
#define TESTS_1B 11
#define TESTS_2B 7
#define TESTS_2C 6
#define TESTS_2D 6
#define TESTS_3A 5
#define TESTS_3B 4

typedef struct Test1
{
    int l;
    int m;
    int n;
    int expected;
} exercises_1_data;

typedef struct Test2
{
    char *filename;
} exercises_2_data;

typedef struct pair_
{
    int x;
    int y;
} pair;

typedef struct Test3
{
    char *filename;
    size_t number_of_pairs;
    pair *pair_array;
} exercises_3_data;

static exercises_1_data exercise_1a[TESTS_1A] = {
        { .n = 1, .m = 1, .expected = 1 },
        { .n = 5, .m = 2, .expected = 30 },
        { .n = 5, .m = 5, .expected = 75 },
        { .n = 0, .m = 10, .expected = 0 },
        { .n = 8, .m = 4, .expected = 144 },
        { .n = 16, .m = 4, .expected = 544 },
        { .n = 4, .m = 16, .expected = 160 },
        { .n = 10, .m = 9, .expected = 495 },
        { .n = 42, .m = 3, .expected = 2709 },
        { .n = 2023, .m = 1, .expected = 2047276 },
        { .n = 12, .m = 49, .expected = 3822 },
        { .n = 64, .m = 2, .expected = 4160 },
};
static exercises_1_data exercise_1b[TESTS_1B] = {
        { .n = 10, .l = 4, .m = 5, .expected = 1100 },
        { .n = 5, .l = 1, .m = 2, .expected = 30 },
        { .n = 16, .l = 8, .m = 4, .expected = 1088 },
        { .n = 0, .l = 4, .m = 5, .expected = 0 },
        { .n = 55, .l = 2, .m = 3, .expected = 9240 },
        { .n = 14, .l = 7, .m = 3, .expected = 2205 },
        { .n = 7, .l = 13, .m = 17, .expected = 6188 },
        { .n = 9, .l = 3, .m = 3, .expected = 135 },
        { .n = 10, .l = 1, .m = 10, .expected = 550},
        { .n = 4, .l = 8, .m = 12, .expected = 240 },
        { .n = 5, .l = 10, .m = 25, .expected = 750 },
};

static exercises_2_data exercise_2b[TESTS_2B] = {
        { .filename = "exercise_2b_simple_expected.png",},
        { .filename = "exercise_2b_bigger_expected.png",},
        { .filename = "exercise_2b_rectangle_one_expected.png",},
        { .filename = "exercise_2b_rectangle_two_expected.png",},
        { .filename = "exercise_2b_pitfalls_one_expected.png",},
        { .filename = "exercise_2b_pitfalls_two_expected.png",},
        { .filename = "exercise_2b_pitfalls_three_expected.png",},
};
static exercises_2_data exercise_2c[TESTS_2C] = {
        { .filename = "exercise_2c_simple_expected.png",},
        { .filename = "exercise_2c_bigger_expected.png",},
        { .filename = "exercise_2c_rectangle_expected.png",},
        { .filename = "exercise_2c_pitfalls_one_expected.png",},
        { .filename = "exercise_2c_pitfalls_two_expected.png",},
        { .filename = "exercise_2c_pitfalls_three_expected.png",},
};
static exercises_2_data exercise_2d[TESTS_2D] = {
        { .filename = "exercise_2d_square_expected.png",},
        { .filename = "exercise_2d_wider_than_high_expected.png",},
        { .filename = "exercise_2d_higher_than_wide_expected.png",},
        { .filename = "exercise_2d_pitfalls_one_expected.png",},
        { .filename = "exercise_2d_pitfalls_two_expected.png",},
        { .filename = "exercise_2d_pitfalls_three_expected.png",},
};

static pair exercise_3a_pairs1[] = {
        { .x = 360, .y = 477 },
        { .x = 125, .y = 85 },      //Width and Height for above coordinate
};
static pair exercise_3a_pairs2[] = {
        { .x = 2000, .y = 2000 },
        { .x = 200, .y = 200 },     //Width and Height for above coordinate
};
static pair exercise_3a_pairs3[] = {
        { .x = 360, .y = 477 },
        { .x = 125, .y = 0 },       //Width and Height for above coordinate
        { .x = 360, .y = 477 },
        { .x = 0, .y = 85 },        //Width and Height for above coordinate
        { .x = 360, .y = 477 },
        { .x = 0, .y = 0 },         //Width and Height for above coordinate
};
static pair exercise_3a_pairs4[] = {
        { .x = 200, .y = 200 },
        { .x = 50, .y = 1 },       //Width and Height for above coordinate
        { .x = 300, .y = 300 },
        { .x = 1, .y = 50 },       //Width and Height for above coordinate
        { .x = 200, .y = 300 },
        { .x = 1, .y = 1 },         //Width and Height for above coordinate
};
static pair exercise_3a_pairs5[] = {
        { .x = -160, .y = 640 },   //outside of top left corner
        { .x = 250, .y = 350 },     //Width and Height for above coordinate
        { .x = 310, .y = 550 },    //outside of top right corner
        { .x = 140, .y = 200 },     //Width and Height for above coordinate
        { .x = 260, .y = 80 },      //outside of bottom right corner
        { .x = 750, .y = 500 },     //Width and Height for above coordinate
        { .x = -40, .y = 40 },      //outside of bottom left corner
        { .x = 120, .y = 80 },      //Width and Height for above coordinate
        { .x = 130, .y = 440 },    //above top middle
        { .x = 110, .y = 110 },     //Width and Height for above coordinate
};
static exercises_3_data exercise_3a[TESTS_3A] = {
        { .number_of_pairs = 2, .pair_array = exercise_3a_pairs1,
                .filename = "exercise_3a_valid_expected.png",},
        { .number_of_pairs = 2, .pair_array = exercise_3a_pairs2,
                .filename = "exercise_3a_invalid_expected.png",},
        { .number_of_pairs = 6, .pair_array = exercise_3a_pairs3,
                .filename = "exercise_3a_input_is_zero_expected.png",},
        { .number_of_pairs = 6, .pair_array = exercise_3a_pairs4,
                .filename = "exercise_3a_line_and_dot_expected.png",},
        { .number_of_pairs = 10, .pair_array = exercise_3a_pairs5,
                .filename = "exercise_3a_partial_expected.png",},
};

static pair exercise_3b_coordinates1[] = {
        { .x = 25, .y = 375 },
        { .x = 375, .y = 25 },
};
static pair exercise_3b_coordinates2[] = {
        { .x = -2500, .y = -2000 },
        { .x = -2000, .y = -2500 },
};
static pair exercise_3b_coordinates3[] = {
        { .x = 337, .y = 450 },
        { .x = 337, .y = 378 },
        { .x = 19, .y = 46 },
        { .x = 161, .y = 46 },
        { .x = 56, .y = 470 },
        { .x = 56, .y = 470 },
};
static pair exercise_3b_coordinates4[] = {
        { .x = 302, .y = 144},      //coordinate inside
        { .x = 600, .y = -351},     //coordinate outside
        { .x = -390, .y = 272},     //coordinate outside
        { .x = 98, .y = 189},      //coordinate inside
        { .x = 344, .y = 567},     //coordinate outside
        { .x = 765, .y = 301},     //coordinate outside
};
static exercises_3_data exercise_3b[TESTS_3B] = {
        { .number_of_pairs = 2, .pair_array = exercise_3b_coordinates1,
                .filename = "exercise_3b_valid_expected.png",},
        { .number_of_pairs = 2, .pair_array = exercise_3b_coordinates2,
                .filename = "exercise_3b_invalid_expected.png",},
        { .number_of_pairs = 6, .pair_array = exercise_3b_coordinates3,
                .filename = "exercise_3b_line_and_dot_expected.png",},
        { .number_of_pairs = 6, .pair_array = exercise_3b_coordinates4,
                .filename = "exercise_3b_partial_expected.png",},
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

char* render_exercise_1a(exercises_1_data testcase)
{
    const char *n = format_int(testcase.n);
    const char *m = format_int(testcase.m);
    int len = strlen("n = ") + strlen(n) + strlen(" und m = ") + strlen(m) + 1;
    char *str = mallocx(len);
    snprintf(str, len, "n = %s und m = %s", n, m);
    free((char*) n);
    free((char*) m);
    return str;
}
char* render_exercise_1b(exercises_1_data testcase)
{
    const char *n = format_int(testcase.n);
    const char *l = format_int(testcase.l);
    const char *m = format_int(testcase.m);
    int len = strlen("n = ") + strlen(n) + strlen(", l = ") + strlen(l) + strlen(" und m = ") + strlen(m) + 1;
    char *str = mallocx(len);
    snprintf(str, len, "n = %s, l = %s und m = %s", n, l, m);
    free((char*) n);
    free((char*) l);
    free((char*) m);
    return str;
}
char* render_exercises_2bcd(Canvas testcase)
{
    const char *width = format_int(testcase->width);
    const char *height = format_int(testcase->height);
    int len = strlen("Wir testen auf einem ") + strlen(width) +
              strlen("x") + strlen(height) + strlen(" Pixel Canvas.") + 1;
    char *str = malloc(len);
    snprintf(str, len, "Wir testen auf einem %sx%s Pixel Canvas.", width, height);
    free((char*) width);
    free((char*) height);
    return str;
}
char* render_exercise_3a(Canvas testcase, pair* array, size_t array_length)
{
    const char *width = format_int(testcase->width);
    const char *height = format_int(testcase->height);
    char* full_input_string = calloc(30, array_length * sizeof(char));
    size_t counter = 1;
    for(int i = 0; i < array_length; i= i+2){
        char* temp_string = calloc(60, sizeof(char));
        snprintf(temp_string,100,TESTRUNNER_LABEL "\t\t%lu. Start bei (%d,%d) mit den Maßen %dx%d\n",
                 counter, array[i].x,array[i].y,array[i+1].x,array[i+1].y );
        counter++;
        strncat(full_input_string,temp_string,strlen(temp_string));
        free(temp_string);
    }
    int len = strlen("Wir testen auf einem ") + strlen(width) + strlen("x") + strlen(height) +
              strlen(" Pixel Canvas mit folgenden Rechtecken:\n") + strlen(full_input_string) + 1;
    char *str = malloc(len);
    snprintf(str, len, "Wir testen auf einem %sx%s Pixel Canvas mit folgenden Rechtecken:\n%s",
             width, height, full_input_string);
    free((char*) width);
    free((char*) height);
    free(full_input_string);
    return str;
}
char* render_exercise_3b(Canvas testcase, pair* array, size_t array_length)
{
    const char *width = format_int(testcase->width);
    const char *height = format_int(testcase->height);
    char* full_input_string = calloc(35, array_length * sizeof(char));
    size_t counter = 1;
    for(int i = 0; i < array_length; i= i+2){
        char* temp_string = calloc(70, sizeof(char));
        snprintf(temp_string,100,TESTRUNNER_LABEL "\t\t%lu. Mit den Koordinaten (%d,%d) und (%d,%d)\n",
                 counter, array[i].x,array[i].y,array[i+1].x,array[i+1].y );
        counter++;
        strncat(full_input_string,temp_string,strlen(temp_string));
        free(temp_string);
    }
    int len = strlen("Wir testen auf einem ") + strlen(width) + strlen("x") + strlen(height) +
              strlen(" Pixel Canvas mit folgenden Rechtecken:\n") + strlen(full_input_string) + 1;
    char *str = malloc(len);
    snprintf(str, len, "Wir testen auf einem %sx%s Pixel Canvas mit folgenden Rechtecken:\n%s",
             width, height, full_input_string);
    free((char*) width);
    free((char*) height);
    free(full_input_string);
    return str;
}

int main(int argc, char const *argv[])
{
    Tester tester = tester_new(argc-1,argv[1], argv[2],
                               "cc -std=c11 -g -Wall "TEST_NAME".c -o "TEST_NAME".o -lm && ./"TEST_NAME".o");


    /* Aufgabe 1a */
    if(begin_exercise(&tester, "sum_of_divisibles", "Aufgabe 1a: Die ersten n Zahlen die durch m teilbar "
                                                    "sind aufsummieren."))
    {
        for (int i = 0; i < TESTS_1A; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercise_1a(exercise_1a[i]);
                assert_int(&tester, exercise_1a[i].expected, sum_of_divisibles(exercise_1a[i].n, exercise_1a[i].m), args);
                free(args);
            }
        }
    }
    /* Aufgabe 1b */
    if(begin_exercise(&tester, "sum_of_doubly_divisibles", "Aufgabe 1b: Die ersten n Zahlen die durch l und m teilbar "
                                                           "sind aufsummieren."))
    {
        for (int i = 0; i < TESTS_1B; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercise_1b(exercise_1b[i]);
                assert_int(&tester, exercise_1b[i].expected, sum_of_doubly_divisibles(exercise_1b[i].n, exercise_1b[i].l,
                                                                                      exercise_1b[i].m), args);
                free(args);
            }
        }
    }
    /* Aufgabe 2a*/
    if(begin_exercise(&tester, "first_canvas_exercise", "Exercise 2a: Canvas Basics"))
    {
        if(begin_testcase(&tester))
        {
            Canvas expected = canvas_from_file("exercise_2a_expected.png");
            Canvas got = canvas_new(expected->width, expected->height, "first_canvas_exercise");

            assert_canvas(&tester, expected, first_canvas_exercise(got), got->supplied_invalid_coordinates ? "Im Feedbackbild ist oben die Canvas c,"
                                                                         " darunter das erwartete Bild, und ganz unten "
                                                                         "sind die Unterschiede markiert." : "");
            canvas_free(got);
            canvas_free(expected);
        }
    }
    /* Aufgabe 2b*/
    if(begin_exercise(&tester,"color_corners","Aufgabe 2b: Die Ecken in einem Canvas schwarz färben."))
    {
        for(int i = 0; i < TESTS_2B; i++)
        {
            if(begin_testcase(&tester))
            {
                Canvas expected = canvas_from_file(exercise_2b[i].filename);
                Canvas got = canvas_new(expected->width, expected->height, "color_corners");

                char *args = render_exercises_2bcd(expected);
                assert_canvas(&tester, expected, color_corners(got), args);
                free(args);

                canvas_free(got);
                canvas_free(expected);
            }
        }
    }
    /* Aufgabe 2c*/
    if(begin_exercise(&tester,"paint_it_black","Aufgabe 2c: Den kompletten Canvas schwarz färben."))
    {
        for(int i = 0; i < TESTS_2C; i++)
        {
            if(begin_testcase(&tester))
            {
                Canvas expected = canvas_from_file(exercise_2c[i].filename);
                Canvas got = canvas_new(expected->width, expected->height, "paint_it_black");

                char *args = render_exercises_2bcd(expected);
                assert_canvas(&tester, expected, paint_it_black(got), args);
                free(args);

                canvas_free(got);
                canvas_free(expected);
            }
        }
    }
    /* Aufgabe 2d*/
    if(begin_exercise(&tester,"descending_diagonal","Aufgabe 2d: Absteigende Diagonalen einfärben."))
    {
        for(int i = 0; i < TESTS_2D; i++)
        {
            if(begin_testcase(&tester))
            {
                Canvas expected = canvas_from_file(exercise_2d[i].filename);
                Canvas got = canvas_new(expected->width, expected->height, "descending_diagonal");

                char *args = render_exercises_2bcd(expected);
                assert_canvas(&tester, expected, descending_diagonal(got), args);
                free(args);

                canvas_free(got);
                canvas_free(expected);
            }
        }
    }
    /* Aufgabe 3a*/
    if(begin_exercise(&tester,"draw_rectangle","Aufgabe 3a: Rechtecke verschiedener Größen und Positionen einfärben."))
    {
        for(int i = 0; i < TESTS_3A; i++)
        {
            if(begin_testcase(&tester))
            {
                Canvas expected = canvas_from_file(exercise_3a[i].filename);
                Canvas got = canvas_new(expected->width, expected->height, "draw_rectangle");

                for(int z = 0; z < exercise_3a[i].number_of_pairs; z = z+2)
                {
                    draw_rectangle(got, exercise_3a[i].pair_array[z].x, exercise_3a[i].pair_array[z].y,
                                   exercise_3a[i].pair_array[z+1].x, exercise_3a[i].pair_array[z+1].y);
                }

                char *args = render_exercise_3a(expected, exercise_3a[i].pair_array, exercise_3a[i].number_of_pairs);
                assert_canvas(&tester, expected, got, args);
                free(args);

                canvas_free(got);
                canvas_free(expected);
            }
        }
    }
    /* Aufgabe 3b*/
    if(begin_exercise(&tester,"draw_rectangle_via_corners","Aufgabe 3b: Rechtecke einfärben durch Angabe "
                                                           "zweier Koordinatenpunkte."))
    {
        for(int i = 0; i < TESTS_3B; i++)
        {
            if(begin_testcase(&tester))
            {
                Canvas expected = canvas_from_file(exercise_3b[i].filename);
                Canvas got = canvas_new(expected->width, expected->height, "draw_rectangle_via_corners");

                for(int z = 0; z < exercise_3b[i].number_of_pairs; z = z+2)
                {
                    draw_rectangle_via_corners(got, exercise_3b[i].pair_array[z].x, exercise_3b[i].pair_array[z].y,
                                               exercise_3b[i].pair_array[z+1].x, exercise_3b[i].pair_array[z+1].y);
                }

                char *args = render_exercise_3b(expected, exercise_3b[i].pair_array, exercise_3b[i].number_of_pairs);
                assert_canvas(&tester, expected, got, args);
                free(args);

                canvas_free(got);
                canvas_free(expected);
            }
        }
    }


    return wrap_up(&tester);
}