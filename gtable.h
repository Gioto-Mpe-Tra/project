#ifndef GTABLE_H
#define	GTABLE_H

#include "G.h"

class Gtable {
public:
    G* g_table;
    
    void createHamming(int k, int L, int D);
    void createEuclidean(int k, int L, int D);
    
    void destroyHamming();
    void destroyEuclidean();
};

#endif

