#include "07ex.c"
#include "testrunner.c"
#include "canvas.h"

#define TEST_NAME "07ex_test"
#define RELATIVE_DIRECTORY_PATH "Testdata/" TEST_NAME "data/"
#define TESTS_1A 8
#define TESTS_1B 8
#define TESTS_1C 10
#define TESTS_1D 11
#define TESTS_1E 7
#define TESTS_1F 12
#define TESTS_1G 13

#define TESTS_2A 7
#define TESTS_2B 7
#define TESTS_2C 9
#define TESTS_2D 6
#define TESTS_2E 8
#define TESTS_2F 8
#define TESTS_2G 11

#define TESTS_3A 9
#define TESTS_3B 8
#define TESTS_3C 8
#define TESTS_3D 5
#define TESTS_3E 9
#define TESTS_3F 8
#define TESTS_3G 10

#define TESTS_4 13
#define TESTS_5AB 9

typedef struct Test1
{
    int32_t x;
    int32_t expected_x;
    int32_t y;
    int32_t expected_y;
    bool equal_same;

} exercises_1_data;

typedef struct Test23
{
    RGB x;
    RGB expected_x;
    RGB y;
    RGB expected_y;
    bool equal_same;

} exercises_2_3_data;

typedef struct Test4
{
    int32_t x;
    int32_t expected;

} exercise_4_data;

typedef struct Test5
{

    int32_t expected_count;
    bool expected_stable;
    Layer* pile_array;
    int32_t number_of_layers;

} exercises_5_data;

static exercises_1_data exercise_1a [TESTS_1A] = {
        {.x = 1, .expected_x = 1},
        {.x = 3, .expected_x = 3},
        {.x = 5, .expected_x = 5},
        {.x = 17, .expected_x = 17},
        {.x = 42, .expected_x = 42},
        {.x = 255, .expected_x = 255},
        {.x = 1001, .expected_x = 1001},
        {.x = 9999, .expected_x = 9999},
};
static exercises_1_data exercise_1b [TESTS_1B] = {
        {.x = -1, .expected_x = 42},
        {.x = -3, .expected_x = 42},
        {.x = -5, .expected_x = 42},
        {.x = -17, .expected_x = 42},
        {.x = -42, .expected_x = 42},
        {.x = -255, .expected_x = 42},
        {.x = -1001, .expected_x = 42},
        {.x = -9999, .expected_x = 42},
};
static exercises_1_data exercise_1c [TESTS_1C] = {
        {.x = 523, .expected_x = -55, .y = -55},
        {.x = -12, .expected_x = -29, .y = -29},
        {.x = -232, .expected_x = -10, .y = -10},
        {.x = 10, .expected_x = 1, .y = 1},
        {.x = 85, .expected_x = 4, .y = 4},
        {.x = -8564, .expected_x = 7, .y = 7},
        {.x = 1232, .expected_x = 11, .y = 11},
        {.x = 3850, .expected_x = 100, .y = 100},
        {.x = 8907, .expected_x = 512, .y = 512},
        {.x = -18477, .expected_x = 8765, .y = 8765},
};
static exercises_1_data exercise_1d [TESTS_1D] = {
        {.x = 523, .expected_x = 5687, .y = 5687, .expected_y = 5687},
        {.x = -12, .expected_x = 4444, .y = 4444, .expected_y = 4444},
        {.x = -232, .expected_x = 1500, .y = 1500, .expected_y = 1500},
        {.x = 10, .expected_x = 123, .y = 123, .expected_y = 123},
        {.x = 85, .expected_x = 64, .y = 64, .expected_y = 64},
        {.x = -8564, .expected_x = 9, .y = 9, .expected_y = 9},
        {.x = 1232, .expected_x = -12, .y = -12, .expected_y = -12},
        {.x = 3850, .expected_x = -33, .y = -33, .expected_y = -33},
        {.x = 8907, .expected_x = -225, .y = -225, .expected_y = -225},
        {.x = -18477, .expected_x = -747, .y = -747, .expected_y = -747},
        {.x = 3423, .expected_x = -2023, .y = -2023, .expected_y = -2023},
};
static exercises_1_data exercise_1e [TESTS_1E] = {
        {.x = 1, .expected_x = 2, .y = 2, .expected_y = 1},
        {.x = -23, .expected_x = 51, .y = 51, .expected_y = -23},
        {.x = 17, .expected_x = 12, .y = 12, .expected_y = 17},
        {.x = 1803, .expected_x = 1914, .y = 1914, .expected_y = 1803},
        {.x = -3402, .expected_x = 55000, .y = 55000, .expected_y = -3402},
        {.x = 7065498, .expected_x = 745, .y = 745, .expected_y = 7065498},
        {.x = 96, .expected_x = 69, .y = 69, .expected_y = 96},
};
static exercises_1_data exercise_1f [TESTS_1F] = {
        {.x = 4, .y = 4, .equal_same = true},
        {.x = 6, .y = 7, .equal_same = false},
        {.x = -11, .y = -11, .equal_same = true},
        {.x = 0, .y = -2, .equal_same = false},
        {.x = 17, .y = 17, .equal_same = true},
        {.x = -28, .y = -28, .equal_same = true},
        {.x = 38, .y = 1412, .equal_same = false},
        {.x = 434, .y = 232, .equal_same = false},
        {.x = -7900, .y = -7900, .equal_same = true},
        {.x = 1, .y = 11, .equal_same = false},
        {.x = 111, .y = 1111, .equal_same = false},
        {.x = 15262, .y = 15262, .equal_same = true},
};
static exercises_1_data exercise_1g [TESTS_1G] = {
        {.x = 12312, .y = 1321, .equal_same = false},
        {.x = 1312, .y = 135437, .equal_same = true},
        {.x = 163, .y = 86, .equal_same = false},
        {.x = 14127, .y = 877, .equal_same = true},
        {.x = 18686, .y = 8664, .equal_same = true},
        {.x = 8998, .y = 974, .equal_same = false},
        {.x = 464, .y = 4242, .equal_same = true},
        {.x = 3453, .y = 132672, .equal_same = true},
        {.x = 92241, .y = 65423, .equal_same = true},
        {.x = 74352, .y = 7341, .equal_same = false},
        {.x = 92241, .y = 65423, .equal_same = true},
        {.x = 234674, .y = 43673, .equal_same = false},
        {.x = 67642, .y = 17563, .equal_same = false},
};

