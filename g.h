#ifndef G_H
#define	G_H

#include "H.h"

class G {
public:
    int k;
    int d;
    H* h_table;
    int* r;
    
    void createHamming(int k, int d);
    void createEuclidean(int k, int d);
    
    void destroy();
    void sort();
    
    int calculate(Item* item);
};

#endif

