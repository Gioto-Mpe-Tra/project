#ifndef HASHTABLE_H
#define	HASHTABLE_H

#include "Item.h"
#include "G.h"

#include "List.h"

class HashTable {
public:
    int size;
    List* lists;
    
    G* g;

    
    void create(int k);
    void create(int k, G* g);  
    
    void destroy();

    void insert(Item* item);    
    void insert(int cluster_id, Item* item);
};

#endif	/* HASHTABLE_H */

