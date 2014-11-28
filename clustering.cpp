
#include "Clustering.h"
#include "Item.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <math.h>


#include "myheader.h"
#include "Lsh.h"

using namespace std;

void Clustering::createClusteringProblem(int k, int L, int c) {
    this->k = k;
    this->L = L;
    this->c = c;
    item_counter = 0;

    cluster_table.create(c);
}

void Clustering::destroy() {
    item_table.destroy();
    cluster_table.destroy();
}

void Clustering::readHamming() {
    ifstream ifs(inputfile);
    ifstream temp_ifs(inputfile);
    char temp[200];
    char name[200];
    char data[200];
    string dummy;
    int i = 0;

    while (!temp_ifs.eof()) {
        getline(temp_ifs, dummy);
        item_counter++;
    }
    item_counter -= 2;
    temp_ifs.close();

    item_table.create(item_counter);

    ifs >> temp; // diavazo epikefalida
    ifs >> temp;

    while (!ifs.eof()) {
        ifs >> name;
        ifs >> data;

        item_table.items[i].createHamming(name, d, data);
        i++;
    }

    ifs.close();
}

void Clustering::readEuclidean(char metric[200]) {
    ifstream ifs(inputfile);
    ifstream temp_ifs(inputfile);
    char temp[200];
    char name[200];
    char data[200];
    string dummy;
    int i = 0;
    int m = -1;

    if (strcmp(metric, "euclidean") == 0) {
        m = METRIC_EUCLIDEAN;
    } else if (strcmp(metric, "manhattan") == 0) {
        m = METRIC_MANHATTAN;
    } else {
        m = METRIC_COSINE;
    }

    while (!temp_ifs.eof()) {
        getline(temp_ifs, dummy);
        item_counter++;
    }
    item_counter -= 3;
    temp_ifs.close();

    item_table.create(item_counter);

    ifs >> temp; // diavazo epikefalida
    ifs >> temp;
    ifs >> temp;
    ifs >> temp;

    while (!ifs.eof()) {
        ifs >> name;
        if (ifs.eof()) {
            break;
        }

        double * temp_data = new double[d];

        for (int j = 0; j < d; j++) {
            ifs >> data;
            temp_data[j] = atof(data);
        }

        item_table.items[i].createEuclidean(name, d, temp_data, m);
        i++;

        delete temp_data;
    }

    ifs.close();
}

void Clustering::readMatrix() {
    return;
}

void Clustering::readFromFile(char* inputfile) {
    char first_item_name[200];
    char first_item_value[200];
    char temp[200];
    char metric[200];
    char line[5000];
    int line_length;

    strcpy(this->inputfile, inputfile);

    ifstream ifs(inputfile);

    if (!ifs) {
        cout << "File " << inputfile << " is missing ... \n";
        return;
    } else {
        ifs >> metric_space;
        ifs >> metric_space_value;
        if (strcmp(metric_space_value, "hamming") == 0) {
            ifs >> first_item_name;
            ifs >> first_item_value;
            d = strlen(first_item_value);
            ifs.close();
            readHamming();
        } else if (strcmp(metric_space_value, "euclidean") == 0) {
            ifs >> temp;
            ifs >> metric;

            ifs.getline(line, 5000);
            ifs.getline(line, 5000);
            line_length = strlen(line);
            d = 0;
            for (int i = 0; i < line_length; i++) {
                if (line[i] == '\t') {
                    d++;
                }
            }

            ifs.close();
            readEuclidean(metric);
        } else if (strcmp(metric_space_value, "matrix") == 0) {
            readMatrix();
        } else {
            cout << "Unknown metric_space_value" << endl;
        }
    }
}

void Clustering::kmedoidspp() {
    double dtable[item_counter];
    double ptable[item_counter];
    double random;

    for (int i = 0; i < c; i++) {
        if (i == 0) {
            cluster_table.insert(0, &item_table.items[rand() % item_counter]);
        } else {
            for (int n = 0; n < item_counter; n++) {
                dtable[n] = item_table.items[n].distance(cluster_table.lists[0].head->item);

                for (int j = 1; j < i; j++) {
                    dtable[n] = fmin(dtable[n], item_table.items[n].distance(cluster_table.lists[j].head->item));
                }
            }

            for (int n = 0; n < item_counter; n++) {
                ptable[n] = dtable[n] * dtable[n];

                if (n > 0) {
                    ptable[n] += ptable[n - 1];
                }
            }

            random = (rand() / ((double) RAND_MAX)) * ptable[item_counter - 1];
            int max = item_counter;
            int min = 0;
            int o = 0;

            while (min <= max) {
                int middle = (max + min) / 2;

                if (ptable[middle] == random) {
                    o = middle;
                } else if (ptable[middle] > random) {
                    if (middle == 0 || ptable[middle - 1] < random) {
                        o = middle;
                        break;
                    } else {
                        max = middle - 1;
                    }
                } else {
                    if (middle == item_counter - 1 || ptable[middle + 1] >= random) {
                        o = middle + 1;
                        break;
                    }
                    min = middle + 1;
                }
            }
            cluster_table.insert(i, &item_table.items[o]);
        }

    }
}

