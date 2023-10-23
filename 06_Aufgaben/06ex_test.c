#include "06ex.c"
#include "testrunner.c"
#include "canvas.h"

#define TEST_NAME "06ex_test"
#define RELATIVE_DIRECTORY_PATH "Testdata/" TEST_NAME "data/"
#define TESTS_1A 5
#define TESTS_1B 4
#define TESTS_1C 9
#define TESTS_2B 4
#define TESTS_2C 9
#define TESTS_2D 9

typedef struct Test1a2d
{
    char *file_in;
    char *file_out;
} exercise_1a2d_data;

typedef struct Test1b_data
{
    int x;
    int y;
    ColorChannel channel;
    float value;
}one_color_data;

typedef struct Test1b
{
    one_color_data *pixel_data;
    int number_of_pixels;
    char *filename;
} exercise_1b_data;

typedef struct Test1c
{
    ColorChannel x_channel;
    ColorChannel y_channel;
    char *filename;
} exercise_1c_data;

typedef struct Test2b_data
{
    int x;
    int y;
    RGB color;
}full_color_data;

typedef struct Test2b
{
    full_color_data* pixel_data;
    int number_of_pixels;
    char *filename;
} exercise_2b_data;

typedef struct Test2c
{
    RGB color_in;
    RGB color_out;
} exercise_2c_data;

static exercise_1a2d_data exercise_1a [TESTS_1A] = {
        {.file_out = "exercise_1a_small_expected.png", .file_in = "exercise_1a_small_input.png"},
        {.file_out = "exercise_1a_big_expected.png", .file_in = "exercise_1a_big_input.png"},
        {.file_out = "exercise_1a_rectangle_expected.png", .file_in = "exercise_1a_rectangle_input.png"},
        {.file_out = "exercise_1a_white_expected.png", .file_in = "exercise_1a_white_input.png"},
        {.file_out = "exercise_1a_blue_expected.png", .file_in = "exercise_1a_blue_input.png"},
};

static one_color_data exercise_1b_pixels1 [2] = {
        {.x = 20, .y = 20, .channel = Red, .value = 1.0},
        {.x = 34, .y = 57, .channel = Red, .value = 0.678},
};
static one_color_data exercise_1b_pixels2 [2] = {
        {.x = 90, .y = 51, .channel = Green, .value = 1.0},
        {.x = 77, .y = 77, .channel = Green, .value = 0.385},
};
static one_color_data exercise_1b_pixels3 [2] = {
        {.x = 3, .y = 46, .channel = Blue, .value = 1.0},
        {.x = 80, .y = 10, .channel = Blue, .value = 0.807},
};
static one_color_data exercise_1b_pixels4 [17] = {
        {.x = 1, .y = 1, .channel = Red, .value = 1.0},
        {.x = 2, .y = 1, .channel = Red, .value = 1.0},
        {.x = 2, .y = 1, .channel = Green, .value = 0.4},
        {.x = 3, .y = 1, .channel = Red, .value = 1.0},
        {.x = 3, .y = 1, .channel = Green, .value = 1.0},
        {.x = 4, .y = 1, .channel = Red, .value = 0.7},
        {.x = 4, .y = 1, .channel = Green, .value = 1.0},
        {.x = 5, .y = 1, .channel = Red, .value = 0.4},
        {.x = 5, .y = 1, .channel = Green, .value = 1.0},
        {.x = 6, .y = 1, .channel = Green, .value = 1.0},
        {.x = 7, .y = 1, .channel = Green, .value = 0.7},
        {.x = 7, .y = 1, .channel = Blue, .value = 1.0},
        {.x = 8, .y = 1, .channel = Green, .value = 0.4},
        {.x = 8, .y = 1, .channel = Blue, .value = 1.0},
        {.x = 9, .y = 1, .channel = Blue, .value = 1.0},
        {.x = 10, .y = 1, .channel = Red, .value = 0.5},
        {.x = 10, .y = 1, .channel = Blue, .value = 1.0},
};
static exercise_1b_data exercise_1b [TESTS_1B] = {
        {.pixel_data = exercise_1b_pixels1, .number_of_pixels = 2, .filename = "exercise_1b_red_expected.png"},
        {.pixel_data = exercise_1b_pixels2, .number_of_pixels = 2, .filename = "exercise_1b_green_expected.png"},
        {.pixel_data = exercise_1b_pixels3, .number_of_pixels = 2, .filename = "exercise_1b_blue_expected.png"},
        {.pixel_data = exercise_1b_pixels4, .number_of_pixels = 17, .filename = "exercise_1b_prism_expected.png"},
};

static exercise_1c_data exercise_1c [TESTS_1C] = {
        {.x_channel = Red, .y_channel = Green, .filename = "exercise_1c_redgreen_expected.png"},
        {.x_channel = Green, .y_channel = Red, .filename = "exercise_1c_greenred_expected.png"},
        {.x_channel = Blue, .y_channel = Red, .filename = "exercise_1c_bluered_expected.png"},
        {.x_channel = Red, .y_channel = Blue, .filename = "exercise_1c_redblue_expected.png"},
        {.x_channel = Green, .y_channel = Blue, .filename = "exercise_1c_greenblue_expected.png"},
        {.x_channel = Blue, .y_channel = Green, .filename = "exercise_1c_bluegreen_expected.png"},
        {.x_channel = Red, .y_channel = Red, .filename = "exercise_1c_red_expected.png"},
        {.x_channel = Green, .y_channel = Green, .filename = "exercise_1c_green_expected.png"},
        {.x_channel = Blue, .y_channel = Blue, .filename = "exercise_1c_blue_expected.png"},
};

