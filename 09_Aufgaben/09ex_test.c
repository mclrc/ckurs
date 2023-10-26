#include "09ex.c"
#include "testrunner.c"

#define TEST_NAME "09ex_test"
#define RELATIVE_DIRECTORY_PATH "Testdata/" TEST_NAME "data/"

#define TESTS_1AB 42
#define TESTS_2AC 5
#define TESTS_2B 13
#define TESTS_3 4

typedef struct Test1ab
{
    uint32_t input;
    uint32_t expected;
} exercises_1ab_data;

typedef struct Test2ac
{
    Layer* pancake_creation_array;
    size_t array_length;
} exercises_2ac_data;

typedef struct Test3
{
    uint16_t* expected_array;
    size_t array_length;
} exercise_3_data;


static exercises_1ab_data exercises_1ab [TESTS_1AB] = {
        {.input = 10, .expected = 10}, {.input = 1, .expected = 1}, {.input = 0, .expected = 0},
        {.input = 3, .expected = 3}, {.input = 6, .expected = 6}, {.input = 9, .expected = 9},
        {.input = 25, .expected = 25}, {.input = 50, .expected = 50}, {.input = 100, .expected = 100},
        {.input = 11, .expected = 11}, {.input = 17, .expected = 17}, {.input = 23, .expected = 23},
        {.input = 64, .expected = 64}, {.input = 128, .expected = 128}, {.input = 256, .expected = 256},
        {.input = 2222, .expected = 2222}, {.input = 3333, .expected = 3333}, {.input = 7777, .expected = 7777},
        {.input = 2, .expected = 2}, {.input = 5, .expected = 5}, {.input = 7, .expected = 7},
        {.input = 456, .expected = 456}, {.input = 123, .expected = 123}, {.input = 789, .expected = 789},
        {.input = 54, .expected = 54}, {.input = 13, .expected = 13}, {.input = 96, .expected = 96},
        {.input = 131, .expected = 131}, {.input = 545, .expected = 545}, {.input = 969, .expected = 969},
        {.input = 80, .expected = 80}, {.input = 40, .expected = 40}, {.input = 20, .expected = 20},
        {.input = 1010110, .expected = 1010110}, {.input = 10110101, .expected = 10110101}, {.input = 11101, .expected = 11101},
        {.input = 97, .expected = 97}, {.input = 65, .expected = 65}, {.input = 52, .expected = 52},
        {.input = 9001, .expected = 9001}, {.input = 1337, .expected = 1337}, {.input = 42, .expected = 42},
};

static Layer exercise2ac_pancake_creation1 [3] = {ActualPancake,ActualPancake,ActualPancake,};
static Layer exercise2ac_pancake_creation2 [11] = {Fruit,Fruit,Fruit,Cream,Cream,Fruit,Cream,Cream,Fruit,Fruit,Fruit,};
static Layer exercise2ac_pancake_creation3 [8] = {ActualPancake,Fruit,Cream,Fruit,ActualPancake,Fruit,Cream,ActualPancake};
static Layer exercise2ac_pancake_creation4 [2] = {Fruit,Cream,};
static Layer exercise2ac_pancake_creation5 [1] = {ActualPancake,};

static exercises_2ac_data exercises_2ac [TESTS_2AC] = {
        {.pancake_creation_array = exercise2ac_pancake_creation1, .array_length = 3},
        {.pancake_creation_array = exercise2ac_pancake_creation2, .array_length = 11},
        {.pancake_creation_array = exercise2ac_pancake_creation3, .array_length = 8},
        {.pancake_creation_array = exercise2ac_pancake_creation4, .array_length = 2},
        {.pancake_creation_array = exercise2ac_pancake_creation5, .array_length = 1},
};

static uint32_t exercise_2b [TESTS_2B] = {1,2,5,10,7,8,13,42,9,25,8,16,64,};

