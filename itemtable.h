#ifndef ITEMTABLE_H
#define	ITEMTABLE_H

#include "Item.h"

class ItemTable {
public:
    Item* items;
    int item_counter;
    
    void create(int item_counter);
    void destroy();
};

#endif	/* ITEMTABLE_H */

