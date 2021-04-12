#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include "stdlib.h"
#include "math.h"
#include <QtGlobal>

double abs_(double);
double max(double);
void copyMatrix(double dest[4][4], const double source[4][4]);
void staticToDynamic(double **& dest, const double source[4][4]);
void dynamicToStatic(double dest[4][4], double **&source);
void multMatr(double a[4][4], const double b[4][4]);
void multVecMatr(double a[4], const double b[4][4]);

#endif // CALCULATIONS_H
