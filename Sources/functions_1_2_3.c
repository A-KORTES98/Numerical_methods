//
// Created by anton on 03.10.17.
//
/*#include "../Headers/functions_1_2_3.h"

double func(double x) {return 2 * x * x + 16 / x;}

double df(double x) {return 4 * x - 16 / (x * x);}


double x1Direc = 0;
double x2Direc = 1;
double x1S = 5;
double x2S = 2;

double func(double step) {
    double x1 = x1S + step * x1Direc;
    double x2 = x2S + step * x2Direc;
    return 2 * x1 * x1 * x1 + 4 * x1 * x2 * x2 * x2 - 10 * x1 * x2 + x2 * x2;
}

double df(double step) {
    double x1 = x1S + step * x1Direc;
    double x2 = x2S + step * x2Direc;
    return 6 * x1 * x1 * x1Direc +
           4 * (x1Direc * x2 * x2 * x2 + 3 * x1 * x2Direc * x2 * x2) -
           10 * (x1Direc * x2 + x2Direc * x1) +
           2 * x2Direc * x2;
}

double df_num(double step) {
    return (func(step + 1e-9) - func(step - 1e-9)) / 2e-9;
}*/
