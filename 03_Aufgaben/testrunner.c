#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "canvas.h"

#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define TESTRUNNER_LABEL "===  "

#define NUM_HAPPY_FACES 5
#define NUM_WORKING_FACES 6

/* INSTRUCTIONS FOR GRADING THROUGH HORUS
 *
 * For grading purposes, call the tester separately for each exercise, with a testcase-filter of -100.
 * The -100 gets intercepted and activates the HORUS-interface while not interfering with the testcases.
 * The testrunner runs through the entire exercise as expected, but will return either 0 or 100 for fail/pass.
 *
 * Students, if you read this and you're tempted to try to outfox it, feel free to try!
 * But remember that we grade server-side! ;)
 */



static const char *const happy_faces[NUM_HAPPY_FACES] = {"\\(^o^)/", "(*^0^*)", "\\(~o~)/", "o_o)/\\(o_o", "(^_^)"};
static const char *const working_faces[NUM_WORKING_FACES] = {"(-_-;)", "<(`^`)>", "\\_(-_-)_/ ", "(~_~;)", "(._.)", "(=____=)"};

/* Linked list of strings. */

typedef struct StringListNode_
{
    const char *item;
    struct StringListNode_ *next;
    size_t count;
} StringListNode;

typedef StringListNode *StringList;

StringList string_list_empty()
{
    return NULL;
}

size_t string_list_count(StringList list)
{
    return list == NULL ? 0 : list->count;
}

void string_list_prepend(StringList *list, const char *item)
{
    StringListNode *new_node = (StringListNode *)malloc(sizeof(StringListNode));
    new_node->item = item;
    new_node->next = *list;
    new_node->count = string_list_count(*list) + 1;
    *list = new_node;
}

const char **string_list_to_reversed_array(StringList list)
{
    int count = string_list_count(list);
    const char **arr = (const char **)malloc(count * sizeof(const char *));

    StringList current = list;
    StringList next;
    int i = 0;
    while (current != NULL)
    {
        next = current->next;
        arr[count - (i + 1)] = current->item;
        current = next;
        i += 1;
    }

    return arr;
}

void string_list_free(StringList list)
{
    StringList current = list;
    StringList next;
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
}

typedef struct Tester_
{
    /************************/
    /* Global Configuration */
    /************************/

    /* If the filter is not null, only run the test whose name is in the filter. */
    const char *filter;

    /*If the above filter is not null, and the testcase_filter is not -1, skip all testcases but the one in the filter */
    int testcase_filter;
    /*Tracks testcases within one exercise. Reset when a new exercise begins.*/
    int current_testcase_number;

    /*If a filter is set, this is initialised as false(otherwise true) and turns true if a match is found */
    bool filter_match;
    /*If a testcase filter is set, this is initialised as false(otherwise true) and turns true if a match is found */
    bool testcase_filter_match;
    /*Whether the wrap-up function returns a HORUS-compliant number or the number of failed tests */
    bool horus_interface;

    /* The command by which to compile and execute the test suite. */
    const char *command;

    /*********************************************/
    /* Information on the currently running test */
    /*********************************************/

    /* Borrowed reference to the test name (or null if there is none). */
    const char *current_exercise_name;
    /* Owned string description of this test. */
    const char *current_exercise_description;
    /* Should the exercise be skipped? */
    bool should_skip_exercise;
    /* Should the testcase be skipped? */
    bool should_skip_testcase;
    /* Has the test been successful so far? */
    bool successful;
    /* How many tests have been run before this one? */
    int current_exercise_number;

    /*******************************************************************/
    /* Statistics on all tests that have run so far (in reverse order) */
    /*******************************************************************/

    /* Owned list of borrowed references to the names of successful tests. */
    StringList successes;
    /* Owned list of borrowed references to the names of failed tests. */
    StringList failures;
} Tester;

Tester tester_new(size_t filter_dimension, const char *filter, const char *testcase_filter_string, const char *command)
{
    /* Sets the filter_match variables according to if filters are in effect or not. If no filters are present
     * it  sets both to 'true', if it filters for an exercise it only sets the testcase_filter_match 'true'
     */
    bool filter_setting = false;
    bool testcase_filter_setting = false;
    if(filter_dimension == 0)
    {
        filter = NULL;
        filter_setting = true;
    }
    if(filter_dimension <= 1)
    {
        testcase_filter_string = NULL;
        testcase_filter_setting = true;
    }

    int temp_filter = -1;
    if(testcase_filter_string != NULL)
     {
        temp_filter = atoi(testcase_filter_string);
    }
    bool interface = false;
    if(temp_filter == -100){
        temp_filter = -1;
        interface = true;
    }

    Tester t = {
        filter,
        .testcase_filter = temp_filter,
        .current_testcase_number = -1,
        .filter_match = filter_setting,
        .testcase_filter_match = testcase_filter_setting,
        .horus_interface = interface,
        command,
        .current_exercise_name = "",
        .current_exercise_description = NULL,
        .current_exercise_number = 0,
        .successful = true,
        .should_skip_exercise = true,
        .should_skip_testcase = true,
        .successes = NULL,
        .failures = NULL,
    };
    return t;
}

