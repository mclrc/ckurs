#include "05ex.c"
#include "testrunner.c"
#include "canvas.h"

#define TEST_NAME "05ex_test"
#define RELATIVE_DIRECTORY_PATH "Testdata/" TEST_NAME "data/"
#define TESTS_1A 5
#define TESTS_1B 4
#define TESTS_2A 13
#define TESTS_2B 7
#define TESTS_3 5

typedef struct Test1
{
    int x;
    int y;
    int width;
    int height;
    char *filename;
} exercises_1_data;

typedef struct Test2a
{
    int b;
    int exp;
    int expected;
} exercise_2a_data;

typedef struct Test2b
{
    int n;
    int start_coord;
    char *filename;
} exercise_2b_data;

typedef struct Test3
{
    int x;
    int y;
    char *file_in;
    char *file_out;
} exercise_3_data;

static exercises_1_data exercise_1a [TESTS_1A] = {
        { .x = 113, .y = 177, .width = 81, .height = 1, .filename = "exercise_1a_simple_expected.png"},
        { .x = 56, .y = 0, .width = 189, .height = 1, .filename = "exercise_1a_edge_expected.png"},
        { .x = -30, .y = 147, .width = 67, .height = 1, .filename = "exercise_1a_partial_one_expected.png"},
        { .x = -49, .y = 233, .width = 500, .height = 1, .filename = "exercise_1a_partial_two_expected.png"},
        { .x = -700, .y = -700, .width = 70, .height = 1, .filename = "exercise_1a_outside_expected.png"},
};
static exercises_1_data exercise_1b [TESTS_1B] = {
        { .x = 134, .y = 113, .width = 50, .height = 50, .filename = "exercise_1b_inside_one_expected.png"},
        { .x = 245, .y = 82, .width = 30, .height = 75, .filename = "exercise_1b_inside_two_expected.png"},
        { .x = -65, .y = 43, .width = 240, .height = 79, .filename = "exercise_1b_partial_expected.png"},
        { .x = -10, .y = -10, .width = 400, .height = 400, .filename = "exercise_1b_full_expected.png"},
};

static exercise_2a_data exercise_2a [TESTS_2A] = {
        { .b = 1, .exp = 7, .expected = 1},
        { .b = 3, .exp = 2, .expected = 9},
        { .b = 7, .exp = 1, .expected = 7},
        { .b = 2, .exp = 8, .expected = 256},
        { .b = 5, .exp = 0, .expected = 1},
        { .b = 0, .exp = 5, .expected = 0},
        { .b = 0, .exp = 0, .expected = 1},
        { .b = 10, .exp = 6, .expected = 1000000},
        { .b = 2, .exp = 8, .expected = 256},
        { .b = 12, .exp = 3, .expected = 1728},
        { .b = 3, .exp = 3, .expected = 27},
        { .b = 4, .exp = 4, .expected = 256},
        { .b = 5, .exp = 5, .expected = 3125},
};

static exercise_2b_data exercise_2b [TESTS_2B] = {
        { .n = 0, .start_coord = 0, .filename = "exercise_2b_order_0_expected.png"},
        { .n = 1, .start_coord = 0, .filename = "exercise_2b_order_1_expected.png"},
        { .n = 2, .start_coord = 0, .filename = "exercise_2b_order_2_expected.png"},
        { .n = 3, .start_coord = 0, .filename = "exercise_2b_order_3_expected.png"},
        { .n = 4, .start_coord = 0, .filename = "exercise_2b_order_4_expected.png"},
        { .n = 5, .start_coord = 0, .filename = "exercise_2b_order_5_expected.png"},
        { .n = 6, .start_coord = 0, .filename = "exercise_2b_order_6_expected.png"},
};