static exercises_2_3_data exercise_2a [TESTS_2A] = {
        {.x = {0.1,0.2,0.3}, .expected_x = {0.1,0.2,0.3}},
        {.x = {0.41,0.22,0.76}, .expected_x = {0.41,0.22,0.76}},
        {.x = {0.87,0.3,0.13}, .expected_x = {0.87,0.3,0.13}},
        {.x = {0.0,0.0,0.0}, .expected_x = {0.0,0.0,0.0}},
        {.x = {0.5,0.5,0.5}, .expected_x = {0.5,0.5,0.5}},
        {.x = {0.96,0.64,0.12}, .expected_x = {0.96,0.64,0.12}},
        {.x = {1.0,1.0,1.0}, .expected_x = {1.0,1.0,1.0}},
};
static exercises_2_3_data exercise_2b [TESTS_2B] = {
        {.x = {-0.1,-0.2,-0.3}, .expected_x = {0.86,0.82,1.0}},
        {.x = {-0.41,-0.22,-0.76}, .expected_x = {0.86,0.82,1.0}},
        {.x = {-0.87,-0.3,-0.13}, .expected_x = {0.86,0.82,1.0}},
        {.x = {0.0,0.0,0.0}, .expected_x = {0.86,0.82,1.0}},
        {.x = {-0.5,-0.5,-0.5}, .expected_x = {0.86,0.82,1.0}},
        {.x = {-0.96,-0.64,-0.12}, .expected_x = {0.86,0.82,1.0}},
        {.x = {-1.0,-1.0,-1.0}, .expected_x = {0.86,0.82,1.0}},
};
static exercises_2_3_data exercise_2c [TESTS_2C] = {
        {.x = {0.74,0.326,0.187}, .expected_x = {0.63,0.64,0.65}, .y = {0.63,0.64,0.65}},
        {.x = {0.18,0.73,0.75}, .expected_x = {0.12,0.24,0.6}, .y = {0.12,0.24,0.6}},
        {.x = {0.123,0.15,0.342}, .expected_x = {0.5,0.31,0.4}, .y = {0.5,0.31,0.4}},
        {.x = {0.54,0.07,0.96}, .expected_x = {0.64,0.067,0.24}, .y = {0.64,0.067,0.24}},
        {.x = {0.717,0.59,0.15}, .expected_x = {0.2,0.12,0.53}, .y = {0.2,0.12,0.53}},
        {.x = {0.78,0.20,0.6}, .expected_x = {0.986,0.34,0.123}, .y = {0.986,0.34,0.123}},
        {.x = {0.21,0.452,0.1}, .expected_x = {0.214,0.665,0.131}, .y = {0.214,0.665,0.131}},
        {.x = {0.674,0.953,0.623}, .expected_x = {0.98,0.234,0.73}, .y = {0.98,0.234,0.73}},
        {.x = {0.0,0.27,0.245}, .expected_x = {0.123,0.456,0.678}, .y = {0.123,0.456,0.678}},
};
static exercises_2_3_data exercise_2d [TESTS_2D] = {
        {.x = {0.1,0.2,0.3}, .expected_x = {0.3,0.2,0.1}, .y = {0.3,0.2,0.1}, .expected_y = {0.3,0.2,0.1}},
        {.x = {0.22,0.564,0.85}, .expected_x = {0.907,0.56,0.13}, .y = {0.907,0.56,0.13}, .expected_y = {0.907,0.56,0.13}},
        {.x = {0.74,0.1321,0.53}, .expected_x = {0.23,0.653,0.34}, .y = {0.23,0.653,0.34}, .expected_y = {0.23,0.653,0.34}},
        {.x = {0.68,0.67,0.66}, .expected_x = {0.123,0.456,0.789}, .y ={0.123,0.456,0.789}, .expected_y = {0.123,0.456,0.789}},
        {.x = {0.86,0.57,0.75}, .expected_x = {0.111,0.444,0.777}, .y = {0.111,0.444,0.777}, .expected_y = {0.111,0.444,0.777}},
        {.x = {0.165,0.63,0.175}, .expected_x = {0.0,0.0,0.0}, .y = {0.0,0.0,0.0}, .expected_y = {0.0,0.0,0.0}},
};
static exercises_2_3_data exercise_2e [TESTS_2E] = {
        {.x = {0.5,0.5,0.5}, .expected_x = {1.0,1.0,1.0}, .y = {1.0,1.0,1.0}, .expected_y = {0.5,0.5,0.5}},
        {.x = {0.23,0.15,0.75}, .expected_x = {0.74,0.1,0.34}, .y = {0.74,0.1,0.34}, .expected_y = {0.23,0.15,0.75}},
        {.x = {0.6,0.5,0.65}, .expected_x = {0.5,0.6,0.56}, .y = {0.5,0.6,0.56}, .expected_y = {0.6,0.5,0.65}},
        {.x = {0.11,0.22,0.33}, .expected_x = {0.55,0.77,0.99}, .y = {0.55,0.77,0.99}, .expected_y = {0.11,0.22,0.33}},
        {.x = {0.89,0.2,0.13}, .expected_x = {0.86,0.82,1.0}, .y = {0.86,0.82,1.0}, .expected_y = {0.89,0.2,0.13}},
        {.x = {0.0,1.0,0.0}, .expected_x = {1.0,0.0,0.0}, .y = {1.0,0.0,0.0}, .expected_y = {0.0,1.0,0.0}},
        {.x = {0.765,0.4,0.24}, .expected_x = {0.242,0.785,0.98}, .y = {0.242,0.785,0.98}, .expected_y = {0.765,0.4,0.24}},
        {.x = {0.1,0.33,0.7}, .expected_x = {0.4,0.5,0.1}, .y = {0.4,0.5,0.1}, .expected_y = {0.1,0.33,0.7}},
};
static exercises_2_3_data exercise_2f [TESTS_2F] = {
        {.x = {0.56,0.67,0.78}, .y = {0.56,0.67,0.78}, .equal_same = true},
        {.x = {0.874,0.24,0.123}, .y = {0.85,0.02,0.445}, .equal_same = false},
        {.x = {0.8,0.7,0.5}, .y = {0.51,0.71,0.91}, .equal_same = false},
        {.x = {0.75,0.25,0.5}, .y = {0.75,0.25,0.5}, .equal_same = true},
        {.x = {1.0,0.1,1.0}, .y = {1.0,0.1,1.0}, .equal_same = true},
        {.x = {0.0,0.0,0.0}, .y = {0.04,0.02,0.01}, .equal_same = false},
        {.x = {0.95,0.242,0.237}, .y = {0.4,0.22,0.7323}, .equal_same = false},
        {.x = {0.0,0.0,0.0}, .y = {0.0,0.0,0.0}, .equal_same = true},
};
static exercises_2_3_data exercise_2g [TESTS_2G] = {
        {.x = {0.0,0.0,0.0}, .y = {0.0,0.0,0.0}, .equal_same = false},
        {.x = {0.1312,0.53,0.64}, .y = {0.644,0.23,0.234}, .equal_same = true},
        {.x = {0.87,0.987,0.32}, .y = {0.423,0.645,0.786}, .equal_same = true},
        {.x = {0.74,0.7,0.4}, .y = {0.5,0.55,0.555}, .equal_same = false},
        {.x = {0.86,0.53,0.543}, .y = {0.534,0.53,0.43}, .equal_same = false},
        {.x = {0.98,0.64,0.18}, .y = {0.93,0.28,0.125}, .equal_same = false},
        {.x = {0.86,0.82,1.0}, .y = {0.75,0.71,0.9}, .equal_same = true},
        {.x = {0.74,0.896,0.267}, .y = {0.186,0.923,0.63}, .equal_same = false},
        {.x = {0.784,0.954,0.23}, .y = {0.75,0.95,0.26}, .equal_same = true},
        {.x = {0.5,0.5,0.5}, .y = {0.6,0.7,0.1}, .equal_same = true},
        {.x = {0.676,0.87,0.675}, .y = {0.64,0.42,0.27}, .equal_same = false},
};

