#include "Gtable.h"
#include "G.h"

void Gtable::createHamming(int k, int L, int D) {
    int f = 0, l = 0, z=0;
    g_table = new G[L];
    for (int i = 0; i < L; i++) {
        g_table[i].createHamming(k, D);

        f = 0;
        l = 0;
        while (f == 0 && i > 0) {
            for (int u = 0; u < i; u++) {
                z = 0;
                l = 0;
                while ((g_table[i].h_table[z].i == g_table[u].h_table[z].i) && (z < k)) {
                    z++;
                }

                if (z == k )
                    l = 1;
                else
                    l = 0;
                
                if (l == 1) {
                    u = 0;
                    f = 0;
                    g_table[i].createHamming(k, D);
                }
                if (u == i - 1 && l == 0)
                    f = 1;
            }
        }
    }
    // dupe check
}

void Gtable::createEuclidean(int k, int L, int D) {
    g_table = new G[L];
    for (int i = 0; i < L; i++) {
        g_table[i].createEuclidean(k, D);
    }
}

void Gtable::destroyHamming() {
    delete g_table;
}

void Gtable::destroyEuclidean() {
    delete g_table;
}

/* enc 
void Gtable::createHamming(int k, int L, int D, int type) {
    g_table = new G[L];
    hamm* g_table_ham;
    eucl* g_table_euc;
    
    switch(type) {
        case HAMMING:
          g_table_ham = (hamm*)  g_table;
          create(g_table_ham . . . . )
          break;
        case HAMMING:
          g_table_eucl = (eucl*)  g_table;
          create(g_table_eucl . . . . )
          break;
          
    }
}
 */
