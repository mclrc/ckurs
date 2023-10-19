#ifndef HEXHELPERS_H
#define HEXHELPERS_H

#include "04_canvas.h"

/*
Berechne die Distanz (abgerundet) zwischen dem Punkt `(x0, y0)` und dem Punkt `(x1, y1)`.
*/
int distance(int x0, int y0, int x1, int y1);

/*
Berechne die Quadratwurzel (abgerundet) von `n`.
*/
int squareroot(int n);


// old stuff:
// /*
// Draw a circle on the canvas at the given x and y coordinate with the given diameter.
// */
// Canvas pack_some_circles(Canvas c, int x, int y, int diameter);

// /*
// Compute the horizontal distance between the center points of adjacent circles of the given diameter in the same row.
// */
// int x_distance(int diameter);

// /*
// Compute the vertical distance between the center points of circles of the given diameter in adjacent rows.
// */
// int y_distance(int diameter);

// /*
// Compute how much each row is shifted to the right compared to the preceding row for circles of the given diameter.
// */
// int x_shift(int diameter);

#endif
