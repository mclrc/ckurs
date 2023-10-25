/*
Diese Datei enthält eine leicht abgewandelte Version der Canvas API: Die Canvas mit einer Schildkröte.
Die Schildkröte sitzt auf einem einzigen Pixel und kann in eine von vier möglichen Richtungen schauen.
Mithilfe von Funktionen kann sie sich jeweils um 90° drehen oder einen Schritt vorwärts in die Richtung machen in die sie
gerade schaut.
Wenn sie sich bewegt, dann färbt die Schildkröte den Pixel den sie gerade verlassen hat schwarz. Daher können Sie durch
geschicktes steuern der Schildkröte auf die Canvas zeichnen.
*/

#ifndef CANVAS_H
#define CANVAS_H

#include "canvas.h"

typedef struct Canvas_ *Canvas;

typedef enum Orientation_ { North, East, South, West } Orientation;

typedef struct TurtleCanvas_ {
    Canvas canvas;
    uint32_t turtle_x;
    uint32_t turtle_y;
    bool draw_black;
    Orientation orientation;
} TurtleCanvas;

/*
Färbt die derzeitige Position der Schildkröte, und bewegt sich dann einen Pixel nach vorne.
Falls der Schritt die Schildkröte von einer Canvas-Kante bewegen würde, taucht sie auf der gegenüberliegenden
Kante wieder auf.
Beispiel: Am Ende der ersten Zeile bewegt sich die Schildkröte weiter nach rechts. Dadurch taucht sie am Anfang der
ersten Zeile wieder auf, also bei (0,0). Das gilt analog für alle Richtungen.
*/
void turtle_advance(TurtleCanvas *c);
/*
Dreht die Schildkröte um 90° nach links.
*/
void turtle_rotate_left(TurtleCanvas *c);
/*
Dreht die Schildkröte um 90° nach rechts.
*/
void turtle_rotate_right(TurtleCanvas *c);
/*
Bestimmt ob die Schildkröte den Pixel färbt bevor sie ihn verlässt oder nicht.
'True' bedeutet der Pixel wird schwarz gefärbt, 'False' das er unverändert bleibt.
*/
void turtle_toggle_color(TurtleCanvas *c);
/*
Gibt die Breite der Canvas zurück auf der sich die Schildkröte befindet.
*/
size_t turtle_canvas_width(TurtleCanvas *c);
/*
Gibt die Höhe der Canvas zurück auf der sich die Schildkröte befindet.
*/
size_t turtle_canvas_height(TurtleCanvas *c);

/*----------------------------------------Für Aufgabe 1a bis hier lesen-----------------------------------------------*/



/*----------------------------------------Für Aufgabe 1c runterscrollen-----------------------------------------------*/




















void turtle_advance(TurtleCanvas *c){
    if(c->draw_black) {
        canvas_set_black(c->canvas, c->turtle_x, c->turtle_y);
    }
    uint32_t x_new = c->turtle_x;
    uint32_t y_new = c->turtle_y;

    if(c->orientation == North){
        if(y_new == turtle_canvas_height(c)-1){
            y_new = 0;
        } else {
            y_new += 1;
        }
    } else if (c->orientation == East){
        if(x_new == turtle_canvas_width(c)-1){
            x_new = 0;
        } else {
            x_new += 1;
        }
    } else if (c->orientation == South){
        if(y_new == 0){
            y_new = turtle_canvas_height(c)-1;
        } else {
            y_new -= 1;
        }
    } else if (c->orientation == West){
        if(x_new == 0){
            x_new = turtle_canvas_width(c)-1;
        } else {
            x_new -= 1;
        }
    }
    c->turtle_x = x_new;
    c->turtle_y = y_new;
}

void turtle_rotate_left(TurtleCanvas *c){
    if (c->orientation == North){
        c->orientation = West;
    } else if (c->orientation == East){
        c->orientation = North;
    } else if (c->orientation == South){
        c->orientation = East;
    } else if (c->orientation == West){
        c->orientation = South;
    }
}

void turtle_rotate_right(TurtleCanvas *c){
    if (c->orientation == North){
        c->orientation = East;
    } else if (c->orientation == East){
        c->orientation = South;
    } else if (c->orientation == South){
        c->orientation = West;
    } else if (c->orientation == West){
        c->orientation = North;
    }
}

void turtle_toggle_color(TurtleCanvas *c){
    if(c->draw_black){
        c->draw_black = false;
    } else {
        c->draw_black = true;
    }
}

size_t turtle_canvas_width(TurtleCanvas *c){
    return canvas_width(c->canvas);
}

size_t turtle_canvas_height(TurtleCanvas *c){
    return canvas_height(c->canvas);
}

/* * * * * * * * * * * * * * * * *  Ganz schön viel gelernt mittlerweile :)  * * * * * * * * * * * * * * * * * * * * * */

#endif