#include <math.h>
#include "../Headers/structures.h"
#include <stdio.h>
#include "../Headers/numerical_meth_4.h"
#define MAX_ITER 100
#define EPS 1e-7
#define DELTA 1e-10
#define startX1 1
#define startX2 1


double func(double);
interval createInterv(double, double);
interval swan1(double, double);
double dichtomy(double, double, int);

double x1 = 1;
double x2 = 2;
int argNum = 1;


int mainF(){
    interval afterSwan = swan1(startX1, 0.01);
    argNum++;
    double min1;
    double min2;
    afterSwan = swan1(startX2, 0.01);
    for (int i = 0; i < 10; i++){
        argNum--;
        min1 = dichtomy(afterSwan.a, afterSwan.b, 20);
        argNum++;
        min2 = dichtomy(afterSwan.a, afterSwan.b, 20);
    }
    printf("App min: (%f; %f) \n", min1, min2);
}



double func(double x){
    if (argNum == 1){
        x1 = x;
    } else{
        x2 = x;
    }
    return (x2 - x1) * (x2 - x1) + 100 * (1 - x1) * (1 - x1);
}

interval createInterv(double prevPrevPoint, double currPoint){
    interval interv;
    if (currPoint < prevPrevPoint){
        interv.a = currPoint;
        interv.b = prevPrevPoint;
    }
    else{
        interv.a = prevPrevPoint;
        interv.b = currPoint;
    }
    return interv;
}

interval swan1(double startP, double h){
    double prevP;
    double currP;
    if (func(startP) < func(startP + h)){
        h = -h;
    }
    prevP = startP;
    currP = startP + h;
    while (func(currP) < func(prevP)){
        h *= 2;
        prevP = currP;
        currP += h;
    }
    return createInterv(prevP - h/2, currP);
}

double dichtomy(double a, double b, int iter){
    double midP = (a + b) / 2;
    if ((iter == 0) || (fabs(b - a) < EPS)){
        return midP;
    }
    double l = midP - DELTA;
    double m = midP + DELTA;
    return func(l) < func(m)
           ? dichtomy(a, m, --iter)
           : dichtomy(l, b, --iter);
}