static exercises_2_3_data exercise_3a [TESTS_3A] = {
        {.x = {0.3,0.2,0.1}, .expected_x = {0.3,0.2,0.1}},
        {.x = {0.443,0.72,0.875}, .expected_x = {0.443,0.72,0.875}},
        {.x = {0.0,0.0,0.0}, .expected_x = {0.0,0.0,0.0}},
        {.x = {0.65,0.35,0.13}, .expected_x = {0.65,0.35,0.13}},
        {.x = {0.15,0.25,0.35}, .expected_x = {0.15,0.25,0.35}},
        {.x = {0.96,0.64,0.12}, .expected_x = {0.96,0.64,0.12}},
        {.x = {0.5,0.5,0.5}, .expected_x = {0.5,0.5,0.5}},
        {.x = {0.64,0.466,0.555}, .expected_x = {0.64,0.466,0.555}},
        {.x = {1.0,1.0,1.0}, .expected_x = {1.0,1.0,1.0}},
};
static exercises_2_3_data exercise_3b [TESTS_3B] = {
        {.x = {0.86,0.82,1.0}, .expected_x = {0.86,0.82,0.0}},
        {.x = {0.42,0.22,0.76}, .expected_x = {0.42,0.22,0.0}},
        {.x = {0.65,0.43,0.23}, .expected_x = {0.65,0.43,0.0}},
        {.x = {0.1,0.1,0.1}, .expected_x = {0.1,0.1,0.0}},
        {.x = {0.5,0.5,0.5}, .expected_x = {0.5,0.5,0.0}},
        {.x = {0.42,0.42,0.42}, .expected_x = {0.42,0.42,0.0}},
        {.x = {0.945,0.664,0.1221}, .expected_x = {0.945,0.664,0.0}},
        {.x = {1.0,1.0,1.0}, .expected_x = {1.0,1.0,0.0}},
};
static exercises_2_3_data exercise_3c [TESTS_3C] = {
        {.x = {0.745,0.36,0.17}, .expected_x = {0.745,0.36,0.65}, .y = {0.63,0.64,0.65}},
        {.x = {0.780,0.25,0.35}, .expected_x = {0.780,0.25,0.321}, .y = {0.34,0.986,0.321}},
        {.x = {0.123,0.99,0.642}, .expected_x = {0.123,0.99,0.31}, .y = {0.7,0.4,0.31}},
        {.x = {0.0,0.27,0.245}, .expected_x = {0.0,0.27,0.678}, .y = {0.123,0.456,0.678}},
        {.x = {0.856,0.09,0.44}, .expected_x = {0.856,0.09,0.64}, .y = {0.34,0.067,0.64}},
        {.x = {0.18,0.43,0.75}, .expected_x = {0.18,0.43,0.48}, .y = {0.12,0.24,0.48}},
        {.x = {0.211,0.452,0.8}, .expected_x = {0.211,0.452,0.664}, .y = {0.137,0.215,0.664}},
        {.x = {0.654,0.623,0.953}, .expected_x = {0.654,0.623,0.652}, .y = {0.92,0.234,0.652}},
};
static exercises_2_3_data exercise_3d [TESTS_3D] = {
        {.x = {0.68,0.67,0.66}, .expected_x = {0.68,0.67,0.789}, .y ={0.123,0.456,0.789}, .expected_y = {0.123,0.456,0.789}},
        {.x = {0.225,0.54,0.75}, .expected_x = {0.225,0.54,0.133}, .y = {0.907,0.56,0.133}, .expected_y = {0.907,0.56,0.133}},
        {.x = {0.1,0.2,0.3}, .expected_x = {0.1,0.2,0.1}, .y = {0.3,0.2,0.1}, .expected_y = {0.3,0.2,0.1}},
        {.x = {0.86,0.82,1.0}, .expected_x = {0.86,0.82,0.777}, .y = {0.111,0.444,0.777}, .expected_y = {0.111,0.444,0.777}},
        {.x = {0.426,0.54,0.432}, .expected_x = {0.426,0.54,0.0}, .y = {0.0,0.0,0.0}, .expected_y = {0.0,0.0,0.0}},
};
static exercises_2_3_data exercise_3e [TESTS_3E] = {
        {.x = {0.1,0.33,0.67}, .expected_x =  {0.1,0.33,0.3}, .y = {0.4,0.5,0.3}, .expected_y = {0.4,0.5,0.67}},
        {.x = {0.5,0.5,0.5}, .expected_x = {0.5,0.5,1.0}, .y = {1.0,1.0,1.0}, .expected_y = {1.0,1.0,0.5}},
        {.x = {0.111,0.222,0.333}, .expected_x = {0.111,0.222,0.999}, .y = {0.555,0.777,0.999}, .expected_y = {0.555,0.777,0.333}},
        {.x = {0.0,1.0,0.0}, .expected_x = {0.0,1.0,0.0}, .y = {1.0,0.0,0.0}, .expected_y = {1.0,0.0,0.0}},
        {.x = {0.324,0.17,0.85}, .expected_x = {0.324,0.17,0.96}, .y = {0.64,0.1,0.96}, .expected_y = {0.64,0.1,0.85}},
        {.x = {0.6,0.5,0.65}, .expected_x = {0.6,0.5,0.56}, .y = {0.5,0.6,0.56}, .expected_y = {0.5,0.6,0.65}},
        {.x = {0.564,0.287,0.77}, .expected_x = {0.564,0.287,0.57}, .y = {0.76,0.45,0.57}, .expected_y = {0.76,0.45,0.77}},
        {.x = {0.13,0.3,0.89}, .expected_x = {0.13,0.3,1.0}, .y = {0.86,0.82,1.0}, .expected_y = {0.86,0.82,0.89}},
        {.x = {0.675,0.45,0.45}, .expected_x = {0.675,0.45,0.32}, .y = {0.32,0.7755,0.32}, .expected_y = {0.32,0.7755,0.45}},
};
static exercises_2_3_data exercise_3f [TESTS_3F] = {
        {.x = {1.0,0.1,1.0}, .y = {1.0,0.6,1.0}, .equal_same = true},
        {.x = {0.9,0.22,0.237}, .y = {0.6,0.47,0.7323}, .equal_same = false},
        {.x = {0.0,0.03,0.0}, .y = {0.04,0.02,0.01}, .equal_same = false},
        {.x = {0.56,0.67,0.78}, .y = {0.56,0.67,0.78}, .equal_same = true},
        {.x = {0.4363,0.9876,0.123}, .y = {0.85,0.02,0.123}, .equal_same = true},
        {.x = {0.0,0.0,0.0}, .y = {0.0,0.0,0.0}, .equal_same = true},
        {.x = {0.643,0.765,0.136}, .y = {0.85,0.02,0.445}, .equal_same = false},
        {.x = {0.86,0.82,1.0}, .y = {0.86,0.82,1.0}, .equal_same = true},
};
static exercises_2_3_data exercise_3g [TESTS_3G] = {
        {.x = {0.644,0.23,0.234}, .y = {0.1312,0.53,0.64}, .equal_same = true},
        {.x = {0.0,0.0,0.0}, .y = {0.0,0.0,0.0}, .equal_same = false},
        {.x = {0.78,0.34,0.65}, .y = {0.555,0.55,0.5}, .equal_same = false},
        {.x = {0.68,0.74,0.23}, .y = {0.91,0.27,0.125}, .equal_same = false},
        {.x = {0.52,0.54,0.56}, .y = {0.6,0.7,0.1}, .equal_same = true},
        {.x = {0.576,0.67,0.875}, .y = {0.65,0.442,0.217}, .equal_same = false},
        {.x = {0.87,0.987,0.32}, .y = {0.423,0.645,0.786}, .equal_same = true},
        {.x = {0.86,0.82,1.0}, .y = {0.77,0.72,0.91}, .equal_same = true},
        {.x = {0.744,0.994,0.23}, .y = {0.95,0.75,0.25}, .equal_same = true},
        {.x = {0.2,0.1,0.05}, .y = {0.5,0.25,0.125}, .equal_same = false},
};