void cleanup_previous_exercise(Tester *t)
{
    t->current_testcase_number = 0;
    if (strlen(t->current_exercise_name) != 0)
    {
        t->current_exercise_number += 1;


        if (t->filter_match && t->testcase_filter_match && t->successful)
        {
            string_list_prepend(&t->successes, t->current_exercise_name);
            printf(TESTRUNNER_LABEL ANSI_COLOR_GREEN "Erfolg %s" ANSI_COLOR_RESET "\n\n", happy_faces[t->current_exercise_number % NUM_HAPPY_FACES]);
        }
    }
}

bool begin_exercise(Tester *t, const char *name, const char *description)
{
    if (t->filter == NULL || strcmp(t->filter,name) == 0)
    {
        cleanup_previous_exercise(t);
        t->should_skip_exercise = false;
        t->filter_match = true;
        printf("\n" TESTRUNNER_LABEL "Starte Test " ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET, name);
        if(t->testcase_filter != -1)
        {
            printf(" in Testfall " ANSI_COLOR_YELLOW "%d" ANSI_COLOR_RESET "\n", t->testcase_filter);
        }
        else
        {
            printf("\n");
        }
        t->current_exercise_name = name;
        t->current_exercise_description = description;
        t->successful = true;
        return true;
    }
    else
    {
        t->should_skip_exercise = true;
        return false;
    }
}

bool begin_testcase(Tester *t)
{
    t->current_testcase_number++;
    if(t->should_skip_exercise == false &&
       (t->testcase_filter == -1 || t->testcase_filter == t->current_testcase_number))
    {
        t->should_skip_testcase = false;
        t->testcase_filter_match = true;
        return true;
    }
    else
    {
        t->should_skip_testcase = true;
        return false;
    }
}

void handle_assertion_failure(Tester *t, const char *expected, const char *got, const char *context)
{
    if (!t->should_skip_exercise && !t->should_skip_testcase && t->successful)
    {
        string_list_prepend(&t->failures, t->current_exercise_name);
        t->should_skip_exercise = true;
        t->successful = false;

        printf( TESTRUNNER_LABEL ANSI_COLOR_CYAN "Baustelle %s" ANSI_COLOR_RESET "\n\n", working_faces[t->current_exercise_number % NUM_WORKING_FACES]);

        if (t->current_exercise_description != NULL)
        {
            printf(TESTRUNNER_LABEL "%s\n", t->current_exercise_description);
        }
        if (context != NULL)
        {
            printf(TESTRUNNER_LABEL "%s\n", context);
        }
        if (expected != NULL)
        {
            printf(TESTRUNNER_LABEL "Erwartet: %s\n", expected);
        }
        if (got != NULL)
        {
            printf(TESTRUNNER_LABEL "Erhielt:  %s\n\n", got);
        }

        if (t->filter == NULL)
        {
            printf("\n" TESTRUNNER_LABEL "Um außschließlich den Test " ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET " zu wiederholen:\n  " ANSI_COLOR_YELLOW "%s %s\n\n" ANSI_COLOR_RESET, t->current_exercise_name, t->command, t->current_exercise_name);
        }
        else if(t->testcase_filter == -1)
        {
            printf("\n" TESTRUNNER_LABEL "Um außschließlich den Testfall " ANSI_COLOR_YELLOW "%d" ANSI_COLOR_RESET " zu wiederholen:\n  " ANSI_COLOR_YELLOW "%s %s %d\n\n" ANSI_COLOR_RESET, t->current_testcase_number, t->command, t->current_exercise_name, t->current_testcase_number);
        }
    }
}

