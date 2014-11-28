#include "Item.h"
#include "myheader.h"
#include "HashTable.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>

using namespace std;

// data: "001010001010010000101011..."
void Item::createHamming(char* name, int d, char* data) {
    type = HAMMING_SPACE;
    this->d = d;
    values = NULL;
    bits = new char[d+1];
    
    for (int i = 0 ;i<d;i++) {
        bits[i] = data[i] - 48;
    }    
    bits[d] = '\0';
    
    strcpy(this->name, name);
}

void Item::createEuclidean(char* name, int d, double* tempdata, int m) {
    type = EUCLIDEAN_SPACE;
    this->d = d;
    bits = NULL;
    values = new double[d];
    
    for (int i = 0 ;i<d;i++) {
        values[i] = tempdata[i];
    }
    strcpy(this->name, name);
}

void Item::destroyHamming() {
    if (bits != NULL) {
        delete bits;
    }
}

void Item::destroyEuclidean() {
    if (values != NULL) {
        delete values;
    }
}


void  Item::visualize() {
    cout << name << " " ;
    
    //for (int i = 0 ;i<d;i++) {
      //  cout << (char)(bits[i] + 48);
    //}
    
    //for (int i = 0 ;i<d;i++) {
      //  cout << values[i] << " ";
    //}
    cout << endl;
}

 double Item::distance(Item* item) {
     double distance = 0;
     if (type == HAMMING_SPACE) {
         for (int i=0;i<d;i++) {
             if (bits[i] != item->bits[i]) {
                 distance++;
             }
         }
     } else if (type == EUCLIDEAN_SPACE) {
         if (metric == METRIC_EUCLIDEAN) {
             for (int i=0;i<d;i++) {
                 distance = distance + pow(values[i] - item->values[i],2);
             }
             distance = sqrt(distance);
         } else if (metric == METRIC_MANHATTAN) {
             // ###
         } else if (metric == METRIC_COSINE) {
             // ###
         }
     }
     return distance;
 }
 
