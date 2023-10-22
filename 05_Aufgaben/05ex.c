/*
Willkommen zum fünften Aufgabenblatt vom Programmierkurs. Auf diesem
Aufabenblatt geht es um Rekursion.

Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den
folgenden Befehl aus: cc -std=c11 -g -Wall 05ex_test.c -o 05ex_test.o -lm &&
./05ex_test.o
*/

#include "05_canvas.h"
#include "canvas.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

/*
Aufgabe 1a:
Zeichnen Sie eine horizontale Linie der Länge `width`, deren am weitesten links
liegender Pixel bei `(x, y)` ist.

_Benutzen Sie keine Schleifen - Die Aufgabe soll über Rekursion gelöst werden!_

*/
Canvas recursive_line(Canvas c, int x, int y, int width) {
  int c_width = canvas_width(c);
  int c_height = canvas_height(c);

  if (x >= c_width || y >= c_height || y < 0 || width <= 0) {
    return c;
  }

  if (x >= 0) {
    canvas_set_black(c, x, y);
  }

  return recursive_line(c, x + 1, y, width - 1);
}

/*
Aufgabe 1b:
Zeichnen Sie ein Rechteck mit der Breite `width` und der Höhe `height`. Der
Pixel der linken unteren Ecke liegt bei `(x, y)`.

_Benutzen Sie keine Schleifen, die Aufgabe soll über Rekursion gelöst werden!_
*/
Canvas recursive_rectangle(Canvas c, int x, int y, int width, int height) {
  int c_height = canvas_height(c);

  if (height <= 0) {
    return c;
  }

  if (y >= 0 && y < c_height) {
    recursive_line(c, x, y, width);
  }
  return recursive_rectangle(c, x, y + 1, width, height - 1);
}

/*
Aufgabe 2:
Der *Sierpinski Carpet der Ordnung 0* ist ein einzelnes schwarzes Pixel.
Der *Sierpinski Carpet der Ordnung n+1* besteht aus acht Sierpinski Carpets der
Ordnung n, angeordnet als drei-mal-drei Quadrat dessen Mittelstück fehlt.

Beispiele (`X` stellt schwarze Pixel dar)
=========================================

Ordnung 0:

X

Ordnung 1:

XXX
X X
XXX

Ordnung 2:

XXXXXXXXX
X XX XX X
XXXXXXXXX
XXX   XXX
X X   X X
XXX   XXX
XXXXXXXXX
X XX XX X
XXXXXXXXX

Siehe auch die Datei `05sierpinski.jpg`

Aufgabe 2a:
Um in der nächsten Aufgabe den Sierpinski-Carpet auf die Canvas zeichnen zu
können müssen Potenzen berechnet werden. Implementieren Sie die Berechnung der
Potenz einer nicht-negativen, ganzzahligen Basis `b` mit einem nicht-negativen,
ganzzahligen Exponenten `exp`.

_Benutzen Sie keine Schleifen, die Aufgabe soll über Rekursion gelöst werden!_
*/
int power(int b, int exp) {
  if (exp == 0)
    return 1;
  return b * power(b, exp - 1);
}

/*
Aufgabe 2b:
Diese Funktion soll den Sierpinski Carpet der Ordnung `n` auf die Canvas
zeichnen, mit unterer linker Ecke an Koordinate `(x, y)`.

_Benutzen Sie keine Schleifen, die Aufgabe soll über Rekursion gelöst werden!_
*/
Canvas sierpinski_carpet(Canvas c, int n, int x, int y) {
  if (n == 0) {
    int c_width = canvas_width(c);
    int c_height = canvas_height(c);
    if (x >= 0 && x < c_width && y >= 0 && y < c_height) {
      canvas_set_black(c, x, y);
    }
    return c;
  }

  int width = power(3, n);
  int segment_width = width / 3;

  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) {
      if (i == 1 && j == 1)
        continue;

      sierpinski_carpet(c, n - 1, x + i * segment_width, y + j * segment_width);
    }

  return c;
}

/*
Aufgabe 3:
Implementieren Sie einen Fülleimer. Gegeben eine Koordinate `(x, y)` auf einer
(bereits bemalten) Canvas, soll die komplette zusammenhängende Fläche aller
Pixel der selben Farbe (schwarz oder weiß) schwarz gefärbt werden. Zwei Pixel
sind Teil der selben Fläche wenn sie die selbe Farbe haben und direkt benachbart
sind. Jeder Pixel hat bis zu vier direkte Nachbarn - die Diagonalen zählen
nicht.

Funktionen, um die Farbe eines Pixels auf der Canvas zu bestimmen, sind im
Headerfile der Canvas dokumentiert.
*/
Canvas bucket_fill(Canvas c, int x, int y) {
  int c_width = canvas_width(c);
  int c_height = canvas_height(c);

  if (x >= 0 && x < c_width && y >= 0 && y < c_height) {
    if (pixel_is_black(c, x, y))
      return c;
    canvas_set_black(c, x, y);
  } else {
    return c;
  }

  int neighbors[4][2] = {{x - 1, y}, {x, y - 1}, {x + 1, y}, {x, y + 1}};

  for (int i = 0; i < 4; i++) {
    int neighbor_x = neighbors[i][0];
    int neighbor_y = neighbors[i][1];

    if (neighbor_x < 0 || neighbor_x >= c_width || neighbor_y < 0 ||
        neighbor_y >= c_height)
      continue;

    if (pixel_is_white(c, neighbor_x, neighbor_y)) {
      bucket_fill(c, neighbor_x, neighbor_y);
    }
  }
  return c;
}
