#ifndef ITEM_H
#define	ITEM_H

class Item {
public:
    char name[200];
    int type;
    int d;
    char* bits;         // hamming
    double* values;     // euclidean
    int metric;
    
    void createHamming(char* name, int d, char* data);
    void createEuclidean(char* name, int d, double* data, int m);
    
    void destroyHamming();
    void destroyEuclidean();
    
    void visualize();
    
    double distance(Item* item);
      
};

#endif	/* ITEM_H */

