/*
Diese Datei enthält die Funktionen, die auf dem Aufgabenblatt nach und nach neu implementiert werden sollen.
Theoretisch könnte man die hier also abschreiben. Wer das macht, kriegt aber keine Punkte, falls wir es merken.
Und sonderlich lehrreich wäre das natürlich auch nicht.
*/






























































































/* Spoilers below*/






















#include "04_canvas.h"
#include "04ex_helpers.h"
#include <math.h>
#include <stdio.h>

/*
 Die Implementierung dieser Funktion ist absichtlich undurchsichtig (kein guter Stil) und
 beinhaltet Konzepte die erst später in diesem Kurs behandelt werden.
 Falls Sie demnach diesen Kommentar lesen:
 Sie müssen den untenstehenden Code noch nicht verstehen, und sollten ihn nicht kopieren.
*/
int squareroot(int n){
    if (n < 2) {
        return n;
    }
    int low = squareroot(n >> 2) << 1;
    int high = low + 1;

    if ((high * high) > n){
        return low;
    } else {
        return high;
    }
}
/*
 Die Implementierung dieser Funktion ist absichtlich undurchsichtig (kein guter Stil) und
 beinhaltet Konzepte die erst später in diesem Kurs behandelt werden.
 Falls Sie demnach diesen Kommentar lesen:
 Sie müssen den untenstehenden Code noch nicht verstehen, und sollten ihn nicht kopieren.
*/
int distance(int x0, int y0, int x1, int y1){
    int exp = 2;
    return sqrt(pow(x1 - x0,exp) + pow(y1 - y0,exp));
}