static full_color_data exercise_2b_pixels1 [3] = {
        {.x = 50, .y = 100, .color = {1.0,0.0,0.0}},
        {.x = 100, .y = 100, .color = {0.0,1.0,0.0}},
        {.x = 150, .y = 100, .color = {0.0,0.0,1.0}},
};
static full_color_data exercise_2b_pixels2 [15] = {
        {.x = 05, .y = 05, .color = {0.5,0.0,0.0}},
        {.x = 10, .y = 10, .color = {0.6,0.0,0.0}},
        {.x = 15, .y = 15, .color = {0.7,0.0,0.0}},
        {.x = 20, .y = 20, .color = {0.8,0.0,0.0}},
        {.x = 25, .y = 25, .color = {0.9,0.0,0.0}},
        {.x = 30, .y = 30, .color = {1.0,0.5,0.0}},
        {.x = 35, .y = 35, .color = {1.0,0.6,0.0}},
        {.x = 40, .y = 40, .color = {1.0,0.7,0.0}},
        {.x = 45, .y = 45, .color = {1.0,0.8,0.0}},
        {.x = 50, .y = 50, .color = {1.0,0.9,0.0}},
        {.x = 55, .y = 55, .color = {1.0,1.0,0.5}},
        {.x = 60, .y = 60, .color = {1.0,1.0,0.6}},
        {.x = 65, .y = 65, .color = {1.0,1.0,0.7}},
        {.x = 70, .y = 70, .color = {1.0,1.0,0.8}},
        {.x = 75, .y = 75, .color = {1.0,1.0,0.9}},
};
static full_color_data exercise_2b_pixels3 [56] = {
        //blue
        {.x = 1, .y = 6, .color = {0.0, 0.0,1.0}},  //left
        {.x = 1, .y = 5, .color = {0.0, 0.0,1.0}},  //left
        {.x = 1, .y = 4, .color = {0.0, 0.0,1.0}},  //left
        {.x = 2, .y = 3, .color = {0.0, 0.0,1.0}},  //bottom
        {.x = 3, .y = 3, .color = {0.0, 0.0,1.0}},  //bottom
        {.x = 4, .y = 3, .color = {0.0, 0.0,1.0}},  //bottom
        {.x = 5, .y = 4, .color = {0.0, 0.0,1.0}},  //right
        {.x = 5, .y = 5, .color = {0.0, 0.0,1.0}},  //right
        {.x = 5, .y = 6, .color = {0.0, 0.0,1.0}},  //right
        {.x = 4, .y = 7, .color = {0.0, 0.0,1.0}},  //top
        {.x = 3, .y = 7, .color = {0.0, 0.0,1.0}},  //top
        {.x = 2, .y = 7, .color = {0.0, 0.0,1.0}},  //top
        //black
        {.x = 7, .y = 6, .color = {0.0, 0.0,0.0}},  //left
        {.x = 7, .y = 5, .color = {0.0, 0.0,0.0}},  //left
        {.x = 7, .y = 4, .color = {0.0, 0.0,0.0}},  //left
        {.x = 8, .y = 3, .color = {0.0,0.0,0.0}},  //bottom
        {.x = 9, .y = 3, .color = {0.0,0.0,0.0}},  //bottom
        {.x = 10, .y = 3, .color = {0.0,0.0,0.0}},  //bottom
        {.x = 11, .y = 4, .color = {0.0,0.0,0.0}},  //right
        {.x = 11, .y = 5, .color = {0.0,0.0,0.0}},  //right
        {.x = 11, .y = 6, .color = {0.0,0.0,0.0}},  //right
        {.x = 10, .y = 7, .color = {0.0,0.0,0.0}},  //top
        {.x = 9, .y = 7, .color = {0.0,0.0,0.0}},  //top
        {.x = 8, .y = 7, .color = {0.0,0.0,0.0}},  //top
        //red
        {.x = 13, .y = 6, .color = {1.0,0.0,0.0}},  //left
        {.x = 13, .y = 5, .color = {1.0,0.0,0.0}},  //left
        {.x = 13, .y = 4, .color = {1.0,0.0,0.0}},  //left
        {.x = 14, .y = 3, .color = {1.0,0.0,0.0}},  //bottom
        {.x = 15, .y = 3, .color = {1.0,0.0,0.0}},  //bottom
        {.x = 16, .y = 3, .color = {1.0,0.0,0.0}},  //bottom
        {.x = 17, .y = 4, .color = {1.0,0.0,0.0}},  //right
        {.x = 17, .y = 5, .color = {1.0,0.0,0.0}},  //right
        {.x = 17, .y = 6, .color = {1.0,0.0,0.0}},  //right
        {.x = 16, .y = 7, .color = {1.0,0.0,0.0}},  //top
        {.x = 15, .y = 7, .color = {1.0,0.0,0.0}},  //top
        {.x = 14, .y = 7, .color = {1.0,0.0,0.0}},  //top
        //yellow
        {.x = 4, .y = 4, .color = {1.0,1.0,0.0}},  //left
        {.x = 4, .y = 3, .color = {1.0,1.0,0.0}},  //left
        {.x = 4, .y = 2, .color = {1.0,1.0,0.0}},  //left
        {.x = 5, .y = 1, .color = {1.0,1.0,0.0}},  //bottom
        {.x = 6, .y = 1, .color = {1.0,1.0,0.0}},  //bottom
        {.x = 7, .y = 1, .color = {1.0,1.0,0.0}},  //bottom
        {.x = 8, .y = 4, .color = {1.0,1.0,0.0}},  //right
        {.x = 8, .y = 2, .color = {1.0,1.0,0.0}},  //right
        {.x = 7, .y = 5, .color = {1.0,1.0,0.0}},  //top
        {.x = 6, .y = 5, .color = {1.0,1.0,0.0}},  //top
        //green
        {.x = 10, .y = 4, .color = {0.0,1.0,0.0}},  //left
        {.x = 10, .y = 3, .color = {0.0,1.0,0.0}},  //left
        {.x = 10, .y = 2, .color = {0.0,1.0,0.0}},  //left
        {.x = 11, .y = 1, .color = {0.0,1.0,0.0}},  //bottom
        {.x = 12, .y = 1, .color = {0.0,1.0,0.0}},  //bottom
        {.x = 13, .y = 1, .color = {0.0,1.0,0.0}},  //bottom
        {.x = 14, .y = 4, .color = {0.0,1.0,0.0}},  //right
        {.x = 14, .y = 2, .color = {0.0,1.0,0.0}},  //right
        {.x = 13, .y = 5, .color = {0.0,1.0,0.0}},  //top
        {.x = 12, .y = 5, .color = {0.0,1.0,0.0}},  //top
};
static full_color_data exercise_2b_pixels4 [172] = {
        //line 18
        {.x = 9, .y = 18, .color = {0.0,0.0,0.0}},
        {.x = 10, .y = 18, .color = {0.0,0.0,0.0}},
        {.x = 11, .y = 18, .color = {0.0,0.0,0.0}},
        //line 17
        {.x = 4, .y = 17, .color = {0.0,0.0,0.0}},
        {.x = 5, .y = 17, .color = {0.0,0.0,0.0}},
        {.x = 6, .y = 17, .color = {0.0,0.0,0.0}},
        {.x = 7, .y = 17, .color = {0.0,0.0,0.0}},
        {.x = 8, .y = 17, .color = {0.0,0.0,0.0}},
        {.x = 9, .y = 17, .color = {0.0,0.5,0.0}},
        {.x = 10, .y = 17, .color = {0.0,0.5,0.0}},
        {.x = 11, .y = 17, .color = {0.0,0.0,0.0}},
        //line 16
        {.x = 3, .y = 16, .color = {0.0,0.0,0.0}},
        {.x = 4, .y = 16, .color = {0.0,0.5,0.0}},
        {.x = 5, .y = 16, .color = {0.0,0.8,0.0}},
        {.x = 6, .y = 16, .color = {0.0,0.0,0.0}},
        {.x = 8, .y = 16, .color = {0.0,0.0,0.0}},
        {.x = 9, .y = 16, .color = {0.0,0.5,0.0}},
        {.x = 10, .y = 16, .color = {0.0,0.5,0.0}},
        {.x = 11, .y = 16, .color = {0.0,0.0,0.0}},
        //line 15
        {.x = 2, .y = 15, .color = {0.0,0.0,0.0}},
        {.x = 3, .y = 15, .color = {0.0,0.5,0.0}},
        {.x = 4, .y = 15, .color = {0.0,0.8,0.0}},
        {.x = 5, .y = 15, .color = {0.0,0.8,0.0}},
        {.x = 6, .y = 15, .color = {0.0,0.0,0.0}},
        {.x = 8, .y = 15, .color = {0.0,0.0,0.0}},
        {.x = 9, .y = 15, .color = {0.0,0.8,0.0}},
        {.x = 10, .y = 15, .color = {0.0,0.0,0.0}},
        {.x = 11, .y = 15, .color = {0.0,0.8,0.0}},
        {.x = 12, .y = 15, .color = {0.0,0.0,0.0}},
        //line 14
        {.x = 1, .y = 14, .color = {0.0,0.0,0.0}},
        {.x = 2, .y = 14, .color = {0.0,0.5,0.0}},
        {.x = 3, .y = 14, .color = {0.0,0.8,0.0}},
        {.x = 4, .y = 14, .color = {0.0,0.8,0.0}},
        {.x = 5, .y = 14, .color = {0.0,0.0,0.0}},
        {.x = 7, .y = 14, .color = {0.0,0.0,0.0}},
        {.x = 8, .y = 14, .color = {0.0,0.8,0.0}},
        {.x = 9, .y = 14, .color = {0.0,0.0,0.0}},
        {.x = 10, .y = 14, .color = {0.0,0.0,0.0}},
        {.x = 11, .y = 14, .color = {0.0,0.8,0.0}},
        {.x = 12, .y = 14, .color = {0.0,0.0,0.0}},
        //line 13
        {.x = 2, .y = 13, .color = {0.0,0.0,0.0}},
        {.x = 3, .y = 13, .color = {0.0,0.0,0.0}},
        {.x = 4, .y = 13, .color = {0.0,0.0,0.0}},
        {.x = 7, .y = 13, .color = {0.0,0.0,0.0}},
        {.x = 8, .y = 13, .color = {0.0,0.8,0.0}},
        {.x = 9, .y = 13, .color = {0.0,0.0,0.0}},
        {.x = 11, .y = 13, .color = {0.0,0.0,0.0}},
        {.x = 12, .y = 13, .color = {0.0,0.8,0.0}},
        {.x = 13, .y = 13, .color = {0.0,0.0,0.0}},
        //line 12
        {.x = 6, .y = 12, .color = {0.0,0.0,0.0}},
        {.x = 7, .y = 12, .color = {0.0,0.8,0.0}},
        {.x = 8, .y = 12, .color = {0.0,0.0,0.0}},
        {.x = 11, .y = 12, .color = {0.0,0.0,0.0}},
        {.x = 12, .y = 12, .color = {0.0,0.8,0.0}},
        {.x = 13, .y = 12, .color = {0.0,0.0,0.0}},
        //line 11
        {.x = 6, .y = 11, .color = {0.0,0.0,0.0}},
        {.x = 7, .y = 11, .color = {0.0,0.8,0.0}},
        {.x = 8, .y = 11, .color = {0.0,0.0,0.0}},
        {.x = 11, .y = 11, .color = {0.0,0.0,0.0}},
        {.x = 12, .y = 11, .color = {0.0,0.8,0.0}},
        {.x = 13, .y = 11, .color = {0.0,0.0,0.0}},
        //line 10
        {.x = 5, .y = 10, .color = {0.0,0.0,0.0}},
        {.x = 6, .y = 10, .color = {0.0,0.8,0.0}},
        {.x = 7, .y = 10, .color = {0.0,0.0,0.0}},
        {.x = 12, .y = 10, .color = {0.0,0.0,0.0}},
        {.x = 13, .y = 10, .color = {0.0,0.8,0.0}},
        {.x = 14, .y = 10, .color = {0.0,0.0,0.0}},
        //line 9
        {.x = 4, .y = 9, .color = {0.0,0.0,0.0}},
        {.x = 5, .y = 9, .color = {1.0,0.0,0.28}},
        {.x = 6, .y = 9, .color = {1.0,0.0,0.28}},
        {.x = 7, .y = 9, .color = {1.0,0.0,0.28}},
        {.x = 8, .y = 9, .color = {0.0,0.0,0.0}},
        {.x = 12, .y = 9, .color = {0.0,0.0,0.0}},
        {.x = 13, .y = 9, .color = {0.0,0.0,0.0}},
        {.x = 14, .y = 9, .color = {0.0,0.0,0.0}},
        //line 8
        {.x = 3, .y = 8, .color = {0.0,0.0,0.0}},
        {.x = 4, .y = 8, .color = {1.0,0.0,0.28}},
        {.x = 5, .y = 8, .color = {1.0,0.0,0.28}},
        {.x = 6, .y = 8, .color = {1.0,0.0,0.28}},
        {.x = 7, .y = 8, .color = {1.0,0.43,0.7}},
        {.x = 8, .y = 8, .color = {1.0,0.0,0.28}},
        {.x = 9, .y = 8, .color = {0.0,0.0,0.0}},
        {.x = 11, .y = 8, .color = {0.0,0.0,0.0}},
        {.x = 12, .y = 8, .color = {1.0,0.0,0.28}},
        {.x = 13, .y = 8, .color = {1.0,0.0,0.28}},
        {.x = 14, .y = 8, .color = {1.0,0.0,0.28}},
        {.x = 15, .y = 8, .color = {0.0,0.0,0.0}},
        //line 7
        {.x = 2, .y = 7, .color = {0.0,0.0,0.0}},
        {.x = 3, .y = 7, .color = {1.0,0.0,0.28}},
        {.x = 4, .y = 7, .color = {1.0,0.0,0.28}},
        {.x = 5, .y = 7, .color = {1.0,0.0,0.28}},
        {.x = 6, .y = 7, .color = {1.0,0.43,0.7}},
        {.x = 7, .y = 7, .color = {1.0,0.8,1.0}},
        {.x = 8, .y = 7, .color = {1.0,0.43,0.7}},
        {.x = 9, .y = 7, .color = {1.0,0.0,0.28}},
        {.x = 10, .y = 7, .color = {0.0,0.0,0.0}},
        {.x = 11, .y = 7, .color = {1.0,0.0,0.28}},
        {.x = 12, .y = 7, .color = {1.0,0.0,0.28}},
        {.x = 13, .y = 7, .color = {1.0,0.0,0.28}},
        {.x = 14, .y = 7, .color = {1.0,0.43,0.7}},
        {.x = 15, .y = 7, .color = {1.0,0.0,0.28}},
        {.x = 16, .y = 7, .color = {0.0,0.0,0.0}},
        //line 6
        {.x = 2, .y = 6, .color = {0.0,0.0,0.0}},
        {.x = 3, .y = 6, .color = {1.0,0.0,0.28}},
        {.x = 4, .y = 6, .color = {1.0,0.0,0.28}},
        {.x = 5, .y = 6, .color = {1.0,0.0,0.28}},
        {.x = 6, .y = 6, .color = {1.0,0.0,0.28}},
        {.x = 7, .y = 6, .color = {1.0,0.43,0.7}},
        {.x = 8, .y = 6, .color = {1.0,0.0,0.28}},
        {.x = 9, .y = 6, .color = {1.0,0.0,0.28}},
        {.x = 10, .y = 6, .color = {0.0,0.0,0.0}},
        {.x = 11, .y = 6, .color = {1.0,0.0,0.28}},
        {.x = 12, .y = 6, .color = {1.0,0.0,0.28}},
        {.x = 13, .y = 6, .color = {1.0,0.43,0.7}},
        {.x = 14, .y = 6, .color = {1.0,0.8,1.0}},
        {.x = 15, .y = 6, .color = {1.0,0.43,0.7}},
        {.x = 16, .y = 6, .color = {1.0,0.0,0.28}},
        {.x = 17, .y = 6, .color = {0.0,0.0,0.0}},
        //line 5
        {.x = 2, .y = 5, .color = {0.0,0.0,0.0}},
        {.x = 3, .y = 5, .color = {1.0,0.0,0.28}},
        {.x = 4, .y = 5, .color = {1.0,0.0,0.28}},
        {.x = 5, .y = 5, .color = {1.0,0.0,0.28}},
        {.x = 6, .y = 5, .color = {1.0,0.0,0.28}},
        {.x = 7, .y = 5, .color = {1.0,0.0,0.28}},
        {.x = 8, .y = 5, .color = {1.0,0.0,0.28}},
        {.x = 9, .y = 5, .color = {1.0,0.0,0.28}},
        {.x = 10, .y = 5, .color = {0.0,0.0,0.0}},
        {.x = 11, .y = 5, .color = {1.0,0.0,0.28}},
        {.x = 12, .y = 5, .color = {1.0,0.0,0.28}},
        {.x = 13, .y = 5, .color = {1.0,0.0,0.28}},
        {.x = 14, .y = 5, .color = {1.0,0.43,0.7}},
        {.x = 15, .y = 5, .color = {1.0,0.0,0.28}},
        {.x = 16, .y = 5, .color = {1.0,0.0,0.28}},
        {.x = 17, .y = 5, .color = {0.0,0.0,0.0}},
        //line 4
        {.x = 3, .y = 4, .color = {0.0,0.0,0.0}},
        {.x = 4, .y = 4, .color = {1.0,0.0,0.28}},
        {.x = 5, .y = 4, .color = {1.0,0.0,0.28}},
        {.x = 6, .y = 4, .color = {1.0,0.0,0.28}},
        {.x = 7, .y = 4, .color = {1.0,0.0,0.28}},
        {.x = 8, .y = 4, .color = {1.0,0.0,0.28}},
        {.x = 9, .y = 4, .color = {0.0,0.0,0.0}},
        {.x = 10, .y = 4, .color = {1.0,0.0,0.28}},
        {.x = 11, .y = 4, .color = {1.0,0.0,0.28}},
        {.x = 12, .y = 4, .color = {1.0,0.0,0.28}},
        {.x = 13, .y = 4, .color = {1.0,0.0,0.28}},
        {.x = 14, .y = 4, .color = {1.0,0.0,0.28}},
        {.x = 15, .y = 4, .color = {1.0,0.0,0.28}},
        {.x = 16, .y = 4, .color = {1.0,0.0,0.28}},
        {.x = 17, .y = 4, .color = {0.0,0.0,0.0}},
        //line 3
        {.x = 4, .y = 3, .color = {0.0,0.0,0.0}},
        {.x = 5, .y = 3, .color = {1.0,0.0,0.28}},
        {.x = 6, .y = 3, .color = {1.0,0.0,0.28}},
        {.x = 7, .y = 3, .color = {1.0,0.0,0.28}},
        {.x = 8, .y = 3, .color = {0.0,0.0,0.0}},
        {.x = 10, .y = 3, .color = {0.0,0.0,0.0}},
        {.x = 11, .y = 3, .color = {1.0,0.0,0.28}},
        {.x = 12, .y = 3, .color = {1.0,0.0,0.28}},
        {.x = 13, .y = 3, .color = {1.0,0.0,0.28}},
        {.x = 14, .y = 3, .color = {1.0,0.0,0.28}},
        {.x = 15, .y = 3, .color = {1.0,0.0,0.28}},
        {.x = 16, .y = 3, .color = {0.0,0.0,0.0}},
        //line 2
        {.x = 5, .y = 2, .color = {0.0,0.0,0.0}},
        {.x = 6, .y = 2, .color = {0.0,0.0,0.0}},
        {.x = 7, .y = 2, .color = {0.0,0.0,0.0}},
        {.x = 11, .y = 2, .color = {0.0,0.0,0.0}},
        {.x = 12, .y = 2, .color = {1.0,0.0,0.28}},
        {.x = 13, .y = 2, .color = {1.0,0.0,0.28}},
        {.x = 14, .y = 2, .color = {1.0,0.0,0.28}},
        {.x = 15, .y = 2, .color = {0.0,0.0,0.0}},
        //line 1
        {.x = 12, .y = 1, .color = {0.0,0.0,0.0}},
        {.x = 13, .y = 1, .color = {0.0,0.0,0.0}},
        {.x = 14, .y = 1, .color = {0.0,0.0,0.0}},
};

