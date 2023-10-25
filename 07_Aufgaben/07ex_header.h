#include <sys/types.h>
#include <math.h>
#include <stdint.h>

/*
Lese 'x', berechne dessen *fizzledipp, und schreibe das Resultat nach 'x'.
*/
void fizzledipp(int32_t *x){
    int64_t t = *x/45;
    t = ((t * 445) + 1909)/57;
    t *= t;
    double_t y = sqrt(sqrt(t)) * 3.3334;
    *x = y;
}

/*
Lese 'x' und 'y', berechne ihren *flabble*, und gebe das Resultat zurück.
*/
int32_t flabble(int32_t *x, int32_t *y){
    int64_t t1 = (*x) * (*y);
    t1 = sqrt(t1 * t1);
    double_t t2 = sin((double)(*y) / (double)(*x));
    t1 = (pow(t1, pow(t2,2))) + 14;
    return t1 * t2;
}

/*
Lese 'y', berechne den *frumple* von 'x' und '*y', und schreibe das Resultat nach 'z'.
*/
void frumple(int32_t x, int32_t *y, int32_t *z){
    float_t y2 = *y;
    for(int i = 0; i < *y; i++){
        y2 = atan(y2) + 27;
    }
    x = ((400 * x) / (cos(x) + 34)) + 15 * (x+1);
    int32_t z2 = 0;
    while((z2 < 144) && (z2 > -144)){
        z2 += x * y2;
    }
    *z = z2;
}
