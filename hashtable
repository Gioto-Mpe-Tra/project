#include "HashTable.h"
#include "G.h"
#include "List.h"
#include <stdio.h>
#include <cmath>

void HashTable::create(int number_of_buckets, G* g) {
    size = number_of_buckets;
    this->g =g;
    
    lists = new List[size];
}

void HashTable::create(int number_of_buckets) {
    size = number_of_buckets;
    g =NULL;
    
    lists = new List[size];
}

void HashTable::destroy() {
    delete lists;
}
    

void HashTable::insert(Item* item) {
    double M = pow(2,32) - 5;
    int position = g->calculate(item);
    position = position % ((unsigned int)M);
    position = position % size;
    lists[position].insert(item);
}

void HashTable::insert(int cluster_id, Item* item) {
    lists[cluster_id].insert(item);
}
