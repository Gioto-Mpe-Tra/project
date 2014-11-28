#include "H.h"
#include "myheader.h"

#include <stdlib.h>
#include <iostream>

using namespace std;

// Hamming

void H::createHamming(int i) {
    this->i = i;
}

void H::createEuclidean(double t, double* v, int d) {
    this->t = t;
    this->d = d;
    this->v = new double[d];
    for (int i=0;i<d;i++) {
        this->v[i] = v[i];
    }
}

void H::createMatrix() {
    
}

int H::calculate(Item* item) {
    double temp = 0;
    
    switch(item->type) {
        case HAMMING_SPACE:
            return item->bits[i];            
        case EUCLIDEAN_SPACE:
            for (int i=0;i<d;i++) {
                temp = temp + v[i]*item->values[i];                
            }
            temp = temp + t;
            temp = temp / W;
            return temp;
        case MATRIX_SPACE:
            break;
    }
    cout << "lathos typos !! \n";
    exit(0);
}