int wrap_up(Tester *t)
{
    cleanup_previous_exercise(t);

    size_t success_count = string_list_count(t->successes);
    size_t failure_count = string_list_count(t->failures);

    if(t->horus_interface){
        if(failure_count > 0){
            return 0;
        } else {
            return 100;
        }
    }

    if (t->filter == NULL)
    {
        printf("\n=============================================\n\n");

        if (success_count == t->current_exercise_number)
        {
            printf(TESTRUNNER_LABEL "Alle Tests bestanden!\n");
            printf(ANSI_COLOR_GREEN);
            for (int i = 0; i < NUM_HAPPY_FACES; i++)
            {
                printf("%s  ", happy_faces[i]);
            }
            printf(ANSI_COLOR_RESET "\n");
        }
        else
        {
            if (success_count > 0)
            {
                printf(TESTRUNNER_LABEL ANSI_COLOR_GREEN "Erfolge: " ANSI_COLOR_RESET "%zd/%zd\n", success_count, success_count + failure_count);
            }
            if (failure_count > 0)
            {
                printf(TESTRUNNER_LABEL ANSI_COLOR_CYAN "Baustellen: " ANSI_COLOR_RESET "%zd/%zd\n", failure_count, success_count + failure_count);

                const char **failures = string_list_to_reversed_array(t->failures);
                for (int i = 0; i < failure_count; i++)
                {
                    printf(TESTRUNNER_LABEL  "- %s\n", failures[i]);
                }
                free(failures);
            }
        }
    }
    else if(!t->filter_match)
    {
        printf("\n" TESTRUNNER_LABEL "Wir konnten keinen Test mit dem Namen " ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET " finden. Kein Test ausgeführt!", t->filter);
        printf(ANSI_COLOR_CYAN "%s" ANSI_COLOR_RESET "\n\n", working_faces[3]);
    }
    else if(!t->testcase_filter_match)
    {
        printf("\n" TESTRUNNER_LABEL "Wir konnten keinen Testfall mit der Nummer " ANSI_COLOR_YELLOW "%d" ANSI_COLOR_RESET " finden. Kein Test ausgeführt!",t->testcase_filter );
        printf(ANSI_COLOR_CYAN "%s" ANSI_COLOR_RESET "\n\n", working_faces[3]);
    }

    string_list_free(t->successes);
    string_list_free(t->failures);

    return failure_count;
}

const char *format_char(char x)
{
    int size = snprintf("", 0, "%u", x);
    char *r = (char *)malloc(size + 1);
    snprintf(r, size + 1, "%u", x);
    return r;
}

void assert_char(Tester *t, char expected, char got, const char *context)
{
    if (expected != got)
    {
        const char *s_expected = format_char(expected);
        const char *s_got = format_char(got);
        handle_assertion_failure(t, s_expected, s_got, context);
        free((char *)s_expected);
        free((char *)s_got);
    }
}

const char *format_uint(unsigned int x) {
    int size = snprintf("", 0, "%u", x);
    char* r = (char*) malloc(size + 1);
    snprintf(r, size + 1, "%u", x);
    return r;
}

void assert_uint(Tester *t, unsigned int expected, unsigned int got, const char *context) {
    if (expected != got) {
        const char* s_expected = format_uint(expected);
        const char* s_got = format_uint(got);
        handle_assertion_failure(t, s_expected, s_got, context);
        free((char*) s_expected);
        free((char*) s_got);
    }
}

const char *format_int(int x) {
    int size = snprintf("", 0, "%d", x);
    char* r = (char*) malloc(size + 1);
    snprintf(r, size + 1, "%d", x);
    return r;
}

const char *format_int32(int32_t x) {
    int size = snprintf("", 0, "%d", x);
    char* r = (char*) malloc(size + 1);
    snprintf(r, size + 1, "%d", x);
    return r;
}

void assert_int(Tester *t, int expected, int got, const char *context) {
    if (expected != got) {
        const char* s_expected = format_int(expected);
        const char* s_got = format_int(got);
        handle_assertion_failure(t, s_expected, s_got, context);
        free((char*) s_expected);
        free((char*) s_got);
    }
}

const char *format_float(float x) {
    int size = snprintf("", 0, "%f", x);
    char* r = (char*) malloc(size + 1);
    snprintf(r, size + 1, "%f", x);
    return r;
}

void assert_float(Tester *t, float expected, float got, const char *context) {
    if ((fabsf(expected - got) >= 0.0001)) {
        const char* s_expected = format_float(expected);
        const char* s_got = format_float(got);
        handle_assertion_failure(t, s_expected, s_got, context);
        free((char*) s_expected);
        free((char*) s_got);
    }
}