void Clustering::parkjun() {
    double pj[item_counter][item_counter];
    double sumpj[item_counter];
    double v[item_counter];
    Item * items[item_counter];

    for (int i = 0; i < item_counter; i++) {
        sumpj[i] = 0;
        for (int j = 0; j < item_counter; j++) {
            pj[i][j] = item_table.items[i].distance(&item_table.items[j]);
            sumpj[i] += pj[i][j];
        }
        items[i] = &item_table.items[i];
    }

    for (int i = 0; i < item_counter; i++) {
        v[i] = 0;
        for (int j = 0; j < item_counter; j++) {
            v[i] += pj[i][j] / sumpj[j];
        }
    }

    double temp;
    Item* tempItem;
    for (int u = 0; u < item_counter; u++) {
        for (int j = item_counter - 1; j > u; j--) {
            if (v[j - 1] > v[j]) {
                temp = v[j - 1];
                v[j - 1] = v[j];
                v[j] = temp;

                tempItem = items[j - 1];
                items[j - 1] = items[j];
                items[j] = tempItem;
            }
        }
    }

    for (int i = 0; i < c; i++) {
        cluster_table.insert(i, items[i]);
    }
}

void Clustering::pam() {
    double d;
    int pos;

    for (int n = 0; n < item_counter; n++) {
        if (item_table.items[n].assigned == false) {
            d = item_table.items[n].distance(cluster_table.lists[0].head->item);
            pos = 0;
        
            for (int j = 1; j < c; j++) {
                double t = fmin(d, item_table.items[n].distance(cluster_table.lists[j].head->item));
                if (d != t) {
                    pos = j;
                    d = t;
                }
            }

            if (&item_table.items[n] != cluster_table.lists[pos].head->item) {
                cluster_table.lists[pos].insert(&item_table.items[n]);
            }

            item_table.items[n].assigned = true;
        }
    }
}

void Clustering::lsh() {
    Lsh lsh;

    lsh.solve(k, L, d, &item_table, &cluster_table, metric_space, metric_space_value);
    pam();
}

void Clustering::lloyd() {
    HashTable* tempClusterTable = new HashTable();
    tempClusterTable->create(cluster_table->size);
    ListNode* tempNode;
    
    
    for (int i=0;i<cluster_table->size;i++)  {
        tempClusterTable->lists[i].insert(medoid);  // ######
    }
}

void Clustering::resetFlags() {
    for (int i = 0; i < item_counter; i++) {
        item_table.items[i].assigned = false;
    }
}

double Clustering::sumJ(HashTable* tempClusterTable) {
    double result = 0;
    Item* centroid;
    ListNode* tempNode;
    
    for (int i=0;i<tempClusterTable->size;i++)  {
        centroid = tempClusterTable->lists[i].head->item;
        tempNode = tempClusterTable->lists[i].head->next;
        
        while(tempNode != NULL) {
            result += centroid->distance(tempNode->item);
            tempNode = tempNode->next;
        }
    }
        
    return result;    
}



void Clustering::solve() {
    // init:    
    //kmedoidspp();
    parkjun();

    //    while (1) {
    //        // assigned
    resetFlags();
    //pam();
    lsh();

    // update
    //    }
    //    

    int counter = 0;
    for (int t = 0, k; t < c; t++) {
        printf("\n---------------------------------------------------------- \n");
        printf("   Cluster #%d: %s %d \n", t, cluster_table.lists[t].head->item->name, cluster_table.lists[t].size);
        printf("---------------------------------------------------------- \n");

        ListNode* temp = cluster_table.lists[t].head;
        k = 0;
        while (temp) {
            printf("%10s \t", temp->item->name);
            if (k > 0 && k % 5 == 0) {
                printf("\n");
            }
            counter++;
            temp = temp->next;
        }
    }
    cout << "\n\n\nTotal items: " << counter << endl;
}
