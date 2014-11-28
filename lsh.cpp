#include "Lsh.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>

#include <cmath>

#include "Item.h"

#include "HashTable.h"
#include "Gtable.h"
#include "H.h"
#include "G.h"
#include "myheader.h"

#include "ItemTable.h"

#define MAX_HITS 2000
using namespace std;

Lsh::Lsh() {
}

Lsh::~Lsh() {
}

void Lsh::error() {
    perror("Something went wrong ! \n");
    exit(-1);
}

void Lsh::searchHamming(Item* q) {
    Item* nn = NULL;
    double min_d = 100000000;
    ListNode* temp;
    double distance;

    for (int i = 0; i < L; i++) {
        int hash = gt.g_table[i].calculate(q);
        temp = hashTables[i].lists[hash].head;
        while (temp != NULL) {
            distance = q->distance(temp->item);
            if (distance < min_d) {
                min_d = distance;
                nn = temp->item;
            }
            temp = temp->next;
        }
    }

    cout << "Nearest Neighbour: " << endl;
    nn->visualize();
    cout << "Distance : " << distance << endl;
}

void Lsh::searchHamming(Item* q, double R, ItemTable* item_table, HashTable* cluster_table, int offset) {
    ListNode* temp;
    double distance;
    int hits = 0;
    int maxhits = MAX_HITS;
    Item** r_neighbour = new Item*[maxhits];
    Item** r_neighbour_temp;

    for (int i = 0; i < MAX_HITS; i++) {
        r_neighbour[i] = NULL;
    }

    for (int i = 0; i < L; i++) {
        int hash = gt.g_table[i].calculate(q);
        temp = hashTables[i].lists[hash].head;
        while (temp != NULL) {
            distance = q->distance(temp->item);
            if (distance < R) {
                int found = 0;
                for (int j = 0; j < hits; j++) {
                    if (strcmp(r_neighbour[j]->name, temp->item->name) == 0) {
                        found = 1;
                        break;
                    }
                }
                if (found == 0) {
                    r_neighbour[hits] = temp->item;
                    hits++;
                    if (hits >= maxhits) {
                        r_neighbour_temp = new Item*[maxhits * 2];
                        for (int l = 0; l < maxhits; l++) {
                            r_neighbour_temp[l] = r_neighbour[l];
                        }
                        delete r_neighbour;
                        r_neighbour = r_neighbour_temp;
                        maxhits = maxhits * 2;
                    }
                }
            }
            temp = temp->next;
        }
    }

    for (int j = 0; j < hits; j++) {
        cluster_table->lists[offset]->insert(r_neighbour[j]);
    }
}

void Lsh::solveHamming(ItemTable* item_table, HashTable* cluster_table) {
    int number_of_buckets = pow(2, k);
    gt.createHamming(k, L, d);
    
    hashTables = new HashTable[L];
    
    for (int i = 0; i < L; i++) {
        hashTables[i].create(number_of_buckets, &gt.g_table[i]);
    }

    for (int i = 0;i<item_table->item_counter;i++) {
        for (int i = 0; i < L; i++) {
            hashTables[i].insert(&item_table->items[i]);
        }
    }
    
    double R = half_distance;
    
    while (R < 10000000) {      // ???
        for (int i=0;i<cluster_table->size;i++) {
            Item* q = cluster_table->lists[i]->head;
            searchHamming(q, R, item_table, cluster_table, i);
        }
        
        R = R*2;
    }

    for (int i = 0; i < L; i++) {
        hashTables[i].destroy();
    }

    delete [] hashTables;
    gt.destroyHamming();
}

void Lsh::searchEuclidean(Item* q) {
    Item* nn = NULL;
    double min_d = 100000000;
    ListNode* temp;
    double distance;

    for (int i = 0; i < L; i++) {
        int hash = gt.g_table[i].calculate(q);
        hash = hash % (unsigned int) (pow(2, 32) - 5);
        hash = hash % hashTables[0].size;

        temp = hashTables[i].lists[hash].head;
        while (temp != NULL) {
            distance = q->distance(temp->item);
            if (distance < min_d) {
                min_d = distance;
                nn = temp->item;
            }
            temp = temp->next;
        }
    }

    cout << "Nearest Neighbour: " << endl;
    nn->visualize();
    cout << "Distance : " << min_d << endl;
}

