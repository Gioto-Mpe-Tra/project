
#ifndef CLUSTERING_H
#define	CLUSTERING_H

#include "ItemTable.h"
#include "HashTable.h"

class Clustering {
public:
    int k;
    int L;
    int c;
    int d;
    
    char metric_space[200];
    char metric_space_value[200];
    
    int item_counter;
    
    char inputfile[300];
    char outputfile[300];
    char configfile[300];
    
    HashTable cluster_table;
    ItemTable item_table;
        
    void createClusteringProblem(int k, int L, int c);
    void destroy();
    
    void readHamming();
    void readEuclidean(char metric[200]);
    void readMatrix();
    
    void kmedoidspp();
    void parkjun();
    
    void pam();
    void lsh();
    
    void lloyd();
    
    void solve();
    
    double sumJ(HashTable* tempClusterTable);
    
    void resetFlags();
    
    void readFromFile(char *filename);
    
private:

};

#endif	/* CLUSTERING_H */

