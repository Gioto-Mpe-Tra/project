#ifndef HEADER_LIST
#define HEADER_LIST

#include "Item.h"

class ListNode { // class ListNode
public:
    Item* item;
    ListNode* next; //double linked list
    ListNode* previous;

    ListNode();
    ListNode(Item* item, ListNode* n_next, ListNode* n_previous);
};

class List {
public:
    int size;
    ListNode* head;
    ListNode* tail;

    List();

    void insert(Item* item);
};

#endif 

