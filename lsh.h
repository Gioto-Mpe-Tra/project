#ifndef LSH_H
#define	LSH_H

#include <iostream>

#include "HashTable.h"
#include "ItemTable.h"
#include "Gtable.h"
#include "H.h"
#include "G.h"
#include "Item.h"

using namespace std;

class Lsh {
public:
    int k;
    int L;
    int d;
    
    char inputfile[300];
    char outputfile[300];
    char queryfile[300];
    
    double half_distance;
    
    HashTable* hashTables;
    Gtable gt;
    
    Lsh();
    ~Lsh();

    void solve(int k, int L, int d, ItemTable* item_table, HashTable* cluster_table, char metric_space[200], char metric_space_value[200]);
        
    
    void error();
    
    void solveHamming(ItemTable* item_table, HashTable* cluster_table);
    void solveEuclidean(char metric[200]);
    void solveMatrix();
    
    void searchHamming(Item* q);
    void searchHamming(Item* q, double R, ItemTable* item_table, HashTable* cluster_table, int offset);
    
    void searchEuclidean(Item* q);
    void searchEuclidean(Item* q, double R);
    
};

#endif	/* LSH_H */

