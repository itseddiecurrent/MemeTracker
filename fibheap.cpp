#include "fibheap.h"
#include <string>
using namespace std;

void FibonacciHeap::insert(Vertex v) {
    struct node* newnode = new struct node;
    newnode->keyVertex = v;
    newnode->parent = nullptr;
    newnode->child = nullptr;
    newnode->degree = 0;
    newnode->prev = newnode;
    newnode->next = newnode;
    if (myNode != nullptr) {
        (myNode->prev)->next = newnode;
        newnode->next = myNode;
        newnode->prev = myNode->prev;
        myNode->prev = newnode;
        //Comparison operator that I have no idea how to implement. How tf do we sort priority on a string?
        if ((string)newnode->keyVertex < (string)myNode->keyVertex) {
            myNode = newnode;
        }
    } else {
        myNode = newnode;
    }
    nodeCount++;
}

void FibonacciHeap::Fibonacci_Link(node* p2, node* p1) {
    (p2->prev)->next = p2->next;
    (p2->next)->prev = p2->prev;
    if (p1->right == p1) {
        myNode = p1;
    }
    
}

