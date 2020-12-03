using namespace std;
class FibonacciHeap {
    public:
    struct node {
        Vertex keyVertex;
        node* parent;
        node* child;
        node* prev;
        node* next;
        int degree;
    }
    void insert(Vertex v);
    void Fibonacci_Link(node* p2, node* p1);
    

    private:
    node* myNode;
    int nodeCount; 
};