void assert_canvas(Tester *t, Canvas_ *expected, Canvas_ *got, const char *context)
{
    int name_size = 9 /*feedback_*/ + strlen(t->current_exercise_name) + 1 /*null byte*/;
    char *name = (char *)malloc(name_size);
    snprintf(name, name_size + 1, "feedback_%s", t->current_exercise_name);

    if (got->supplied_invalid_coordinates) {
        const char *rendered_x = format_int32(got->first_invalid_x);
        const char *rendered_y = format_int32(got->first_invalid_y);

        int actual_context_size = (context ? strlen(context) : strlen("\n\n")) + strlen("\n\n" TESTRUNNER_LABEL "Ungültige Koordinate genutzt: (, )") + strlen(ANSI_COLOR_CYAN) + strlen(rendered_x)  + strlen(rendered_x) + strlen(ANSI_COLOR_RESET) + strlen("\n") + 1 /*null byte*/;
        char *actual_context = (char *)malloc(actual_context_size);
        snprintf(actual_context, actual_context_size + 1, "%s \n" TESTRUNNER_LABEL "Ungültige Koordinate genutzt: %s(%s, %s)%s\n", (context ? context : "\n\n"), ANSI_COLOR_CYAN, rendered_x, rendered_y, ANSI_COLOR_RESET);

        free((void *) rendered_x);
        free((void *) rendered_y);

        handle_assertion_failure(t, NULL, NULL, actual_context);
    } else if (canvas_eq(got, expected) != 1) {
        int actual_context_size = (context ? strlen(context) : strlen("\n\n")) + strlen("\n\n" TESTRUNNER_LABEL "Nichtübereinstimmende Bilder. Visuelles Feedback: ") + strlen(ANSI_COLOR_CYAN) + strlen(name) + strlen(".png") + strlen(ANSI_COLOR_RESET) + strlen("\n") + 1 /*null byte*/;
        char *actual_context = (char *)malloc(actual_context_size);
        snprintf(actual_context, actual_context_size + 1, "%s \n" TESTRUNNER_LABEL "Nichtübereinstimmende Bilder. Visuelles Feedback: %s%s.png%s\n", (context ? context : "\n\n"), ANSI_COLOR_CYAN, name, ANSI_COLOR_RESET);

        handle_assertion_failure(t, NULL, NULL, actual_context);
        canvas_feedback(got, expected, name);
        free(actual_context);
    } else {
        int filename_size = strlen("Feedback/") + name_size + 4 /* .png */ + 1 /*null byte*/;
        char* filename = (char *)malloc(filename_size);
        snprintf(filename, filename_size, "Feedback/%s.png", name);
        remove(filename);
        free(filename);
        //creates a picture of the successful testcase in a Subfolder
        const char* case_number = format_int(t->current_testcase_number);
        int temp_len = strlen(got->name) + strlen(case_number);
        char* temp_name = malloc(temp_len);
        snprintf(temp_name,temp_len,"%s%s", got->name, case_number);
        free(got->name);
        got->name = temp_name;
        canvas_save_folder(got, "Success");
        free((char*)case_number);

    }
    free(name);
}
/*
 * Since we are not using function pointers, comparison of the struct is handled in the test-sheet, and the result is passed
 * on to the assert as 'got'. Expected is always 1, and if got is also 1 they match. 'Context' is also provided by a
 * function on the test-sheet.
 */
void assert_struct(Tester *t, int got, const char *context){
    int expected = 1;
    if (expected != got) {
        handle_assertion_failure(t, NULL, NULL, context);
    }
}

const char *format_bool(bool a) {
    char* r = (char*) mallocx(6);
    if(a){
        snprintf(r, 5, "true");
    } else {
        snprintf(r, 6, "false");
    }
    return r;
}

void assert_bool(Tester *t, bool expected, bool got, const char *context){
    if (expected != got) {
        const char* s_expected = format_bool(expected);
        const char* s_got = format_bool(got);
        handle_assertion_failure(t, s_expected, s_got, context);
        free((char*) s_expected);
        free((char*) s_got);
    }
}

const char *format_pointer(void* p) {
    int size = snprintf("", 0, "%p", p);
    char* r = (char*) mallocx(size + 1);
    snprintf(r, size + 1, "%p", p);
    return r;
}

void assert_pointer(Tester *t, void* expected, void* got, const char *context){
    if (expected != got) {
        const char* s_expected = format_pointer(expected);
        const char* s_got = format_pointer(got);
        handle_assertion_failure(t, s_expected, s_got, context);
        free((char*) s_expected);
        free((char*) s_got);
    }
}

