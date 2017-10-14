#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "../Headers/structures.h"
#include "../Headers/functions_1_2_3.h"
#define GOLD_RATIO1 (sqrt(5) - 1)/2
#define GOLD_RATIO2 (3 - sqrt(5))/2
#define START_POINT 2
#define EPS 1E-6
#define DELTA 1E-3
#define MAX_ITER 51


void swap(double*, double*);
double d_4(double, double, double);
interval swan1(double, double);
interval swan2(double, double);
double dichtomy(double, double, int);
double goldenRatioRcrs(double, double, double, bool, int);
double goldenRatio1(double, double);
double goldenRatio2(double, double);
int createFibArr(double, double, double[]);
double fibonacci1(double, double);
double fibonacci2(double, double);
double bolzano(double, double, int);
double linearInterp(double, double, int);
double nextPLinInterp(double, double);
double cubInterp(double, double, int);
double nextPCubInterp(double, double);
double DSK(double, double, int);
interval threePointSearch(double, double, double, int);






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

double d_4(double a, double b, double c){
    return b +
           ((b - a) * (func(a) - func(c))) /
           (2 * (func(a) - 2 * func(b) + func(c)));
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

interval swan2(double startP, double h){
    double prevP;
    double currP;
    if (df(startP) > 0){
        h = -h;
    }
    prevP = startP;
    currP = startP + h;
    while (df(currP) * df(prevP) > 0){
        h *= 2;
        prevP = currP;
        currP += h;
    }
    return createInterv(prevP, currP);
}

double dichtomy(double a, double b, int iter){
    double midP = (a + b) / 2;
    if ((iter == MAX_ITER) || (fabs(b - a) < EPS)){
        return midP;
    }
    double l = midP - DELTA;
    double m = midP + DELTA;
    return func(l) < func(m)
           ? dichtomy(a, m, ++iter)
           : dichtomy(l, b, ++iter);
}

double goldenRatioRcrs(double a, double b, double x, bool isXLess, int iter) {
    double l;
    double m;
    if ((fabs(b - a) < EPS) || (iter == MAX_ITER)){
        return (b + a)/2;
    }
    if (isXLess){
        l = x;
        m = a + GOLD_RATIO1 * (b - a);
    }
    else{
        l = a + GOLD_RATIO2 * (b - a);
        m = x;
    }
    if (func(l) < func(m)){
        b = m;
        x = l;
        isXLess = false;
    }
    else{
        a = l;
        x = m;
        isXLess = true;
    }
    return goldenRatioRcrs(a, b, x, isXLess, ++iter);
}

double goldenRatio1(double a, double b){
    int iter = 0;
    double length = b - a;
    double l = a + GOLD_RATIO2 * length;
    double m = a + GOLD_RATIO1 * length;
    while ((fabs(b - a) > EPS) && (iter != MAX_ITER)){
        if (func(m) > func(l)){
            length = m - a;
            b = m;
            m = l;
            l = a + GOLD_RATIO2 * length;
        }
        else{
            length = b - l;
            a = l;
            l = m;
            m = a + GOLD_RATIO1 * length;
        }
        iter++;
    }
    return (a + b)/2;
}

double goldenRatio2(double a, double b){
    int iter = 0;
    double length = b - a;
    double x1 = a + length * GOLD_RATIO1;
    double x2;
    while ((fabs(b - a) > EPS) && (iter != MAX_ITER)){
        x2 =  b + a - x1;
        if (x1 > x2){
            swap(&x1, &x2);
        }
        if (func(x2) > func(x1)){
            b = x2;
        }
        else
        {
            a = x1;
            x1 = x2;
        }
        iter++;

    }
    return (a + b)/2;
}

int createFibArr(double a, double b, double arr[]){
    double limitNum = (b - a) / EPS;
    arr[0] = 1;
    arr[1] = 2;
    int i = 1;
    while ((arr[i++] < limitNum) && (i < MAX_ITER)){
        arr[i] = arr[i-1] + arr[i-2];
        printf("%f\n", arr[i]);
    }
    arr[i] = arr[i-1] + arr[i-2];
    return i;
}

double fibonacci1(double a, double b){
    double fib[MAX_ITER];
    int iter = createFibArr(a, b, fib);
    double m = a + (b - a) * fib[iter - 1] / fib[iter];
    double l = a + (b - a) * fib[iter - 2] / fib[iter];
    while (--iter >= 0){
        if (func(l) < func(m)){
            b = m;
            m = l;
            l = a + (b - a) * fib[iter - 2] / fib[iter];
        }
        else {
            a = l;
            l = m;
            m = a + (b - a) * fib[iter - 1] / fib[iter];
        }
    }
    m = l + EPS;
    return func(l) > func(m) ? (l + b) / 2 : (a + m) / 2;
}

double fibonacci2(double a, double b){
    double fib[MAX_ITER];
    int iter = createFibArr(a, b, fib);
    double x1 = a + (b - a) * fib[iter - 1] / fib[iter];
    double x2;
    while (--iter >= 0){
        x2 = a + b - x1;
        x1 > x2 ? swap(&x1, &x2) : NULL ;
        if (func(x1) < func(x2)){
            b = x2;
        }
        else {
            a = x1;
            x1 = x2;
        }
    }
    return (a + b) / 2;
}

double bolzano(double a, double b, int iter){
    double midP = (a + b) / 2;
    if (((fabs(b - a) < EPS) && (df(midP) < EPS)) || (iter == MAX_ITER))
        return (a + b) / 2;
    if (df(midP) > 0)
        b = midP;
    else
        a = midP;
    return bolzano(a, b, ++iter);
}

void swap(double *a, double *b){
    double c = *a;
    *a = *b;
    *b = c;
}

double linearInterp(double a, double b, int iter){
    double nextP = nextPLinInterp(a, b);
    double dNextP = df(nextP);
    if ((dNextP < EPS) || (iter == MAX_ITER)){
        return nextP;
    }
    return  dNextP > 0 ? linearInterp(a, nextP, ++iter) : linearInterp(nextP, b, ++iter);
}

double nextPLinInterp(double prevP, double currP){
    return currP - (df(currP) * (currP - prevP)) / (df(currP) - df(prevP));
}

double cubInterp(double a, double b, int iter){
    double g = nextPCubInterp(a, b);
    double x = a + g * (b - a);
    return iter == MAX_ITER ? x :
           g < 0 ? a :
           g < 0 ? a :
           g > 1 ? b :
           df(x) < EPS ? x :
           df(x) > 0 ? cubInterp(a, x, ++iter) : cubInterp(x, b, ++iter);
}

double nextPCubInterp(double prevP, double currP){
    double z = df(prevP) + df(currP) + 3 * ((func(prevP) - func(currP)) / (currP - prevP));
    double w = sqrt(z * z - df(prevP) * df(currP));
    return (z + w - df(prevP)) / (df(currP) - df(prevP) + 2 * w);
}

interval threePointSearch(double a, double mid, double b, int iter){
    if ((fabs(b - a) < EPS) || (iter == 0)){
        return createInterv(a, b);
    }
    double length = b - a;
    double a_mid = a + length / 4;
    double mid_b = b - length / 4;

    if (func(a_mid) < func(mid)){
        b = mid;
        mid = a_mid;
    }else if (func(mid) < func(mid_b)){
        a = a_mid;
        b = mid_b;
    }else{
        a = mid;
        mid = mid_b;
    }

    return threePointSearch(a, mid, b, --iter);
}

double DSK(double x, double h, int iter){
    if ((fabs(df(x)) < EPS) || (iter == 0)){
        return x;
    }
    interval afterSwan = swan2(x, h);
    x = (afterSwan.b + afterSwan.a) / 2;
    double d = d_4(afterSwan.a, x, afterSwan.b);
    return func(d) < func(x)
           ? DSK(d, h / 2, --iter)
           : DSK(x, h / 2, --iter);
}