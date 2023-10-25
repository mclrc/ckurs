#include "08ex.c"
#include "testrunner.c"
#include "canvas.h"

#define TEST_NAME "08ex_test"
#define RELATIVE_DIRECTORY_PATH "Testdata/" TEST_NAME "data/"

#define TESTS_1A 4
#define TESTS_1B 3

#define TESTS_2AB 6
#define TESTS_2CD 7
#define TESTS_2E 4
#define TESTS_2F 7

typedef struct Test1ab
{
    uint32_t steps;
    size_t x;
    size_t y;
    Orientation orientation;
    char* filename;
} exercises_1ab_data;

typedef struct Test2ab
{
    uint16_t* array;
    size_t array_length;
    size_t expected_index;
} exercises_2ab_data;

typedef struct Test2cd
{
    uint16_t* array;
    size_t array_length;
    size_t min_distance;
    size_t max_distance;
} exercises_2cd_data;

typedef struct Test2e
{
    uint16_t* result_array;
    uint16_t* expected_array;
    size_t array_length;
} exercise_2e_data;

typedef struct Test2f
{
    uint16_t* in_array;
    uint16_t* out_array;
    uint16_t* expected_array;
    size_t array_length;
} exercise_2f_data;

static exercises_1ab_data exercise_1a [TESTS_1A] = {
        {.x = 23, .y = 0, .orientation = North, .steps = 46, .filename = "exercise_1a_vertical_expected.png"},
        {.x = 20, .y = 70, .orientation = East, .steps = 100, .filename = "exercise_1a_horizontal_expected.png"},
        {.x = 110, .y = 65, .orientation = South, .steps = 95, .filename = "exercise_1a_wrap_expected.png"},
        {.x = 78, .y = 123, .orientation = West, .steps = 300, .filename = "exercise_1a_connecting_expected.png"},
};
static exercises_1ab_data exercise_1b [TESTS_1B] = {
        {.filename = "exercise_1b_simple_expected.png"},
        {.filename = "exercise_1b_big_expected.png"},
        {.filename = "exercise_1b_one_expected.png"},
};


static uint16_t exercises2ab_array1 [5] = {3,4,5,2,1};
static uint16_t exercises2ab_array2 [11] = {17,5,23,41,227,11,2,59,227,29,53};
static uint16_t exercises2ab_array3 [8] = {2,4,7,9,1,5,8,3};
static uint16_t exercises2ab_array4 [8] = {128,64,32,16,8,4,2,1};
static uint16_t exercises2ab_array5 [10] = {10,20,30,40,50,60,70,80,90,100};
static uint16_t exercises2ab_array6 [20] = {70,88,19,74,94,13,26,50,54,40,10,1,12,52,57,82,69,15,84,90};

static exercises_2ab_data exercises_2ab [TESTS_2AB] = {
        {.array_length = 5, .array = exercises2ab_array1, .expected_index = 2},
        {.array_length = 11, .array = exercises2ab_array2, .expected_index = 4},
        {.array_length = 8, .array = exercises2ab_array3, .expected_index = 3},
        {.array_length = 8, .array = exercises2ab_array4, .expected_index = 0},
        {.array_length = 10, .array = exercises2ab_array5, .expected_index = 9},
        {.array_length = 20, .array = exercises2ab_array6, .expected_index = 4},
};

static uint16_t exercises2cd_array1 [4] = {1,3,7,4};
static uint16_t exercises2cd_array2 [5] = {3,4,5,2,1};
static uint16_t exercises2cd_array3 [8] = {10,40,20,50,30,46,60,70};
static uint16_t exercises2cd_array4 [5] = {2,2,2,2,2};
static uint16_t exercises2cd_array5 [7] = {4, 8, 16, 32, 16, 8, 4};
static uint16_t exercises2cd_array6 [13] = {6,56,49,4,15,20,24,48,43,13,17,9,52};
static uint16_t exercises2cd_array7 [2] = {0,256};

static exercises_2cd_data exercises_2cd [TESTS_2CD] = {
        {.array_length = 4, .array = exercises2cd_array1, .min_distance = 1, .max_distance = 6},
        {.array_length = 5, .array = exercises2cd_array2, .min_distance = 1, .max_distance = 4},
        {.array_length = 8, .array = exercises2cd_array3, .min_distance = 4, .max_distance = 60},
        {.array_length = 5, .array = exercises2cd_array4, .min_distance = 0, .max_distance = 0},
        {.array_length = 7, .array = exercises2cd_array5, .min_distance = 0, .max_distance = 28},
        {.array_length = 13, .array = exercises2cd_array6, .min_distance = 1, .max_distance = 52},
        {.array_length = 2, .array = exercises2cd_array7, .min_distance = 256, .max_distance = 256},
};


