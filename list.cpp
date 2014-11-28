#include <iostream>
#include <cstring>

#include "List.h"
#include "Item.h"

using namespace std;

// ********************* LIST NODE ************************

ListNode::ListNode(Item * item, ListNode* n_next, ListNode* n_previous) :
    item(item), next(n_next), previous(n_previous)  //constructor
{

}

// **********************  LIST *****************************

List::List() : size(0), head(NULL), tail(NULL) {                       //initialize List

}

void List::insert(Item* item) {                                              // insert job to the list
    if (head == NULL) {
        head = tail = new ListNode(item, NULL, NULL);                      // if not exist ListNode create new ListNode
    } else {
        tail->next = new ListNode(item, NULL, tail);
        tail = tail->next;
    }
    size++;                                                             //increase the size of list
}