static uint16_t exercise3_expected1 [3] = {1,4,9};
static uint16_t exercise3_expected2 [8] = {1,4,9,16,25,36,49,64};
static uint16_t exercise3_expected3 [13] = {1,4,9,16,25,36,49,64,81,100,121,144,169};
static uint16_t exercise3_expected4 [21] = {1,4,9,16,25,36,49,64,81,100,121,144,169,196,225,256,289,324,361,400,441};

static exercise_3_data exercise_3 [TESTS_3] = {
        {.array_length = 3, .expected_array = exercise3_expected1},
        {.array_length = 8, .expected_array = exercise3_expected2},
        {.array_length = 13, .expected_array = exercise3_expected3},
        {.array_length = 21, .expected_array = exercise3_expected4},
};

uint32_t count_layers (PileOfPancakes* output){
    uint32_t counter = 0;

    PileOfPancakes* current = output;
    while(current != NULL){
        counter++;
        current = current->further_layers;
    }
    return counter;
}
PileOfPancakes* create_pile_from_array (Layer* layer_array, size_t layers){
    PileOfPancakes* first;
    PileOfPancakes* current;
    for(int i = 0; i < layers; i++){
        PileOfPancakes* next = mallocx(sizeof(PileOfPancakes));
        next->layer = layer_array[i];
        if(i == 0){
            first = next;
            current = first;
        } else {
            current->further_layers = next;
            current = next;
        }
    }
    current->further_layers = NULL;
    return first;
}

char* render_exercises_2ac(exercises_2ac_data testcase)
{
    const char *layer_count = format_int(testcase.array_length);

    char* full_input_string = calloc(125, testcase.array_length * sizeof(char));
    size_t counter = 1;
    for(int i = 0; i < testcase.array_length; i++){
        char* temp_string = calloc(60, sizeof(char));

        if(testcase.pancake_creation_array[i] == Cream){
            snprintf(temp_string,60,TESTRUNNER_LABEL " %lu.\t\t ~~@     Cream      @~~\n", counter);
        }
        if(testcase.pancake_creation_array[i] == Fruit){
            snprintf(temp_string,60,TESTRUNNER_LABEL " %lu.\t\t •¤0     Fruit      0¤•\n", counter);
        }
        if(testcase.pancake_creation_array[i] == ActualPancake){
            snprintf(temp_string,60,TESTRUNNER_LABEL " %lu.\t\t === Actual Pancake ===\n", counter);
        }
        counter++;

        strncat(full_input_string,temp_string,strlen(temp_string));
        free(temp_string);
    }
    char* plate = TESTRUNNER_LABEL "   \t        ¯¯--------------------¯¯\n";

    size_t len = strlen("Wir testen mit folgendem Pancake-Pile aus ") + strlen(layer_count) + strlen(" Lagen:\n\n")
                 + strlen(full_input_string) + strlen(plate) + 1;
    char *str = mallocx(len);
    snprintf(str, len, "Wir testen mit folgendem Pancake-Pile aus %s Lagen:\n\n%s%s",
             layer_count, full_input_string,plate);
    free((char*) layer_count);
    free(full_input_string);
    return str;

}

