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
    public:
        Node *root;
        PairingHeap(){
            root = new Node();
        }
        PairingHeap(Node *root){
            this->root = root;
        }
        int FindMin();
        void Insert(int x);
        PairingHeap* Meld(PairingHeap* h);
        void DecreaseKey(int delta, int key);
        void Delete(int key);
        void DeleteMin();
        bool IsEmpty(){return root == nullptr;}
};

PairingHeap* MakeHeap(){
    return new PairingHeap();
}

int PairingHeap::FindMin(){
    if (IsEmpty) return -1;
    return this->root->value;
}

void PairingHeap::Insert(int x){
    //Make x into a one-node tree and link it with current tree
    PairingHeap *h1 = new PairingHeap(new Node(x));
    this->Meld(h1);
}

PairingHeap* PairingHeap::Meld(PairingHeap* h){
    //Return the tree formed by linking current tree and h.
    if (IsEmpty) return h;
    if (h->IsEmpty) return this;
    int root1 = this->root->value;
    int root2 = h->root->value;

    //Make the root of smaller key the parent of the root of larger key
    if (root1 < root2){
        //Result root is root1 (current root)
        Node* temp = this->root->left; //restore left child
        this->root->left = h->root;    //insert h into left child of current root
        h->root->right = temp;         //set right child of h (sibling)
    }
    else{
        //Result root is root2 (root of h)
        Node* temp = h->root->left;   //restore left child
        h->root->left = this->root;   //insert current tree into left child of h's root
        this->root->right = temp;     //set right child (sibling)
    }
}



int main(){
    PairingHeap *h = MakeHeap();
    return 0;
}
