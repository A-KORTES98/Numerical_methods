/*#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "../Headers/structures.h"
#include "../Headers/numerical_meth_1_2.h"
#include "../Headers/functions_1_2_3.h"
#define GOLD_RATIO1 (sqrt(5) - 1)/2
#define GOLD_RATIO2 (3 - sqrt(5))/2
#define START_POINT 2
#define EPS 1E-6
#define DELTA 1E-3
#define MAX_ITER 51



int spaceMain(){
    double h = 0.001;
    interval afterSwan = swan2(0, h);
    for (int i = 0; i < 20; i++){
        afterSwan = swan2((afterSwan.a + afterSwan.b) / 2, h / 2);
    }
    displayResI(afterSwan);
    displayResD(DSK(0, 0.00001, 40));
}


void displayResI(interval interv){
    printf("result interval: [(%f;%f), (%f,%f)]\n",
           x1Direc * interv.a + x1S,
           x2Direc * interv.a + x2S,
           x1Direc * interv.b + x1S,
           x2Direc * interv.b + x2S);
}

void displayResD(double appMin){
    printf("Approximate minimum: (%f;%f)",
           x1Direc * appMin + x1S,
           x2Direc * appMin + x2S);
}
*/