int main(int argc, char const *argv[]) {
    Tester tester = tester_new(argc - 1, argv[1], argv[2],
                               "cc -std=c11 -g -Wall "TEST_NAME".c -o "TEST_NAME".o -lm && ./"TEST_NAME".o");

    /* Aufgabe 1a */
    if(begin_exercise(&tester,"return_pointer","Aufgabe 1a: Einen Pointer auf den gleichen Wert zurückgeben."))
    {
        for (int i = 0; i < TESTS_1AB; i++)
        {
            if(begin_testcase(&tester))
            {
                uint32_t* output = return_pointer(exercises_1ab[i].input);
                if(output == NULL){
                    assert_bool(&tester, true, false, "Der NULL-Platzhalter muss noch in der Rückgabe ersetzt werden :).");
                } else {
                    assert_uint(&tester, exercises_1ab[i].expected, *(output), "");
                    free(output);
                }
            }
        }
    }
    /* Aufgabe 1b */
    if(begin_exercise(&tester,"free_pointer","Aufgabe 1b: Einen Pointer freigeben und dessen Wert zurückgeben."))
    {
        for (int i = 0; i < TESTS_1AB; i++)
        {
            if(begin_testcase(&tester))
            {
                uint32_t* input = mallocx(sizeof(uint32_t));
                *input = exercises_1ab[i].input;
                assert_uint(&tester, exercises_1ab[i].expected, free_pointer(input), "");
            }
        }
    }
    /* Aufgabe 2a */
    if(begin_exercise(&tester,"free_pancake","Aufgabe 2a: Überprüfen Sie mit Hilfe von valgrind ob Sie alle Elemente "
                                             "freigegeben haben. Wenn valgrind keine Speicher-Leaks mehr anzeigt, setzen "
                                             "Sie den Rückgabewert der Funktion auf 'true'."))
    {
        for (int i = 0; i < TESTS_2AC; i++)
        {
            if(begin_testcase(&tester))
            {
                PileOfPancakes pancakes;
                pancakes.layer = exercises_2ac[i].pancake_creation_array[0];
                pancakes.further_layers = NULL;
                if(exercises_2ac[i].array_length > 1){
                    pancakes.further_layers = create_pile_from_array(&(exercises_2ac[i].pancake_creation_array[1]),
                                                                     exercises_2ac[i].array_length-1);
                }

                char* args = render_exercises_2ac(exercises_2ac[i]);
                assert_bool(&tester, true, free_pancake(pancakes), args);
                free(args);
            }
        }
    }
    /* Aufgabe 2b */
    if(begin_exercise(&tester,"create_pancake","Aufgabe 2b: Einen Pancake-Pile mit n Schichten erstellen."))
    {
        for (int i = 0; i < TESTS_2B; i++)
        {
            if(begin_testcase(&tester))
            {
                PileOfPancakes pancakes = create_pancake(exercise_2b[i]);
                uint32_t output = count_layers(&pancakes);
                assert_uint(&tester, exercise_2b[i], output, "");
                free_pancake(pancakes);
            }
        }
    }
    /* Aufgabe 2c */
    if(begin_exercise(&tester,"free_pancake2","Aufgabe 2c: Überprüfen Sie mit Hilfe von valgrind ob Sie alle Elemente "
                                              "freigegeben haben. Wenn valgrind keine Speicher-Leaks mehr anzeigt, setzen "
                                              "Sie den Rückgabewert der Funktion auf 'true'."))
    {
        for (int i = 0; i < TESTS_2AC; i++)
        {
            if(begin_testcase(&tester))
            {
                PileOfPancakes* pancakes = create_pile_from_array(exercises_2ac[i].pancake_creation_array,
                                                                 exercises_2ac[i].array_length);

                char* args = render_exercises_2ac(exercises_2ac[i]);
                assert_bool(&tester, true, free_pancake2(pancakes), args);
                free(args);
            }

        }
    }
    /* Aufgabe 3 */
    if(begin_exercise(&tester,"create_dynamic_array","Aufgabe 3: Ein dynamisches Array erstellen."))
    {
        for (int i = 0; i < TESTS_3; i++)
        {
            if(begin_testcase(&tester))
            {
                size_t len = exercise_3[i].array_length;
                uint16_t* output = create_dynamic_array(len);
                if(output == NULL){
                    assert_bool(&tester, true, false, "Der NULL-Platzhalter muss noch in der Rückgabe ersetzt werden :).");
                } else {
                    assert_uint16_array(&tester,exercise_3[i].expected_array, output, len, "");
                    free(output);
                }
            }
        }
    }

    return wrap_up(&tester);
}
