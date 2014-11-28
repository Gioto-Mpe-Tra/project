#include "ItemTable.h"
#include "Item.h"

#include <iostream>
#include <fstream>

using namespace std;

void ItemTable::create(int item_counter) {
    this->item_counter = item_counter;
    items = new Item[item_counter];
}

void ItemTable::destroy() {
    delete [] items;
}
