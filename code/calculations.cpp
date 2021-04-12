#include "calculations.h"

double abs_(double a) {
    return a < 0 ? -a : a;
}

double max(double a, double b) {
    return a < b ? b : a;
}

void copyMatrix(double dest[4][4], const double source[4][4]) {
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            dest[i][j] = source[i][j];
        }
    }
}

void staticToDynamic(double **& dest, const double source[4][4]) {
    dest = (double**)malloc(4*sizeof(double*));
    for(int i = 0; i < 4; ++i) {
        dest[i] = (double*)malloc(4*sizeof(double));
    }
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            dest[i][j] = source[i][j];
        }
    }
}

void multMatr(double a[4][4], const double b[4][4]) {
    double res[4][4];

    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            res[i][j] = 0;
            for(int k = 0; k < 4; ++k) {
                res[i][j] += a[i][k]*b[k][j];
            }
        }
    }

    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            a[i][j] = res[i][j];
        }
    }
}

void multVecMatr(double a[4], const double b[4][4]) {
    double res[4];

    for(int j = 0; j < 4; ++j) {
        res[j] = 0;
        for(int k = 0; k < 4; ++k) {
            res[j] += a[k]*b[k][j];
        }
    }

    for(int i = 0; i < 4; ++i)
        a[i] = res[i];
}