static exercise_4_data exercise_4 [TESTS_4] = {
        {.x = 1, .expected = 1940},
        {.x = -1, .expected = -1084},
        {.x = 13, .expected = 187109},
        {.x = 25, .expected = 17435},
        {.x = 42, .expected = 5707},
        {.x = -7, .expected = -4080},
        {.x = -52, .expected = -2625},
        {.x = -365, .expected = 428},
        {.x = 100, .expected = 2739},
        {.x = 256, .expected = 1169},
        {.x = 2023, .expected = 428},
        {.x = 9, .expected = 37381},
        {.x = 6174, .expected = 428},
};

static Layer exercise5recipe1 [1]= {ActualPancake,};
static Layer exercise5recipe2 [2]= {Fruit,Cream,};
static Layer exercise5recipe3 [4]= {ActualPancake,Fruit,Cream,ActualPancake,};
static Layer exercise5recipe4 [6]= {ActualPancake,ActualPancake,ActualPancake,ActualPancake,ActualPancake,Cream,};
static Layer exercise5recipe5 [8]= {ActualPancake,Cream,ActualPancake,Fruit,ActualPancake,Cream,ActualPancake,Fruit,};
static Layer exercise5recipe6 [3]= {ActualPancake,ActualPancake,ActualPancake,};
static Layer exercise5recipe7 [11]= {Fruit,Fruit,Fruit,Fruit,Fruit,Fruit,Fruit,Fruit,Fruit,Cream,Cream,};
static Layer exercise5recipe8 [10]= {Cream,Fruit,Fruit,Cream,ActualPancake,ActualPancake,Fruit,Cream,Fruit,ActualPancake};
static Layer exercise5recipe9 [9]= {ActualPancake,Fruit,Cream,Fruit,ActualPancake,Fruit,Cream,ActualPancake,ActualPancake};