void Lsh::searchEuclidean(Item* q, double R) {
    ListNode* temp;
    double distance;
    int hits = 0;
    int maxhits = MAX_HITS;
    Item** r_neighbour = new Item*[maxhits];
    Item** r_neighbour_temp;

    for (int i = 0; i < MAX_HITS; i++) {
        r_neighbour[i] = NULL;
    }

    for (int i = 0; i < L; i++) {
        int hash = gt.g_table[i].calculate(q);
        hash = hash % (unsigned int) (pow(2, 32) - 5);
        hash = hash % hashTables[0].size;

        temp = hashTables[i].lists[hash].head;
        while (temp != NULL) {
            distance = q->distance(temp->item);
            if (distance < R) {
                int found = 0;
                for (int j = 0; j < hits; j++) {
                    if (strcmp(r_neighbour[j]->name, temp->item->name) == 0) {
                        found = 1;
                        break;
                    }
                }
                if (found == 0) {
                    r_neighbour[hits] = temp->item;
                    hits++;
                    if (hits >= maxhits) {
                        r_neighbour_temp = new Item*[maxhits * 2];
                        for (int l = 0; l < maxhits; l++) {
                            r_neighbour_temp[l] = r_neighbour[l];
                        }
                        delete r_neighbour;
                        r_neighbour = r_neighbour_temp;
                        maxhits = maxhits * 2;
                    }
                }
            }
            temp = temp->next;
        }
    }

    cout << "Nearest Neighbours: " << endl;
    for (int j = 0; j < hits; j++) {
        cout << j + 1 << ") ";
        r_neighbour[j]->visualize();
    }
}

void Lsh::solveEuclidean(char metric[200]) {
    ifstream ifs(inputfile);
    ifstream qfs(queryfile);
    ifstream temp_ifs(inputfile);
    string dummy;
    // char temp[200];
    char temp[200];
    char name[200];
    char data[200];
    // char itemdata[200]; ###
    int m = -1;
    int item_counter = 0;
    double R;

    if (strcmp(metric, "euclidean") == 0) {
        m = METRIC_EUCLIDEAN;
    } else if (strcmp(metric, "manhattan") == 0) {
        m = METRIC_MANHATTAN;
    } else {
        m = METRIC_COSINE;
    }
    if (m == -1) {
        cout << "unknown metric ! \n";
        return;
    }

    while (!temp_ifs.eof()) {
        getline(temp_ifs, dummy);
        item_counter++;
    }
    item_counter -= 3;

    cout << "Solving euclidean ... with d=" << d << " and k=" << k << " and L=" << L << " and metric: " << metric << " " << m << endl << endl;

    gt.createEuclidean(k, L, d);
    hashTables = new HashTable[L];
    for (int i = 0; i < L; i++) {
        hashTables[i].create(item_counter / 8, &gt.g_table[i]);
    }

    ifs >> temp;
    ifs >> temp;
    ifs >> temp;
    ifs >> temp;

    while (!ifs.eof()) {
        Item* item = new Item();
        ifs >> name;
        if (ifs.eof()) {
            break;
        }
        double * temp_data = new double[d];

        for (int i = 0; i < d; i++) {
            ifs >> data;
            temp_data[i] = atof(data);
        }
        item->createEuclidean(name, d, temp_data, m);

        for (int i = 0; i < L; i++) {
            hashTables[i].insert(item);
        }
        delete temp_data;

        cout << "add: ";
        item->visualize();
    }

    qfs >> R;
    while (!qfs.eof()) {
        Item* q = new Item();
        qfs >> name;
        if (qfs.eof()) {
            break;
        }
        double * temp_data = new double[d];
        for (int i = 0; i < d; i++) {
            qfs >> data;
            temp_data[i] = atof(data);
        }
        q->createEuclidean(name, d, temp_data, m);

        delete temp_data;

        cout << "----------------------------------- q = " << q->name << endl;

        if (R == 0) {
            searchEuclidean(q);
        } else {
            searchEuclidean(q, R);
        }
    }

    for (int i = 0; i < L; i++) {
        hashTables[i].destroy();
    }

    delete [] hashTables;
    gt.destroyEuclidean();
}

void Lsh::solveMatrix() {
    cout << "Solving matrix ... with d=" << d << " and k=" << k << " and L=" << L << endl << endl;
}

void Lsh::solve(int k, int L, int d, ItemTable* item_table, HashTable* cluster_table, char metric_space[200], char metric_space_value[200]) {
    this->k = k;
    this->L = L;
    this->d = d;
    
    half_distance = cluster_table.lists[0].head->item->distance(&cluster_table.lists[1].head->item);
    
    for (int i=0;i<cluster_table->size;i++) {
        for (int j=0;j<cluster_table->size;j++) {
            if (i != j) {
                half_distance =fmin(half_distance, cluster_table.lists[i].head->item->distance(&cluster_table.lists[j].head->item));
            }
        }
    }
    half_distance = half_distance / 2;
    
    if (strcmp(metric_space_value, "hamming") == 0) {
        solveHamming(item_table, cluster_table);
    } else if (strcmp(metric_space_value, "euclidean") == 0) {
        // solveEuclidean(metric);
    } else if (strcmp(metric_space_value, "matrix") == 0) {
        solveMatrix();
    } else {
        cout << "Unknown metric_space_value" << endl;
    }
}
