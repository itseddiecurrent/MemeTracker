using namespace std;
class FibonacciHeap {
    public:
    struct node {
        Vertex keyVertex;
        node* parent;
        node* child;
        node* prev;
        node* next;
    }
    void insert(Vertex v);
    node* myNode; 
};