static exercise_2b_data exercise_2b [TESTS_2B] = {
        {.pixel_data = exercise_2b_pixels1, .number_of_pixels = 3, .filename = "exercise_2b_purecolors_expected.png"},
        {.pixel_data = exercise_2b_pixels2, .number_of_pixels = 15, .filename = "exercise_2b_ladder_expected.png"},
        {.pixel_data = exercise_2b_pixels3, .number_of_pixels = 56, .filename = "exercise_2b_olympics_expected.png"},
        {.pixel_data = exercise_2b_pixels4, .number_of_pixels = 172, .filename = "exercise_2b_cherry_expected.png"},
};

static exercise_2c_data exercise_2c [TESTS_2C] = {
        {.color_in = {0,0,0}, .color_out = {0,0,0}},
        {.color_in = {0.86,0.82,1.0}, .color_out = {0.852394,0.852394,0.852394}},
        {.color_in = {1.0,0,0}, .color_out = {0.2989,0.2989,0.2989}},
        {.color_in = {0,1.0,0}, .color_out = {0.587,0.587,0.587}},
        {.color_in = {0,0,1.0}, .color_out = {0.1140,0.1140,0.1140}},
        {.color_in = {1.0,0.84,0}, .color_out = {0.791980,0.791980,0.791980}},
        {.color_in = {0.749,0.5373,0.4392}, .color_out = {0.589340,0.589340,0.589340}},
        {.color_in = {1,1,1}, .color_out = {0.9999,0.9999,0.9999}},
        {.color_in = {0.5,0.5,0.5}, .color_out = {0.49995,0.49995,0.49995}},
};