const char *format_uint16_array(uint16_t* arr, size_t arr_len) {
    size_t sum_of_digits = 0;
    for(int i = 0; i < arr_len; i++){
        size_t size = snprintf("", 0, "%d", arr[i]);
        sum_of_digits += size;
    }

    size_t string_len = sum_of_digits + arr_len-1 /*number of commas*/ + 2 /*curly braces*/ + 1;
    char* array_string = mallocx(string_len);
    snprintf(array_string, 2, "{");
    for(int i = 0; i < arr_len; i++){
        char* substring = mallocx(64);
        snprintf(substring, 65, "%d,", arr[i]);
        if(i == arr_len-1){
            snprintf(substring, 65, "%d", arr[i]);
        }
        strcat(array_string, substring);
        free(substring);
    }
    strcat(array_string, "}");
    return array_string;
}

bool uint16_array_equality(uint16_t* expected, uint16_t* got, size_t array_length){
    for(int i = 0; i < array_length; i++){
        if(expected[i] != got[i]){
            return false;
        }
    }
    return true;
}

void assert_uint16_array(Tester *t, uint16_t* expected, uint16_t* got, size_t array_length, const char *context){
    if (!uint16_array_equality(expected, got, array_length)) {
        const char* s_expected = format_uint16_array(expected, array_length);
        const char* s_got = format_uint16_array(got, array_length);
        handle_assertion_failure(t, s_expected, s_got, context);
        free((char*) s_expected);
        free((char*) s_got);
    }
}

const char *format_float_array(float* arr, size_t arr_len) {
    size_t sum_of_symbols = 0;
    for(int i = 0; i < arr_len; i++){
        size_t size = snprintf("", 0, "%.4f", arr[i]);
        sum_of_symbols += size;
    }

    size_t string_len = sum_of_symbols + arr_len-1 /*number of commas*/ + 2 /*curly braces*/ + 1;
    char* array_string = mallocx(string_len);
    snprintf(array_string, 2, "{");
    for(int i = 0; i < arr_len; i++){
        char* substring = mallocx(64);
        snprintf(substring, 65, "%.4f,", arr[i]);
        if(i == arr_len-1){
            snprintf(substring, 65, "%.4f", arr[i]);
        }
        strcat(array_string, substring);
        free(substring);
    }
    strcat(array_string, "}");
    return array_string;
}

bool float_array_equality(float* expected, float* got, size_t array_length){
    for(int i = 0; i < array_length; i++){
        if(expected[i] != got[i]){
            return false;
        }
    }
    return true;
}

void assert_float_array(Tester *t, float* expected, float* got, size_t array_length, const char *context){
    if (!float_array_equality(expected, got, array_length)) {
        const char* s_expected = format_float_array(expected, array_length);
        const char* s_got = format_float_array(got, array_length);
        handle_assertion_failure(t, s_expected, s_got, context);
        free((char*) s_expected);
        free((char*) s_got);
    }
}

///////////////////////
//// Example Usage ////
///////////////////////

// /* Example functions to be tested. */

// char twice(char x) {
//     return 2 * x;
// }

// char add(char a, char b) {
//     return a + (2 * b);
// }

// /* What writing the tests would look like. */

// int main(int argc, char const *argv[])
// {
//    Tester tester = tester_new(argc -1, argv[1], argv[2],"cc -std=c11 -g -Wall <<XY>ex_test.c> -o <<XY>ex_test.o> -lm && ./<<XY>ex_test.o>" );

//     /* Exercise 1 */

//    if(begin_exercise(&tester, "double", "Exercise 1: twice returns double its argument.")){
//        if(begin_testcase(&tester)){
//            assert_uint(&tester, 0, twice(0), "x = 0");
//        }
//        if(begin_testcase(&tester)){
//            assert_uint(&tester, 34, twice(17), "x = 17");
//        }
//    }

//     /* Exercise 2*/

//    if(begin_exercise(&tester, "add", "Exercise 2: add returns the sum of its arguments.")){
//        if(begin_testcase(&tester)){
//            assert_uint(&tester, 5, add(5, 0), "a = 5, b = 0");
//        }
//        if(begin_testcase(&tester)){
//            assert_uint(&tester, 5, add(2, 3), "a = 2, b = 3");
//        }
//        if(begin_testcase(&tester)){
//            assert_uint(&tester, 5, add(0, 5), "a = 0, b = 5");
//        }
//    }

//    return wrap_up(&tester);
// }
