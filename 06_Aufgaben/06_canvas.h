#ifndef CANVAS_H
#define CANVAS_H

struct Canvas_;
typedef struct Canvas_ *Canvas;

/*
 * Setzt den Rotanteil eines Pixel an der gegebenen Koordinate.
 * Der Koordinatenursprung (0,0) sitzt in der linken unteren Ecke des Bildes.
 *
 * `r = 1.0` gibt maximalen Rotanteil, `r = 0.0` gibt keinerlei Rotanteil, `r = 0.5` gibt halben Rotanteil, usw.
 * `r` größer als 1.0 wird auf 1.0 normiert und `r` kleiner als 0.0 wird auf 0.0 normiert.
 * Koordinaten außerhalb des Canvas werden ignoriert.
*/
Canvas canvas_set_r(Canvas c, int x, int y, float r);

/*
 * Setzt den Grünanteil eines Pixel an der gegebenen Koordinate.
 * Der Koordinatenursprung (0,0) sitzt in der linken unteren Ecke des Bildes.
 *
 * `g = 1.0` gibt maximalen Grünanteil, `g = 0.0` gibt keinerlei Grünanteil, `r = 0.5` gibt halben Grünanteil, usw.
 * `g` größer als 1.0 wird auf 1.0 normiert und `g` kleiner als 0.0 wird auf 0.0 normiert.
 * Koordinaten außerhalb des Canvas werden ignoriert.
*/
Canvas canvas_set_g(Canvas c, int x, int y, float g);

/*
 * Setzt den Blauanteil eines Pixel an der gegebenen Koordinate, `r = 0.5` gibt halben Blauanteil, usw.
 * Der Koordinatenursprung (0,0) sitzt in der linken unteren Ecke des Bildes.
 *
 * `b = 1.0` gibt maximalen Blauanteil, `b = 0.0` gibt keinerlei Blauanteil.
 * `b` größer als 1.0 wird auf 1.0 normiert und `b` kleiner als 0.0 wird auf 0.0 normiert.
 * Koordinaten außerhalb des Canvas werden ignoriert.
*/
Canvas canvas_set_b(Canvas c, int x, int y, float b);

/*
 * Setzt die Farbe eines Pixel an der gegebenen Koordinate auf schwarz.
 * Der Koordinatenursprung (0,0) sitzt in der linken unteren Ecke des Bildes.
 *
 * Die Parameter müssen innerhalb dieser Grenzen bleiben:
 * 0 <= x < Canvasbreite
 * 0 <= y < Canvashöhe
 */
Canvas canvas_set_black(Canvas c, int x, int y);

/*
 * Setzt die Farbe eines Pixel an der gegebenen Koordinate auf weiß.
 * Der Koordinatenursprung (0,0) sitzt in der linken unteren Ecke des Bildes.
 *
 * Die Parameter müssen innerhalb dieser Grenzen bleiben:
 * 0 <= x < Canvasbreite
 * 0 <= y < Canvashöhe
 */
Canvas canvas_set_white(Canvas c, int x, int y);



/*
 * Ließt den Rotanteil eins Pixels an der gegebenen Koordinate.
 * Der Koordinatenursprung (0,0) sitzt in der linken unteren Ecke des Bildes.
 *
 * `1.0` bedeutet maximaler Rotanteil, `0.0` bedeutet keinerlei Rotanteil.
 * `-1.0` bedeutet Koordinate außerhalb des Canvas, also kein valider Rotanteil.
 *
 */
float canvas_get_r (Canvas c, int x, int y);

/*
 * Ließt den Grünanteil eins Pixels an der gegebenen Koordinate.
 * Der Koordinatenursprung (0,0) sitzt in der linken unteren Ecke des Bildes.
 *
 * `1.0` bedeutet maximaler Grünanteil, `0.0` bedeutet keinerlei Grünanteil.
 * `-1.0` bedeutet Koordinate außerhalb des Canvas, also kein valider Grünanteil.
 *
 */
float canvas_get_g (Canvas c, int x, int y);

/*
 * Ließt den Blauanteil eins Pixels an der gegebenen Koordinate.
 * Der Koordinatenursprung (0,0) sitzt in der linken unteren Ecke des Bildes.
 *
 * `1.0` bedeutet maximaler Blauanteil, `0.0` bedeutet keinerlei Blauanteil.
 * `-1.0` bedeutet Koordinate außerhalb des Canvas, also kein valider Blauanteil.
 *
 */
float canvas_get_b (Canvas c, int x, int y);

/*
 * Gibt `1` zurück, falls der Pixel an der gegebenen Koordinate schwarz ist, ansonsten `0`.
 */
int pixel_is_black(Canvas c, int x, int y);

/*
 * Gibt `1` zurück, falls der Pixel an der gegebenen Koordinate weiß ist, ansonsten `0`.
 */
int pixel_is_white(Canvas c, int x, int y);



/*
 * Gibt die Breite der Canvas zurück.
 */
int canvas_width(Canvas aCanvas);

/*
 * Gibt die Höhe der Canvas zurück.
 */
int canvas_height(Canvas aCanvas);



/*
 * Speichert die Canvas c im momentanen Zustand in einem Debug-Unterordner. Die einzelnen Bilder sind nummeriert und die
 * Nummer steigt um 1 jedes mal wenn canvas_save_debug aufgerufen wird.
 */
void canvas_save_debug(Canvas c);

#endif