static exercise_1a2d_data exercise_2d [TESTS_2D] = {
        {.file_in = "exercise_1c_red_expected.png", .file_out = "exercise_2d_red_expected.png"},
        {.file_in = "exercise_1a_small_expected.png", .file_out = "exercise_2d_rg_expected.png"},
        {.file_in = "exercise_1a_white_expected.png", .file_out = "exercise_2d_inverse_rg_expected.png"},
        {.file_in = "exercise_1c_bluered_expected.png", .file_out = "exercise_2d_br_expected.png"},
        {.file_in = "exercise_1b_prism_expected.png", .file_out = "exercise_2d_pictures_one_expected.png"},
        {.file_in = "exercise_2b_olympics_expected.png", .file_out = "exercise_2d_pictures_two_expected.png"},
        {.file_in = "exercise_2b_cherry_expected.png", .file_out = "exercise_2d_pictures_three_expected.png"},
        {.file_in = "exercise_2d_landscape_one_input.png", .file_out = "exercise_2d_landscape_one_expected.png"},
        {.file_in = "exercise_2d_landscape_two_input.png", .file_out = "exercise_2d_landscape_two_expected.png"},
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
int compare_RGB(RGB expected, RGB got){
    int result = 1;
    if((fabsf(expected.r - got.r) >= 0.0001) || (fabsf(expected.g - got.g) >= 0.0001)
          || (fabsf(expected.b - got.b) >= 0.0001) ){
        result = 0;
    }
    return result;
}
const char* format_color_enum (ColorChannel a_channel){
    int size;
    char* color;
    if(a_channel == Red){
        size = 4;
        color = (char*) mallocx(size);
        snprintf(color, size, "Red");
    } else if (a_channel == Green){
        size = 6;
        color = (char*) mallocx(size);
        snprintf(color, size, "Green");
    } else {
        size = 5;
        color = (char*) mallocx(size);
        snprintf(color, size, "Blue");
    }
    return color;
}

char* render_exercise_1a2d(Canvas t,exercise_1a2d_data testcase)
{
    const char *width = format_int(t->width);
    const char *height = format_int(t->height);

    int len = strlen("Wir testen auf einem ") + strlen(width) + strlen("x") + strlen(height) +
              strlen(" Pixel Canvas. Die Input-Canvas im 'Testdata'-Ordner heißt ") +
              strlen(testcase.file_in) + strlen(" .") + 1;
    char *str = malloc(len);
    snprintf(str, len, "Wir testen auf einem %sx%s Pixel Canvas. Die Input-Canvas im "
                       "'Testdata'-Ordner heißt %s .",width, height, testcase.file_in);
    free((char*) width);
    free((char*) height);
    return str;
}
char* render_exercise_1b(Canvas t, exercise_1b_data testcase)
{
    const char *width = format_int(t->width);
    const char *height = format_int(t->height);

    char* full_input_string = calloc(125, testcase.number_of_pixels * sizeof(char));
    size_t counter = 1;
    for(int i = 0; i < testcase.number_of_pixels; i++){
        char* temp_string = calloc(120, sizeof(char));
        const char *color = format_color_enum(testcase.pixel_data[i].channel);
        snprintf(temp_string,100,TESTRUNNER_LABEL "\t\t%lu. Pixel mit den Koordinaten: (%d,%d), Channel: %s "
                                                  "und dem Farbwert: %.4f\n", counter, testcase.pixel_data[i].x,
                                                  testcase.pixel_data[i].y, color, testcase.pixel_data[i].value);
        counter++;
        strncat(full_input_string,temp_string,strlen(temp_string));
        free(temp_string);
        free((char*)color);
    }

    int len = strlen("Wir testen auf einem ") + strlen(width) + strlen("x") + strlen(height) +
              strlen(" Pixel Canvas mit folgenden Pixeln:\n") + strlen(full_input_string) + 1;
    char *str = malloc(len);
    snprintf(str, len, "Wir testen auf einem %sx%s Pixel Canvas mit folgenden Pixeln:\n%s",
             width, height, full_input_string);
    free((char*) width);
    free((char*) height);
    free(full_input_string);
    return str;
}
char* render_exercise_1c(Canvas t, exercise_1c_data testcase)
{
    const char *width = format_int(t->width);
    const char *height = format_int(t->height);
    const char *color_x = format_color_enum(testcase.x_channel);
    const char *color_y = format_color_enum(testcase.y_channel);

    int len = strlen("Wir testen auf einem ") + strlen(width) + strlen("x") + strlen(height) +
              strlen(" Pixel Canvas mit dem Farbkanal '") + strlen(color_x) + strlen("' für X und '") +
              strlen(color_y) + strlen("' für Y.") + 1;
    char *str = malloc(len);
    snprintf(str, len, "Wir testen auf einem %sx%s Pixel Canvas mit dem Farbkanal '%s' für X und '%s' für Y.",width,
             height, color_x, color_y);
    free((char*) width);
    free((char*) height);
    free((char*) color_x);
    free((char*) color_y);
    return str;
}
char* render_exercise_2ac(RGB expected, RGB got){

    int len = strlen("Erwartet: R = ") + 6 + strlen(" G = ") + 6 + strlen(" B = ") + 6 + strlen("\n") +
              strlen(TESTRUNNER_LABEL "Erhielt:  R = ") + 6 + strlen(" G = ") + 6 + strlen(" B = ") + 6 + strlen("\n") + 1;
    //The + 6 results from each float in the RGB struct, being printed to four decimal points
    char* context = mallocx(len); //size
    snprintf(context, len, "Erwartet: R = %.4f G = %.4f B = %.4f\n"
                           TESTRUNNER_LABEL "Erhielt:  R = %.4f G = %.4f B = %.4f\n", expected.r, expected.g, expected.b,
                                                                                      got.r, got.g, got.b);

    return context;
}
char* render_exercise_2b(Canvas t, exercise_2b_data testcase)
{
    const char *width = format_int(t->width);
    const char *height = format_int(t->height);

    char* full_input_string = calloc(125, testcase.number_of_pixels * sizeof(char));
    size_t counter = 1;
    for(int i = 0; i < testcase.number_of_pixels; i++){
        char* temp_string = calloc(120, sizeof(char));

        snprintf(temp_string,120,TESTRUNNER_LABEL "\t\t%lu. Pixel mit den Koordinaten: (%d,%d) "
                                 "und dem Farbstruct: R = %.4f G = %.4f B = %.4f\n", counter, testcase.pixel_data[i].x,
                 testcase.pixel_data[i].y, testcase.pixel_data[i].color.r, testcase.pixel_data[i].color.g,
                 testcase.pixel_data[i].color.b);
        counter++;

        strncat(full_input_string,temp_string,strlen(temp_string));
        free(temp_string);
    }

    int len = strlen("Wir testen auf einem ") + strlen(width) + strlen("x") + strlen(height) +
              strlen(" Pixel Canvas mit folgenden Pixeln:\n") + strlen(full_input_string) + 1;
    char *str = malloc(len);
    snprintf(str, len, "Wir testen auf einem %sx%s Pixel Canvas mit folgenden Pixeln:\n%s",
             width, height, full_input_string);
    free((char*) width);
    free((char*) height);
    free(full_input_string);
    return str;
}

int main(int argc, char const *argv[]) {
    Tester tester = tester_new(argc - 1, argv[1], argv[2],
                               "cc -std=c11 -g -Wall "TEST_NAME".c -o "TEST_NAME".o -lm && ./"TEST_NAME".o");
    /* Aufgabe 1a */
    if(begin_exercise(&tester,"swatch_red_green","Aufgabe 1a: Den Canvas mit einem rot-grünen Farbgradienten füllen."))
    {
        for(int i = 0; i < TESTS_1A; i++)
        {
            if(begin_testcase(&tester))
            {
                Canvas expected = canvas_from_file(exercise_1a[i].file_out);
                Canvas got = canvas_from_file(exercise_1a[i].file_in);
                free(got->name);
                got->name = mallocx(strlen("swatch_red_green")+1);
                snprintf(got->name, strlen("swatch_red_green")+1,"swatch_red_green");

                char *args = render_exercise_1a2d(expected,exercise_1a[i]);
                assert_canvas_approx(&tester, expected, swatch_red_green(got), args);
                free(args);

                canvas_free(got);
                canvas_free(expected);
            }
        }
    }
    /* Aufgabe 1b */
    if(begin_exercise(&tester,"canvas_set_channel","Aufgabe 1b: Angebene Farbkanäle per Variable einfärben."))
    {
        for(int i = 0; i < TESTS_1B; i++)
        {
            if(begin_testcase(&tester))
            {
                Canvas expected = canvas_from_file(exercise_1b[i].filename);
                Canvas got = canvas_new_black(expected->width, expected->height, "canvas_set_channel");

                char *args = render_exercise_1b(expected,exercise_1b[i]);
                for(int j = 0; j < exercise_1b[i].number_of_pixels; j++){

                    canvas_set_channel(got, exercise_1b[i].pixel_data[j].x, exercise_1b[i].pixel_data[j].y,
                                       exercise_1b[i].pixel_data[j].channel, exercise_1b[i].pixel_data[j].value);
                }

                assert_canvas(&tester, expected, got, args);
                free(args);

                canvas_free(got);
                canvas_free(expected);
            }
        }
    }
    /* Aufgabe 1c */
    if(begin_exercise(&tester,"swatch_rgb","Aufgabe 1c: Den Canvas mit einem Farbgradienten füllen."))
    {
        for(int i = 0; i < TESTS_1C; i++)
        {
            if(begin_testcase(&tester))
            {
                Canvas expected = canvas_from_file(exercise_1c[i].filename);
                Canvas got = canvas_new_black(expected->width, expected->height, "swatch_rgb");

                char *args = render_exercise_1c(expected,exercise_1c[i]);
                assert_canvas_approx(&tester, expected, swatch_rgb(got, exercise_1c[i].x_channel, exercise_1c[i].y_channel), args);
                free(args);

                canvas_free(got);
                canvas_free(expected);
            }
        }
    }
    /* Aufgabe 2a */
    if(begin_exercise(&tester,"lilac","Aufgabe 2a: Die Farbwerte von 'lilac' zuweisen."))
    {
        if(begin_testcase(&tester))
        {
            RGB expected;
            expected.r = 0.86;
            expected.g = 0.82;
            expected.b = 1.0;
            RGB got = lilac();
            char *args = render_exercise_2ac(expected, got);
            assert_struct(&tester,compare_RGB(expected, got), args);
            free(args);
        }
    }
    /* Aufgabe 2b */
    if(begin_exercise(&tester,"canvas_set_rgb_struct","Aufgabe 2b: Alle Farbkanäle gleichzeitig setzen."))
    {
        for(int i = 0; i < TESTS_2B; i++)
        {
            if(begin_testcase(&tester))
            {
                Canvas expected = canvas_from_file(exercise_2b[i].filename);
                Canvas got = canvas_new(expected->width, expected->height, "canvas_set_rgb_struct");

                for(int j = 0; j < exercise_2b[i].number_of_pixels; j++){

                    canvas_set_rgb_struct(got, exercise_2b[i].pixel_data[j].x, exercise_2b[i].pixel_data[j].y,
                                          exercise_2b[i].pixel_data[j].color);
                }

                char *args = render_exercise_2b(expected,exercise_2b[i]);
                assert_canvas(&tester, expected, got, args);
                free(args);

                canvas_free(got);
                canvas_free(expected);
            }
        }
    }
    /* Aufgabe 2c */
    if(begin_exercise(&tester,"rgb_to_gray","Aufgabe 2c: Farben in ihren Grauton konvertieren."))
    {
        for(int i = 0; i < TESTS_2C; i++)
        {
            if(begin_testcase(&tester))
            {
                RGB got = rgb_to_gray(exercise_2c[i].color_in);
                RGB expected = exercise_2c[i].color_out;
                char *args = render_exercise_2ac(expected, got);
                assert_struct(&tester, compare_RGB(expected, got), args);
                free(args);
            }
        }
    }
    /* Aufgabe 2d */
    if(begin_exercise(&tester,"canvas_to_gray","Aufgabe 2d: Eine komplette Canvas in Grautöne konvertieren."))
    {
        for(int i = 0; i < TESTS_2D; i++)
        {
            if(begin_testcase(&tester))
            {
                Canvas expected = canvas_from_file(exercise_2d[i].file_out);
                Canvas got = canvas_from_file(exercise_2d[i].file_in);
                free(got->name);
                got->name = mallocx(strlen("canvas_to_gray") +1);
                snprintf(got->name, strlen("canvas_to_gray")+1,"canvas_to_gray");

                char *args = render_exercise_1a2d(expected, exercise_2d[i]);
                assert_canvas_approx(&tester, expected, canvas_to_gray(got), args);
                free(args);

                canvas_free(got);
                canvas_free(expected);
            }
        }
    }

    return wrap_up(&tester);
}