static exercises_5_data exercise_5ab [TESTS_5AB] = {
        {.expected_count = 0, .expected_stable = true, .pile_array = exercise5recipe1, .number_of_layers = 1},
        {.expected_count = 1, .expected_stable = false, .pile_array = exercise5recipe2, .number_of_layers = 2},
        {.expected_count = 1, .expected_stable = true, .pile_array = exercise5recipe3, .number_of_layers = 4},
        {.expected_count = 0, .expected_stable = false, .pile_array = exercise5recipe4, .number_of_layers = 6},
        {.expected_count = 2, .expected_stable = false, .pile_array = exercise5recipe5, .number_of_layers = 8},
        {.expected_count = 0, .expected_stable = true, .pile_array = exercise5recipe6, .number_of_layers = 3},
        {.expected_count = 9, .expected_stable = false, .pile_array = exercise5recipe7, .number_of_layers = 11},
        {.expected_count = 4, .expected_stable = false, .pile_array = exercise5recipe8, .number_of_layers = 10},
        {.expected_count = 3, .expected_stable = true, .pile_array = exercise5recipe9, .number_of_layers = 9},
};

int compare_RGB(RGB expected, RGB got){
    int result = 1;
    if((fabsf(expected.r - got.r) >= 0.0001) || (fabsf(expected.g - got.g) >= 0.0001)
       || (fabsf(expected.b - got.b) >= 0.0001) ){
        result = 0;
    }
    return result;
}
PileOfPancakes* create_pile(Layer* layer_array, size_t layers){
    PileOfPancakes* first = mallocx(sizeof(PileOfPancakes));
    first->layer = layer_array[0];
    first->further_layers = NULL;
    PileOfPancakes* current = first;
    PileOfPancakes* next = NULL;
    for(int i = 1; i < layers; i++){
        next = mallocx(sizeof(PileOfPancakes));
        next->layer = layer_array[i];
        next->further_layers = NULL;
        current->further_layers = next;
        current = next;
    }
    return first;
}
void eat_pile(PileOfPancakes* pile){
    PileOfPancakes* current = pile;
    PileOfPancakes* next;
    while(current != NULL){
        next = current->further_layers;
        free(current);
        current = next;
    }
}

char* render_exercise_1e(exercises_1_data testcase)
{
    const char *x = format_int(testcase.x);
    const char *y = format_int(testcase.y);
    int len = strlen("x =  und y = ") + strlen(x) + strlen(y) + 1;
    char *str = mallocx(len);
    snprintf(str, len, "x = %s und y = %s", x, y);
    free((char*) x);
    free((char*) y);
    return str;
}
char* render_exercises_23(RGB expected, RGB got, bool X_or_Y){

    int len = strlen("Wir testen x:\n") + strlen(TESTRUNNER_LABEL "Erwartet: R = ") + 7 + strlen(" G = ") + 7 +
              strlen(" B = ") + 7 + strlen("\n") + strlen(TESTRUNNER_LABEL "Erhielt:  R = ") + 7 +
              strlen(" G = ") + 7 + strlen(" B = ") + 7 + strlen("\n") + 1;
    //The + 7 results from each float in the RGB struct being printed to four decimal points, potentially with a - sign
    char* context = mallocx(len); //size
    snprintf(context, len +4, "Wir testen %s:\n" TESTRUNNER_LABEL "Erwartet: R = %.4f G = %.4f B = %.4f\n"
                           TESTRUNNER_LABEL "Erhielt:  R = %.4f G = %.4f B = %.4f\n", X_or_Y?"x":"y", expected.r,
                           expected.g, expected.b, got.r, got.g, got.b);

    return context;
}
char* render_exercise_4(exercise_4_data testcase)
{
    const char *x = format_int(testcase.x);
    int len = strlen("Wir berechnen den frumbleflabblefizzledipp von x = .") + strlen(x) + 1;
    char *str = mallocx(len);
    snprintf(str, len, "Wir berechnen den frumbleflabblefizzledipp von x = %s.", x);
    free((char*) x);
    return str;
}
char* render_exercises_5(exercises_5_data testcase)
{
    const char *layer_count = format_int(testcase.number_of_layers);

    char* full_input_string = calloc(125, testcase.number_of_layers * sizeof(char));
    size_t counter = 1;
    for(int i = 0; i < testcase.number_of_layers; i++){
        char* temp_string = calloc(60, sizeof(char));

        if(testcase.pile_array[i] == Cream){
            snprintf(temp_string,60,TESTRUNNER_LABEL " %lu.\t\t ~~@     Cream      @~~\n", counter);
        }
        if(testcase.pile_array[i] == Fruit){
            snprintf(temp_string,60,TESTRUNNER_LABEL " %lu.\t\t •¤0     Fruit      0¤•\n", counter);
        }
        if(testcase.pile_array[i] == ActualPancake){
            snprintf(temp_string,60,TESTRUNNER_LABEL " %lu.\t\t === Actual Pancake ===\n", counter);
        }
        counter++;

        strncat(full_input_string,temp_string,strlen(temp_string));
        free(temp_string);
    }
    char* plate = TESTRUNNER_LABEL "   \t        ¯¯--------------------¯¯\n";

    size_t len = strlen("Wir bauen folgenden Pancake-Pile aus ") + strlen(layer_count) + strlen(" Lagen:\n\n")
            + strlen(full_input_string) + strlen(plate) + 1;
    char *str = mallocx(len);
    snprintf(str, len, "Wir bauen folgenden Pancake-Pile aus %s Lagen:\n\n%s%s",
             layer_count, full_input_string,plate);
    free((char*) layer_count);
    free(full_input_string);
    return str;
}


