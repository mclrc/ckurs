/*
Willkommen zum achten Aufgabenblatt vom Programmierkurs. Auf diesem Aufabenblatt
geht es um Pointer und Arrays.

Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den
folgenden Befehl aus: cc -std=c11 -g -Wall 08ex_test.c -o 08ex_test.o -lm &&
./08ex_test.o
*/

#include "turtlecanvas.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/*
Aufgabe 1a:
Lesen Sie das Headerfile `turtlecanvas.h`. Diese Funktion soll die Turtle `d`
Schritte vorwärts machen lassen.
*/
void turtle_advance_by(TurtleCanvas *c, uint32_t d) {
  for (int i = 0; i < d; i++)
    turtle_advance(c);
}

/*
Aufgabe 1b:
Füllen Sie die Turtlecanvas mit horizontalen, abwechselnd schwarzen und weißen
Linien (die unterste Zeile soll schwarz gefärbt werden). Die Turtle ist anfangs
an Position (0, 0), ist nach rechts orientiert, und zeichnet schwarz.
*/
void turtle_stripes(TurtleCanvas *c) {
  int c_width = turtle_canvas_width(c);
  int c_height = turtle_canvas_height(c);

  while (c->turtle_y < c_height) {
    for (; c->turtle_x < c_width - 1; turtle_advance(c)) {
    };
    turtle_rotate_left(c);
    turtle_advance(c);
    turtle_toggle_color(c);
    turtle_rotate_left(c);
    for (; c->turtle_x > 0; turtle_advance(c)) {
    };
    if (c->turtle_y == c_height - 1)
      return;
    turtle_rotate_right(c);
    turtle_advance(c);
    turtle_toggle_color(c);
    turtle_rotate_right(c);
  }
}

/*
Aufgabe 1c:
Lesen Sie die Implementierungen der Turtlecanvas-Funktionen weiter unten in der
"turtlecanvas.h". Der Quellcode sollte vollständig verständlich und
unüberraschend sein. Hinweis: Diese Aufgabe wird nicht bewertet.
*/

/*
Aufgabe 2a:
Geben Sie einen Pointer auf das erste Vorkommen der größten Zahl im Eingabearray
zurück.
*/
uint16_t *find_maximal_number(uint16_t numbers[], size_t numbers_len) {
  uint16_t *cur_max = numbers;
  for (uint16_t *c = numbers + 1; c < numbers + numbers_len; c++)
    if (*c > *cur_max)
      cur_max = c;
  return cur_max;
}

/*
Aufgabe 2b:
Geben Sie (einen Pointer auf) das Teilarray zurück, welches ab dem ersten
Vorkommen der größten Zahl im Eingabearray beginnt.
*/
uint16_t *find_subarray_starting_at_maximal_number(uint16_t numbers[],
                                                   size_t numbers_len) {
  return find_maximal_number(numbers, numbers_len);
}

/*
Aufgabe 2c:
Geben Sie die größtmögliche Distanz zwischen zwei Zahlenwerten aus dem Array
`numbers` zurück. Beispiel: Im Array {1, 3, 7, 4} ist die größte Distanz die
zwischen 1 und 7, und beträgt damit `6`.
*/
uint16_t safe_diff(uint16_t a, uint16_t b) { return a < b ? b - a : a - b; }
uint16_t max(uint16_t a, uint16_t b) { return a > b ? a : b; }
uint16_t min(uint16_t a, uint16_t b) { return a < b ? a : b; }

uint16_t find_maximum_distance(uint16_t numbers[], size_t numbers_len) {
  uint16_t current_max_diff = 0;

  for (int i = 0; i < numbers_len - 1; i++)
    for (int j = i + 1; j < numbers_len; j++) {
      current_max_diff =
          max(current_max_diff, safe_diff(numbers[i], numbers[j]));
    }

  return current_max_diff;
}

/*
Aufgabe 2d:
Geben Sie die kleinstmögliche Distanz zwischen zwei Zahlenwerten aus dem Array
`numbers` zurück. Beispiel: Im Array {1, 3, 7, 4} ist die kleinste Distanz die
zwischen 3 und 4, und beträgt damit `1`.
*/
uint16_t find_minimum_distance(uint16_t numbers[], size_t numbers_len) {
  uint16_t current_min_diff = UINT16_MAX;

  for (int i = 0; i < numbers_len - 1; i++)
    for (int j = i + 1; j < numbers_len; j++) {
      current_min_diff =
          min(current_min_diff, safe_diff(numbers[i], numbers[j]));
    }

  return current_min_diff;
}

/*
Aufgabe 2e:
Schreiben Sie die ersten `numbers_len` Quadratzahlen aufsteigend in das gegebene
Array `numbers`. Hinweis: Wir starten bei `1`. Sollte numbers_len also `5` sein,
sind die ersten 5 Quadratzahlen bis einschließlich die von 5 gemeint: 1, 4, 9,
16, 25.
*/
void square_ascending(uint16_t numbers[], size_t numbers_len) {
  for (int i = 0; i < numbers_len; i++)
    numbers[i] = (i + 1) * (i + 1);
}

/*
Aufgabe 2f:
Füllen Sie das Array `out` mit den aufsteigend sortierten Zahlen aus dem `in`
Array. Beide Arrays haben die Länge `len`. Beispiel: Ist `in` {1, 4, 3, 7, 4},
so soll `out` am Ende {1, 3, 4, 4, 7} sein.
*/

void swap(uint16_t *a, uint16_t *b) {
  uint16_t z = *a;
  *a = *b;
  *b = z;
}

void print_array(uint16_t nums[], size_t nums_len) {
  for (int i = 0; i < nums_len; i++)
    printf("%d,", nums[i]);
  puts("\n");
}

void sort_ascending(uint16_t in[], uint16_t out[], size_t len) {
  for (int i = 0; i < len; i++)
    out[i] = in[i];

  for (int i = 0; i < len; i++) {
    for (int j = 1; j < len - i; j++) {
      if (out[j] < out[j - 1])
        swap(out + j, out + j - 1);
    }
  }
}
