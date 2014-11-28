#ifndef H_H
#define	H_H

#include "Item.h"

#define W 4

class H {
public:
    int i;
    int d;
    double t;          // [0...w-1]
    double*v ;
            
    void createHamming(int i);
    void createEuclidean(double t, double* v, int d);
    void createMatrix();
        
    int calculate(Item* item);
};

#endif	/* H_H */