static uint16_t exercise2e_result1 [2] = {0,0};
static uint16_t exercise2e_expected1 [2] = {1,4};

static uint16_t exercise2e_result2 [6] = {0,0,0,0,0,0};
static uint16_t exercise2e_expected2 [6] = {1,4,9,16,25,36};

static uint16_t exercise2e_result3 [10] = {0,0,0,0,0,0,0,0,0,0};
static uint16_t exercise2e_expected3 [10] = {1,4,9,16,25,36,49,64,81,100};

static uint16_t exercise2e_result4 [20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static uint16_t exercise2e_expected4 [20] = {1,4,9,16,25,36,49,64,81,100,121,144,169,196,225,256,289,324,361,400};

static exercise_2e_data exercise_2e [TESTS_2E] = {
        {.array_length = 2, .result_array = exercise2e_result1, .expected_array = exercise2e_expected1},
        {.array_length = 6, .result_array = exercise2e_result2, .expected_array = exercise2e_expected2},
        {.array_length = 10, .result_array = exercise2e_result3, .expected_array = exercise2e_expected3},
        {.array_length = 20, .result_array = exercise2e_result4, .expected_array = exercise2e_expected4},
};


static uint16_t exercise2f_out1 [5] = {0,0,0,0,0};
static uint16_t exercise2f_in1 [5] = {3,4,5,2,1};
static uint16_t exercise2f_expected1 [5] = {1,2,3,4,5};

static uint16_t exercise2f_out2 [1] = {0};
static uint16_t exercise2f_in2 [1] = {5};
static uint16_t exercise2f_expected2 [1] = {5};

static uint16_t exercise2f_out3 [8] = {0,0,0,0,0,0,0,0};
static uint16_t exercise2f_in3 [8] = {128,64,32,16,8,4,2,1};
static uint16_t exercise2f_expected3 [8] = {1,2,4,8,16,32,64,128};

static uint16_t exercise2f_out4 [10] = {0,0,0,0,0,0,0,0,0,0};
static uint16_t exercise2f_in4 [10] = {10,10,10,10,10,10,10,10,10,10};
static uint16_t exercise2f_expected4 [10] = {10,10,10,10,10,10,10,10,10,10};

static uint16_t exercise2f_out5 [13] = {0,0,0,0,0,0,0,0,0,0,0,0,0};
static uint16_t exercise2f_in5 [13] = {4,20,8,10,9,27,31,40,15,11,14,12,34};
static uint16_t exercise2f_expected5 [13] = {4,8,9,10,11,12,14,15,20,27,31,34,40};

static uint16_t exercise2f_out6 [25] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static uint16_t exercise2f_in6 [25] = {8,10,1,8,6,1,3,2,5,1,9,8,2,2,1,8,10,7,1,2,7,1,6,5,3};
static uint16_t exercise2f_expected6 [25] = {1,1,1,1,1,1,2,2,2,2,3,3,5,5,6,6,7,7,8,8,8,8,9,10,10};

static uint16_t exercise2f_out7 [16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static uint16_t exercise2f_in7 [16] = {64,128,64,256,16,8,128,128,256,256,128,8,4,64,128,32};
static uint16_t exercise2f_expected7 [16] = {4,8,8,16,32,64,64,64,128,128,128,128,128,256,256,256};

static exercise_2f_data exercise_2f [TESTS_2F] = {
        {.array_length = 5, .out_array = exercise2f_out1, .in_array = exercise2f_in1, .expected_array = exercise2f_expected1},
        {.array_length = 1, .out_array = exercise2f_out2, .in_array = exercise2f_in2, .expected_array = exercise2f_expected2},
        {.array_length = 8, .out_array = exercise2f_out3, .in_array = exercise2f_in3, .expected_array = exercise2f_expected3},
        {.array_length = 10, .out_array = exercise2f_out4, .in_array = exercise2f_in4, .expected_array = exercise2f_expected4},
        {.array_length = 13, .out_array = exercise2f_out5, .in_array = exercise2f_in5, .expected_array = exercise2f_expected5},
        {.array_length = 25, .out_array = exercise2f_out6, .in_array = exercise2f_in6, .expected_array = exercise2f_expected6},
        {.array_length = 16, .out_array = exercise2f_out7, .in_array = exercise2f_in7, .expected_array = exercise2f_expected7},
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
TurtleCanvas* create_turtle_canvas_with_position(size_t width, size_t height,
                                                 size_t x_coord, size_t y_coord, Orientation cardinal, char* canvas_name){
    TurtleCanvas* c = mallocx(sizeof(TurtleCanvas));
    c->canvas = canvas_new(width, height, canvas_name);
    c->turtle_x = x_coord;
    c->turtle_y = y_coord;
    c->draw_black = true;
    c->orientation = cardinal;
    return c;
}
TurtleCanvas* create_turtle_canvas(size_t width, size_t height, char* canvas_name){
    TurtleCanvas* c = create_turtle_canvas_with_position(width, height, 0, 0, East, canvas_name);
    return c;
}
void turtle_canvas_free(TurtleCanvas* c){
    canvas_free(c->canvas);
    free(c);
}

char* render_exercise_1a(exercises_1ab_data testcase, Canvas t)
{
    const char *width = format_int(t->width);
    const char *height = format_int(t->height);
    const char *steps = format_uint(testcase.steps);

    int len = strlen("Wir testen auf einem ") + strlen(width) + strlen("x") + strlen(height) +
              strlen(" Pixel Canvas und lassen die Schildkröte ") + strlen(steps) + strlen(" Schritte machen.") + 1;
    char *str = mallocx(len);
    snprintf(str, len, "Wir testen auf einem %sx%s Pixel Canvas und lassen die Schildkröte %s Schritte machen.",
             width, height, steps);
    free((char*) width);
    free((char*) height);
    free((char*) steps);
    return str;
}
char* render_exercise_1b(Canvas t)
{
    const char *width = format_int(t->width);
    const char *height = format_int(t->height);

    int len = strlen("Wir testen auf einem ") + strlen(width) + strlen("x") + strlen(height) +
              strlen(" Pixel Canvas.") + 1;
    char *str = mallocx(len);
    snprintf(str, len, "Wir testen auf einem %sx%s Pixel Canvas.",
             width, height);
    free((char*) width);
    free((char*) height);
    return str;
}
char* render_exercises_2ab( exercises_2ab_data testcase)
{
    const char *length = format_uint(testcase.array_length);
    const char *index = format_int(testcase.expected_index);
    const char* array_string = format_uint16_array(testcase.array, testcase.array_length);

    int len = strlen("Wir testen auf dem folgenden Array der Länge ") + strlen(length) + strlen(":\n" TESTRUNNER_LABEL)
            + strlen(array_string) + strlen("\n" TESTRUNNER_LABEL "Das erste Vorkommen der größten Zahl ist am Index ")
            + strlen(index) + strlen(".") + 1;

    char *str = mallocx(len);
    snprintf(str, len, "Wir testen auf dem folgenden Array der Länge %s:\n" TESTRUNNER_LABEL "%s\n" TESTRUNNER_LABEL
                       "Das erste Vorkommen der größten Zahl ist am Index %s.",length,
             array_string, index);

    free((char*) array_string);
    free((char*) length);
    free((char*) index);
    return str;
}
char* render_exercises_2cd( exercises_2cd_data testcase)
{
    const char *length = format_uint(testcase.array_length);
    const char* array_string = format_uint16_array(testcase.array, testcase.array_length);

    int len = strlen("Wir testen auf dem folgenden Array der Länge ") + strlen(length) + strlen(":\n" TESTRUNNER_LABEL)
              + strlen(array_string) + strlen("\n")  + 1;

    char *str = mallocx(len);
    snprintf(str, len, "Wir testen auf dem folgenden Array der Länge %s:\n" TESTRUNNER_LABEL "%s\n",length,
             array_string);

    free((char*) array_string);
    free((char*) length);
    return str;
}
char* render_exercise_2f( exercise_2f_data testcase)
{
    const char *length = format_uint(testcase.array_length);
    const char* array_string = format_uint16_array(testcase.in_array, testcase.array_length);

    int len = strlen("Wir testen auf dem folgenden Array der Länge ") + strlen(length) + strlen(":\n" TESTRUNNER_LABEL)
              + strlen(array_string) + strlen("\n")  + 1;

    char *str = mallocx(len);
    snprintf(str, len, "Wir testen auf dem folgenden Array der Länge %s:\n" TESTRUNNER_LABEL "%s\n",length,
             array_string);

    free((char*) array_string);
    free((char*) length);
    return str;
}

int main(int argc, char const *argv[]) {
    Tester tester = tester_new(argc - 1, argv[1], argv[2],
                               "cc -std=c11 -g -Wall "TEST_NAME".c -o "TEST_NAME".o -lm && ./"TEST_NAME".o");

    /* Aufgabe 1a */
    if(begin_exercise(&tester,"turtle_advance_by","Aufgabe 1a: Die Schildkröte mehrere Schritte vorwärts laufen lassen."))
    {
        for (int i = 0; i < TESTS_1A; i++)
        {
            if(begin_testcase(&tester))
            {
                Canvas expected = canvas_from_file(exercise_1a[i].filename);
                TurtleCanvas* got = create_turtle_canvas_with_position(expected->width, expected->height,
                                                                       exercise_1a[i].x, exercise_1a[i].y,
                                                                       exercise_1a[i].orientation, "turtle_advance_by");

                char *args = render_exercise_1a(exercise_1a[i], got->canvas);
                turtle_advance_by(got, exercise_1a[i].steps);
                assert_canvas(&tester, expected, got->canvas, args);
                free(args);

                turtle_canvas_free(got);
                canvas_free(expected);
            }
        }
    }
    /* Aufgabe 1b */
    if(begin_exercise(&tester,"turtle_stripes","Aufgabe 1b: Die Schildkröte horizontale Streifen zeichnen lassen."))
    {
        for (int i = 0; i < TESTS_1B; i++)
        {
            if(begin_testcase(&tester))
            {
                Canvas expected = canvas_from_file(exercise_1b[i].filename);
                TurtleCanvas* got = create_turtle_canvas(expected->width, expected->height, "turtle_stripes");

                char *args = render_exercise_1b(got->canvas);
                turtle_stripes(got);
                assert_canvas(&tester, expected, got->canvas, args);
                free(args);

                turtle_canvas_free(got);
                canvas_free(expected);
            }
        }
    }
    /* Aufgabe 2a */
    if(begin_exercise(&tester,"find_maximal_number","Aufgabe 2a: Den Speicherort der ersten größten Zahl zurückgeben."))
    {
        for (int i = 0; i < TESTS_2AB; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercises_2ab(exercises_2ab[i]);
                uint16_t* got = find_maximal_number(exercises_2ab[i].array, exercises_2ab[i].array_length);
                uint16_t* expected = &(exercises_2ab[i].array[exercises_2ab[i].expected_index]);
                assert_pointer(&tester, expected, got, args);
                free(args);
            }
        }
    }
    /* Aufgabe 2b */
    if(begin_exercise(&tester,"find_subarray_starting_at_maximal_number","Aufgabe 2b: Den Anfang des Arrays ab der "
                                                                         "ersten größten Zahl zurückgeben."))
    {
        for (int i = 0; i < TESTS_2AB; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercises_2ab(exercises_2ab[i]);
                uint16_t* got = find_subarray_starting_at_maximal_number(exercises_2ab[i].array,
                                                                         exercises_2ab[i].array_length);
                uint16_t* expected = &(exercises_2ab[i].array[exercises_2ab[i].expected_index]);
                assert_pointer(&tester, expected, got, args);
                free(args);
            }
        }
    }
    /* Aufgabe 2c */
    if(begin_exercise(&tester,"find_maximum_distance","Aufgabe 2c: Den größten Abstand zwischen Zahlen im Array finden."))
    {
        for (int i = 0; i < TESTS_2CD; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercises_2cd(exercises_2cd[i]);
                assert_uint(&tester, exercises_2cd[i].max_distance,
                            find_maximum_distance(exercises_2cd[i].array,exercises_2cd[i].array_length), args);
                free(args);
            }
        }
    }
    /* Aufgabe 2d */
    if(begin_exercise(&tester,"find_minimum_distance","Aufgabe 2d: Den kleinsten Abstand zwischen Zahlen im Array finden."))
    {
        for (int i = 0; i < TESTS_2CD; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercises_2cd(exercises_2cd[i]);
                assert_uint(&tester, exercises_2cd[i].min_distance,
                            find_minimum_distance(exercises_2cd[i].array, exercises_2cd[i].array_length),args);
                free(args);
            }
        }
    }
    /* Aufgabe 2e */
    if(begin_exercise(&tester,"square_ascending","Aufgabe 2e: Die ersten 'numbers_len' Quadratzahlen berechnen."))
    {
        for (int i = 0; i < TESTS_2E; i++)
        {
            if(begin_testcase(&tester))
            {
                size_t len = exercise_2e[i].array_length;
                square_ascending(exercise_2e[i].result_array, len);
                assert_uint16_array(&tester,exercise_2e[i].expected_array, exercise_2e[i].result_array, len, "");
            }
        }
    }
    /* Aufgabe 2f */
    if(begin_exercise(&tester,"sort_ascending","Aufgabe 2f: Zahlen eines Arrays aufsteigend sortieren."))
    {
        for (int i = 0; i < TESTS_2F; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercise_2f(exercise_2f[i]);
                size_t len = exercise_2f[i].array_length;
                sort_ascending(exercise_2f[i].in_array, exercise_2f[i].out_array, len);
                assert_uint16_array(&tester,exercise_2f[i].expected_array, exercise_2f[i].out_array, len, args);
                free(args);
            }
        }
    }

    return wrap_up(&tester);
}
