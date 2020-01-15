#include <iostream>
using namespace std;
class Node{
    public:
    int value;
    Node* left;  //first child
    Node* right; //next sibling or parent
    
    Node(int value){
        this->value = value;
        this->left = nullptr;
        this->right = nullptr;
    }
    Node(){
        this->left = nullptr;
        this->right = nullptr;
    }
};

class PairingHeap{
    private: Node *root;
    public:
        PairingHeap(){
            root = new Node();
        }
        void FindMin();
        void Insert(int x);
        void Meld(PairingHeap h);
        void DecreaseKey(int delta, int key);
        void Delete(int key);
        void DeleteMin();
};

PairingHeap MakeHeap(){
    return *(new PairingHeap());
}

int main(){
    PairingHeap h = MakeHeap();
    return 0;
}