static exercise_3_data exercise_3 [TESTS_3] = {
        { .x = 2, .y = 8, .file_in = "exercise_3_z_empty.png", .file_out = "exercise_3_z_full.png"},
        { .x = 2, .y = 8, .file_in = "exercise_3_z_full.png", .file_out = "exercise_3_z_full.png"},
        { .x = 1, .y = 5, .file_in = "exercise_3_z_nontrivial.png", .file_out = "exercise_3_z_nontrivial.png"},
        { .x = 23, .y = 37, .file_in = "exercise_3_z_nontrivial.png", .file_out = "exercise_3_z_nontrivial_sky.png"},
        { .x = 25, .y = 20, .file_in = "exercise_3_z_nontrivial.png", .file_out = "exercise_3_z_nontrivial_face.png"},
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
char* render_exercise_1a(Canvas t,exercises_1_data testcase)
{
    const char *width = format_int(t->width);
    const char *height = format_int(t->height);
    const char *x = format_int(testcase.x);
    const char *y = format_int(testcase.y);
    const char *line_width = format_int(testcase.width);

    int len = strlen("Wir testen auf einem ") + strlen(width) + strlen("x") + strlen(height) +
              strlen(" Pixel Canvas mit einer Linie der Länge ") + strlen(line_width) + strlen(" startend bei (") +
              strlen(x) + strlen(",") + strlen(y) + strlen(").") + 1;
    char *str = malloc(len);
    snprintf(str, len, "Wir testen auf einem %sx%s Pixel Canvas mit einer Linie der Länge %s startend bei (%s,%s).",
             width, height, line_width, x, y);
    free((char*) width);
    free((char*) height);
    free((char*) x);
    free((char*) y);
    free((char*) line_width);
    return str;
}
char* render_exercise_1b(Canvas t,exercises_1_data testcase)
{
    const char *width = format_int(t->width);
    const char *height = format_int(t->height);
    const char *x = format_int(testcase.x);
    const char *y = format_int(testcase.y);
    const char *rect_width = format_int(testcase.width);
    const char *rect_height = format_int(testcase.height);

    int len = strlen("Wir testen auf einem ") + strlen(width) + strlen("x") + strlen(height) +
              strlen(" Pixel Canvas mit einem Rechteck der Länge ") + strlen(rect_width) + strlen(" und der Höhe ") +
              strlen(rect_height) + strlen(", mit der unteren linken Ecke bei (") +
              strlen(x) + strlen(",") + strlen(y) + strlen(").") + 1;
    char *str = malloc(len);
    snprintf(str, len, "Wir testen auf einem %sx%s Pixel Canvas mit einem Rechteck der Länge %s und der Höhe %s, "
                       "mit der unteren linken Ecke bei (%s,%s).",
             width, height, rect_width, rect_height, x, y);
    free((char*) width);
    free((char*) height);
    free((char*) x);
    free((char*) y);
    free((char*) rect_width);
    free((char*) rect_height);
    return str;
}
char* render_exercise_2a(exercise_2a_data testcase)
{
    const char *b = format_int(testcase.b);
    const char *exp = format_int(testcase.exp);
    int len = strlen("b = ") + strlen(b) + strlen(" und exp = ") + strlen(exp) + 1;
    char *str = malloc(len);
    snprintf(str, len, "b = %s und exp = %s", b, exp);
    free((char*) b);
    free((char*) exp);
    return str;
}
char* render_exercise_2b(exercise_2b_data testcase)
{
    const char *n = format_int(testcase.n);
    int len = strlen("n = ") + strlen(n) + 1;
    char *str = malloc(len);
    snprintf(str, len, "n = %s", n);
    free((char*) n);
    return str;
}
char* render_exercise_3(Canvas t,exercise_3_data testcase)
{
    const char *width = format_int(t->width);
    const char *height = format_int(t->height);
    const char *x = format_int(testcase.x);
    const char *y = format_int(testcase.y);

    int len = strlen("Wir testen auf einem ") + strlen(width) + strlen("x") + strlen(height) +
              strlen(" Pixel Canvas startend bei (") +
              strlen(x) + strlen(",") + strlen(y) + strlen("). Die Input-Canvas im 'Testdata'-Ordner heißt ") +
              strlen(testcase.file_in) + strlen(" .") + 1;
    char *str = malloc(len);
    snprintf(str, len, "Wir testen auf einem %sx%s Pixel Canvas startend bei (%s,%s). Die Input-Canvas im "
                       "'Testdata'-Ordner heißt %s .",width, height, x, y, testcase.file_in);
    free((char*) width);
    free((char*) height);
    free((char*) x);
    free((char*) y);
    return str;
}

int main(int argc, char const *argv[]) {
    Tester tester = tester_new(argc - 1, argv[1], argv[2],
                               "cc -std=c11 -g -Wall "TEST_NAME".c -o "TEST_NAME".o -lm && ./"TEST_NAME".o");

    /* Aufgabe 1a*/
    if(begin_exercise(&tester,"recursive_line","Aufgabe 1a: Eine horizontale Linie rekursiv zeichnen."))
    {
        for(int i = 0; i < TESTS_1A; i++)
        {
            if(begin_testcase(&tester))
            {
                Canvas expected = canvas_from_file(exercise_1a[i].filename);
                Canvas got = canvas_new(expected->width, expected->height, "recursive_line");

                char *args = render_exercise_1a(expected, exercise_1a[i]);
                assert_canvas(&tester, expected, recursive_line(got, exercise_1a[i].x, exercise_1a[i].y,
                                                                 exercise_1a[i].width), args);
                free(args);

                canvas_free(got);
                canvas_free(expected);
            }
        }
    }
    /* Aufgabe 1b*/
    if(begin_exercise(&tester,"recursive_rectangle","Aufgabe 1b: Ein Reckteck rekursiv zeichnen."))
    {
        for(int i = 0; i < TESTS_1B; i++)
        {
            if(begin_testcase(&tester))
            {
                Canvas expected = canvas_from_file(exercise_1b[i].filename);
                Canvas got = canvas_new(expected->width, expected->height, "recursive_rectangle");

                char *args = render_exercise_1b(expected, exercise_1b[i]);
                assert_canvas(&tester, expected, recursive_rectangle(got, exercise_1b[i].x, exercise_1b[i].y,
                                                                exercise_1b[i].width, exercise_1b[i].height), args);
                free(args);

                canvas_free(got);
                canvas_free(expected);
            }
        }
    }
    /* Aufgabe 2a*/
    if(begin_exercise(&tester, "power", "Aufgabe 2a: Berechnung von ganzzahligen Potenzen."))
    {
        for (int i = 0; i < TESTS_2A; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercise_2a(exercise_2a[i]);
                assert_int(&tester, exercise_2a[i].expected, power(exercise_2a[i].b, exercise_2a[i].exp), args);
                free(args);
            }
        }
    }
    /* Aufgabe 2b*/
    if(begin_exercise(&tester,"sierpinski_carpet","Aufgabe 2b: Den Sierpinski-Carpet implementieren."))
    {
        for(int i = 0; i < TESTS_2B; i++)
        {
            if(begin_testcase(&tester))
            {
                Canvas expected = canvas_from_file(exercise_2b[i].filename);
                Canvas got = canvas_new(expected->width, expected->height, "sierpinski_carpet");

                char *args = render_exercise_2b(exercise_2b[i]);
                int start = exercise_2b[i].start_coord;
                assert_canvas(&tester, expected, sierpinski_carpet(got, exercise_2b[i].n, start, start), args);
                free(args);

                canvas_free(got);
                canvas_free(expected);
            }
        }
    }
    /* Aufgabe 3*/
    if(begin_exercise(&tester,"bucket_fill","Aufgabe 3: Einen Fülleimer implementieren."))
    {
        for(int i = 0; i < TESTS_3; i++)
        {
            if(begin_testcase(&tester))
            {
                Canvas expected = canvas_from_file(exercise_3[i].file_out);
                Canvas got = canvas_from_file(exercise_3[i].file_in);
                free(got->name);
                got->name = mallocx(strlen("bucket_fill")+1);
                snprintf(got->name, strlen("bucket_fill")+1,"bucket_fill");

                char *args = render_exercise_3(expected, exercise_3[i]);
                assert_canvas(&tester, expected, bucket_fill(got, exercise_3[i].x, exercise_3[i].y), args);
                free(args);

                canvas_free(got);
                canvas_free(expected);
            }
        }
    }

    return wrap_up(&tester);
}