int main(int argc, char const *argv[]) {
    Tester tester = tester_new(argc - 1, argv[1], argv[2],
                               "cc -std=c11 -g -Wall "TEST_NAME".c -o "TEST_NAME".o -lm && ./"TEST_NAME".o");

    /* Aufgabe 1a */
    if(begin_exercise(&tester,"retrieve_from_pointer","Aufgabe 1a: Speicherort eines Pointers lesen."))
    {
        for (int i = 0; i < TESTS_1A; i++)
        {
            if(begin_testcase(&tester))
            {
                assert_int(&tester, exercise_1a[i].expected_x, retrieve_from_pointer(&(exercise_1a[i].x)), "");
            }
        }
    }
    /* Aufgabe 1b */
    if(begin_exercise(&tester,"set_through_pointer1","Aufgabe 1b: Speicherort eines Pointers auf 42 setzen."))
    {
        for (int i = 0; i < TESTS_1B; i++)
        {
            if(begin_testcase(&tester))
            {
                set_through_pointer1(&(exercise_1b[i].x));
                assert_int(&tester, exercise_1b[i].expected_x, exercise_1b[i].x, "");
            }
        }
    }
    /* Aufgabe 1c */
    if(begin_exercise(&tester,"set_through_pointer2","Aufgabe 1c: Speicherort eines Pointers auf y setzen."))
    {
        for (int i = 0; i < TESTS_1C; i++)
        {
            if(begin_testcase(&tester))
            {
                set_through_pointer2(&(exercise_1c[i].x), exercise_1c[i].y);
                assert_int(&tester, exercise_1c[i].expected_x, exercise_1c[i].x, "");
            }
        }
    }
    /* Aufgabe 1d */
    if(begin_exercise(&tester,"set_through_pointer3","Aufgabe 1d: Speicherort eines Pointers auf den Wert bei y setzen."))
    {
        for (int i = 0; i < TESTS_1D; i++)
        {
            if(begin_testcase(&tester))
            {
                set_through_pointer3(&(exercise_1d[i].x), &(exercise_1d[i].y));
                assert_int(&tester, exercise_1d[i].expected_x, exercise_1d[i].x, "");
                assert_int(&tester, exercise_1d[i].expected_y, exercise_1d[i].y, "Wir testen ob 'y' unverändert ist.");
            }
        }
    }
    /* Aufgabe 1e */
    if(begin_exercise(&tester,"swap","Aufgabe 1e: Wert bei x und Wert bei y vertauschen."))
    {
        for (int i = 0; i < TESTS_1E; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercise_1e(exercise_1e[i]);
                swap(&(exercise_1e[i].x), &(exercise_1e[i].y));
                assert_int(&tester, exercise_1e[i].expected_x, exercise_1e[i].x, args);
                assert_int(&tester, exercise_1e[i].expected_y, exercise_1e[i].y, args);
                free(args);
            }
        }
    }
    /* Aufgabe 1f */
    if(begin_exercise(&tester,"point_to_equal_values","Aufgabe 1f: Überprüfen ob Speicherorte den gleichen Wert haben."))
    {
        for (int i = 0; i < TESTS_1F; i++)
        {
            if(begin_testcase(&tester))
            {
                assert_bool(&tester, exercise_1f[i].equal_same,
                            point_to_equal_values(&(exercise_1f[i].x), &(exercise_1f[i].y)), "");
            }
        }
    }
    /* Aufgabe 1g */
    if(begin_exercise(&tester,"point_to_same_values","Aufgabe 1g: Überprüfen ob zwei Variablen auf den "
                                                     "selben Speicherort zeigen."))
    {
        for (int i = 0; i < TESTS_1G; i++)
        {
            if(begin_testcase(&tester))
            {
                if(exercise_1g[i].equal_same){
                    assert_bool(&tester, exercise_1g[i].equal_same,
                                point_to_same_values(&(exercise_1g[i].x), &(exercise_1g[i].x)), "");
                } else {
                    assert_bool(&tester, exercise_1g[i].equal_same,
                                point_to_same_values(&(exercise_1g[i].x), &(exercise_1g[i].y)), "");
                }
            }
        }
    }

    /* Aufgabe 2a */
    if(begin_exercise(&tester,"retrieve_from_pointer_struct","Aufgabe 2a: Speicherort eines Struct-Pointers lesen."))
    {
        for (int i = 0; i < TESTS_2A; i++)
        {
            if(begin_testcase(&tester))
            {
                RGB retrieved = retrieve_from_pointer_struct(&exercise_2a[i].x);
                char *args = render_exercises_23(exercise_2a[i].expected_x, retrieved, true);
                int res = compare_RGB(retrieved, exercise_2a[i].expected_x);
                assert_struct(&tester, res, args);
                free(args);
            }
        }
    }
    /* Aufgabe 2b */
    if(begin_exercise(&tester,"set_through_pointer_struct1","Aufgabe 2b: Speicherort eines Struct-Pointers auf 'Flieder' setzen."))
    {
        for (int i = 0; i < TESTS_2B; i++)
        {
            if(begin_testcase(&tester))
            {
                set_through_pointer_struct1(&exercise_2b[i].x);
                char *args = render_exercises_23(exercise_2b[i].expected_x, exercise_2b[i].x, true);
                assert_struct(&tester, compare_RGB(exercise_2b[i].x, exercise_2b[i].expected_x), args);
                free(args);
            }
        }
    }
    /* Aufgabe 2c */
    if(begin_exercise(&tester,"set_through_pointer_struct2","Aufgabe 2c: Speicherort eines Struct-Pointers auf y setzen."))
    {
        for (int i = 0; i < TESTS_2C; i++)
        {
            if(begin_testcase(&tester))
            {
                set_through_pointer_struct2(&exercise_2c[i].x, exercise_2c[i].y);
                char *args = render_exercises_23(exercise_2c[i].expected_x, exercise_2c[i].x, true);
                assert_struct(&tester, compare_RGB(exercise_2c[i].x, exercise_2c[i].expected_x), args);
                free(args);
            }
        }
    }
    /* Aufgabe 2d */
    if(begin_exercise(&tester,"set_through_pointer_struct3","Aufgabe 2d: Speicherort eines Struct-Pointers auf "
                                                            "den Wert bei y setzen."))
    {
        for (int i = 0; i < TESTS_2D; i++)
        {
            if(begin_testcase(&tester))
            {
                set_through_pointer_struct3(&(exercise_2d[i].x), &(exercise_2d[i].y));
                char *args = render_exercises_23(exercise_2d[i].expected_x, exercise_2d[i].x, true);
                assert_struct(&tester, compare_RGB(exercise_2d[i].x, exercise_2d[i].expected_x), args);
                free(args);
                args = render_exercises_23(exercise_2d[i].expected_y, exercise_2d[i].y, false);
                assert_struct(&tester, compare_RGB(exercise_2d[i].y, exercise_2d[i].expected_y), args);
                free(args);
            }
        }
    }
    /* Aufgabe 2e */
    if(begin_exercise(&tester,"swap_struct","Aufgabe 2e: Wert bei x und Wert bei y vertauschen."))
    {
        for (int i = 0; i < TESTS_2E; i++)
        {
            if(begin_testcase(&tester))
            {
                swap_struct(&(exercise_2e[i].x), &(exercise_2e[i].y));
                char *args = render_exercises_23(exercise_2e[i].expected_x, exercise_2e[i].x, true);
                assert_struct(&tester, compare_RGB(exercise_2e[i].x, exercise_2e[i].expected_x), args);
                free(args);
                args = render_exercises_23(exercise_2e[i].expected_y, exercise_2e[i].y, false);
                assert_struct(&tester, compare_RGB(exercise_2e[i].y, exercise_2e[i].expected_y), args);
                free(args);
            }
        }
    }
    /* Aufgabe 2f */
    if(begin_exercise(&tester,"point_to_equal_values_struct","Aufgabe 2f: Überprüfen ob Speicherorte von structs "
                                                             "den gleichen Wert haben."))
    {
        for (int i = 0; i < TESTS_2F; i++)
        {
            if(begin_testcase(&tester))
            {
                assert_bool(&tester, exercise_2f[i].equal_same,
                            point_to_equal_values_struct(&(exercise_2f[i].x), &(exercise_2f[i].y)), "");
            }
        }
    }
    /* Aufgabe 2g */
    if(begin_exercise(&tester,"point_to_same_values_struct","Aufgabe 2g: Überprüfen ob zwei struct-Variablen auf den "
                                                     "selben Speicherort zeigen."))
    {
        for (int i = 0; i < TESTS_2G; i++)
        {
            if(begin_testcase(&tester))
            {
                if(exercise_2g[i].equal_same){
                    assert_bool(&tester, exercise_2g[i].equal_same,
                                point_to_same_values_struct(&(exercise_2g[i].x), &(exercise_2g[i].x)), "");
                } else {
                    assert_bool(&tester, exercise_2g[i].equal_same,
                                point_to_same_values_struct(&(exercise_2g[i].x), &(exercise_2g[i].y)), "");
                }
            }
        }
    }
    /* Aufgabe 3a */
    if(begin_exercise(&tester,"retrieve_from_pointer_field","Aufgabe 3a: Speicherort eines Feldes vom Struct-Pointer "
                                                            "lesen."))
    {
        for (int i = 0; i < TESTS_3A; i++)
        {
            if(begin_testcase(&tester))
            {
                assert_float(&tester, exercise_3a[i].expected_x.b, retrieve_from_pointer_field(&exercise_3a[i].x), "");
            }
        }
    }
    /* Aufgabe 3b */
    if(begin_exercise(&tester,"set_through_pointer_field1","Aufgabe 3b: Speicherort eines Feldes vom Struct-Pointers "
                                                           "auf 0 setzen."))
    {
        for (int i = 0; i < TESTS_3B; i++)
        {
            if(begin_testcase(&tester))
            {
                set_through_pointer_field1(&exercise_3b[i].x);
                char *args = render_exercises_23(exercise_3b[i].expected_x, exercise_3b[i].x, true);
                assert_struct(&tester, compare_RGB(exercise_3b[i].x, exercise_3b[i].expected_x), args);
                free(args);
            }
        }
    }
    /* Aufgabe 3c */
    if(begin_exercise(&tester,"set_through_pointer_field2","Aufgabe 3c: Speicherort eines Feldes vom Struct-Pointer auf"
                                                           " ein Feld des Structs y setzen."))
    {
        for (int i = 0; i < TESTS_3C; i++)
        {
            if(begin_testcase(&tester))
            {
                set_through_pointer_field2(&exercise_3c[i].x, exercise_3c[i].y);
                char *args = render_exercises_23(exercise_3c[i].expected_x, exercise_3c[i].x, true);
                assert_struct(&tester, compare_RGB(exercise_3c[i].x, exercise_3c[i].expected_x), args);
                free(args);
            }
        }
    }
    /* Aufgabe 3d */
    if(begin_exercise(&tester,"set_through_pointer_field3","Aufgabe 3d: Speicherort eines Struct-Pointers auf "
                                                            "den Wert bei y setzen."))
    {
        for (int i = 0; i < TESTS_3D; i++)
        {
            if(begin_testcase(&tester))
            {
                set_through_pointer_field3(&(exercise_3d[i].x), &(exercise_3d[i].y));
                char *args = render_exercises_23(exercise_3d[i].expected_x, exercise_3d[i].x, true);
                assert_struct(&tester, compare_RGB(exercise_3d[i].x, exercise_3d[i].expected_x), args);
                free(args);
                args = render_exercises_23(exercise_3d[i].expected_y, exercise_3d[i].y, false);
                assert_struct(&tester, compare_RGB(exercise_3d[i].y, exercise_3d[i].expected_y), args);
                free(args);
            }
        }
    }
    /* Aufgabe 3e */
    if(begin_exercise(&tester,"swap_field","Aufgabe 3e: Wert eines Feldes von x und y vertauschen."))
    {
        for (int i = 0; i < TESTS_3E; i++)
        {
            if(begin_testcase(&tester))
            {
                swap_field(&(exercise_3e[i].x), &(exercise_3e[i].y));
                char *args = render_exercises_23(exercise_3e[i].expected_x, exercise_3e[i].x, true);
                assert_struct(&tester, compare_RGB(exercise_3e[i].x, exercise_3e[i].expected_x), args);
                free(args);
                args = render_exercises_23(exercise_3e[i].expected_y, exercise_3e[i].y, false);
                assert_struct(&tester, compare_RGB(exercise_3e[i].y, exercise_3e[i].expected_y), args);
                free(args);
            }
        }
    }
    /* Aufgabe 3f */
    if(begin_exercise(&tester,"point_to_equal_values_field","Aufgabe 3f: Überprüfen ob Felder von Structs "
                                                             "den gleichen Wert haben."))
    {
        for (int i = 0; i < TESTS_3F; i++)
        {
            if(begin_testcase(&tester))
            {
                assert_bool(&tester, exercise_3f[i].equal_same,
                            point_to_equal_values_field(&(exercise_3f[i].x), &(exercise_3f[i].y)), "");
            }
        }
    }
    /* Aufgabe 3g */
    if(begin_exercise(&tester,"point_to_same_values_field","Aufgabe 3g: Überprüfen ob zwei struct-Variablen ein Feld mit "
                                                            "identischem Speicherort enthalten."))
    {
        for (int i = 0; i < TESTS_3G; i++)
        {
            if(begin_testcase(&tester))
            {
                if(exercise_3g[i].equal_same){
                    assert_bool(&tester, exercise_3g[i].equal_same,
                                point_to_same_values_field(&(exercise_3g[i].x), &(exercise_3g[i].x)), "");
                } else {
                    assert_bool(&tester, exercise_3g[i].equal_same,
                                point_to_same_values_field(&(exercise_3g[i].x), &(exercise_3g[i].y)), "");
                }
            }
        }
    }
    /* Aufgabe 4 */
    if(begin_exercise(&tester,"frumpleflabblefizzledipp","Aufgabe 4: Berechnen des frumpleflabblefizzledipp!"))
    {
        for (int i = 0; i < TESTS_4; i++)
        {
            if(begin_testcase(&tester))
            {
                int z = frumpleflabblefizzledipp(exercise_4[i].x);
                char *args = render_exercise_4(exercise_4[i]);
                assert_int(&tester, exercise_4[i].expected, z, args);
                free(args);
            }
        }
    }
    /* Aufgabe 5a */
    if(begin_exercise(&tester,"count_fruit_layers","Aufgabe 5a: Die Anzahl an Fruchtschichten eines Pancake-Piles zählen."))
    {
        for (int i = 0; i < TESTS_5AB; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercises_5(exercise_5ab[i]);
                PileOfPancakes* pile = create_pile(exercise_5ab[i].pile_array, exercise_5ab[i].number_of_layers);
                assert_int(&tester, exercise_5ab[i].expected_count, count_fruit_layers(*pile), args);
                free(args);
                eat_pile(pile);
            }
        }
    }
    /* Aufgabe 5b */
    if(begin_exercise(&tester,"is_stable","Aufgabe 5b: Überprüfen ob ein Pancake-Pile stabil steht."))
    {
        for (int i = 0; i < TESTS_5AB; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercises_5(exercise_5ab[i]);
                PileOfPancakes* pile = create_pile(exercise_5ab[i].pile_array, exercise_5ab[i].number_of_layers);
                assert_bool(&tester, exercise_5ab[i].expected_stable, is_stable(*pile), args);
                free(args);
                eat_pile(pile);
            }
        }
    }

    return wrap_up(&tester);
}
