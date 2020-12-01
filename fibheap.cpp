#include "fibheap.h"
#include <string>
using namespace std;

void FibonacciHeap::insert(Vertex v) {
    struct node* newnode = new struct node;
    newnode->keyVertex = v;
    newnode->parent = nullptr;
    newnode->child = nullptr;
    newnode->prev = newnode;
    newnode->next = newnode;
    if (myNode != nullptr) {
        (myNode->prev)->next = newnode;
        newnode->next = myNode;
        newnode->prev = myNode->prev;
        myNode->prev = newnode;
        if (((string)newnode->keyVertex).length() < ((string)myNode->keyVertex).length) {
            myNode = newnode;
        }
    } else {
        myNode = newnode;
    }
}

