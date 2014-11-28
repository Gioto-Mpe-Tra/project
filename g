#include "G.h"
#include "H.h"
#include "myheader.h"

#include <cstdio>
#include <cstdlib>
#include <cmath>

void G::createHamming(int k, int d) { // function which create g hash function for Hamming space
    int found;

    h_table = new H[k];
    this->k = k;
    for (int i = 0; i < k; i++) {
        h_table[i].createHamming(rand() % d);

        found = 1;
        while (found == 1 && i > 0) {
            for (int u = 0; u < i; u++) {
                if (h_table[i].i == h_table[u].i) {
                    u = 0;
                    found = 1;
                    h_table[i].createHamming(rand() % d);
                } else {
                    found = 0;
                }
            }
        }
    }
    sort();
}

void G::createEuclidean(int k, int d) { // function which create g hash function for Euclidean space
    h_table = new H[k];
    int i, j;
    this->k = k;
    double x1, x2, S, y1, y2;

    r = new int[d];
    for (int j = 0; j < d; j++) {
        r[j] = rand() % 1000;
    }

    for (int i = 0; i < k; i++) {
        double t = rand() / ((double) RAND_MAX) * W;

        double* v = new double[d];
        for (int j = 0; j < d; j++) {

            do {
                x1 = 2.0 * rand() - 1.0;
                x2 = 2.0 * rand() - 1.0;
                S = x1 * x1 + x2 * x2;
            } while (S >= 1.0);

            S = sqrt((-2.0 * log(S)) / S);
            v[j] = x1 * S;
        }

        h_table[i].createEuclidean(t, v, d);
    }
}

void G::destroy() { // function which destroy g hash function
    if (h_table != 0) {
        delete h_table;
    }
}

void G::sort() { // function which sort h function
    H temp; //δεδομένα Ν,Α
    int u, j;

    for (u = 0; u < k; u++) {
        for (j = k - 1; j > u; j--) {
            if (h_table[j - 1].i > h_table[j].i) {
                temp = h_table[j - 1];
                h_table[j - 1] = h_table[j];
                h_table[j] = temp;
            }
        }
    }
}

int G::calculate(Item* item) { // function which calculate g hash function
    int value = 0;

    switch (item->type) {
        case HAMMING_SPACE:
            for (int i = 0; i < k; i++) {
                value += h_table[i].calculate(item) * pow(2, i);
            }
            break;
        case EUCLIDEAN_SPACE:
            for (int i = 0; i < k; i++) {
                value += h_table[i].calculate(item) * r[i];
            }
            break;
        case MATRIX_SPACE:
            break;
    }

    return value;
}
