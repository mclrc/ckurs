#ifndef CANVAS_H
#define CANVAS_H

struct Canvas_;
typedef struct Canvas_ *Canvas;

/*
 * Gibt die Breite der Canvas zurück.
 */
int canvas_width(Canvas aCanvas);

/*
 * Gibt die Höhe der Canvas zurück.
 */
int canvas_height(Canvas aCanvas);

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
 * Speichert die Canvas c im momentanen Zustand in einem Debug-Unterordner. Die einzelnen Bilder sind nummeriert und die
 * Nummer steigt um 1 jedes mal wenn canvas_save_debug aufgerufen wird.
 */
void canvas_save_debug (Canvas c);

#endif
