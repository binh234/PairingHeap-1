#ifndef PAIRINGHEAP_H_INCLUDED
#define PAIRINGHEAP_H_INCLUDED
#include <iostream>

using namespace std;

class Node{
    public:
    int value;
    Node* child;        //first child
    Node* nextSibling; //next sibling

    Node(int value){
        this->value = value;
        this->child = nullptr;
        this->nextSibling = nullptr;
    }
    Node(){
        this->child = nullptr;
        this->nextSibling = nullptr;
    }
};

class PairingHeap{
private:
    Node *root;
    void clean(Node*& root);
    Node* Meld(Node* root, Node* h);
    Node* TwoPassMeld(Node* p);

public:

    PairingHeap(){
        root = nullptr;
    }
    PairingHeap(Node *root){
        this->root = root;
    }
    ~PairingHeap(){
        clean(root);
    }
    void clean(){
        clean(root);
    }
    void Meld(Node* h){
        root= Meld(root,h);
    }
    int FindMin();
    void Insert(int x);
    void DecreaseKey(Node*& X, int newVal);
    void Delete(Node*& key);
    int DeleteMin();
    bool IsEmpty(){return root == nullptr;}
};

PairingHeap* MakeHeap(){
    return new PairingHeap();
}

int PairingHeap::FindMin(){
    if (IsEmpty()) return -1;
    return this->root->value;
}

void PairingHeap::Insert(int x){
    //Make x into a one-node tree and link it with current tree
    Node *newNode = new Node(x);
    this->root=this->Meld(root,newNode);
}

Node* PairingHeap::Meld(Node* root, Node* h){
    //Return the tree formed by linking current tree and h.
    if (IsEmpty())return h;
    if (h==nullptr) return root;
    int root1 = root->value;
    int root2 = h->value;

    //Make the root of smaller key the parent of the root of larger key
    if (root1 < root2){
        //Result root is root1 (current root)
        h->nextSibling = root->child;         //set right child of h (sibling)
        root->child = h;                      //insert h into left child of current root
        return root;
    }
    else{
        //Result root is root2 (root of h)
        root->nextSibling = h->child;     //set right child (sibling)
        h->child = root;                  //insert current tree into left child of h
        return h;
    }
}

/**
 * Decrease value in node X to newVal
 * newVal must be smaller than the currently stored value.
 */
void PairingHeap::DecreaseKey(Node*& X, int newVal){
    if(newVal<X->value){
        X->value=newVal;
        if(X!=root){
            Node* p= X;         //Cuts X's subtree from the heap
            X=X->nextSibling;
            p->nextSibling=nullptr;
            root=Meld(root, p); //Link 2 trees resulting from the cut
        }
    }
}

/**
 * Cut the root's child and its siblings to trees
 * The resulting trees are then combined to form a single tree
 * The linkings are performed in two passes
 * In the first pass, melding each pair of trees from left-to-right
 * In the second pass, links the remaining trees from right-to-left to form a single tree
 */
Node* PairingHeap::TwoPassMeld(Node* p){
    if(p==nullptr||p->nextSibling==nullptr)
        return p;
    Node *A, *B, *newNode;
    A = p;
    B = p->nextSibling;
    newNode = p->nextSibling->nextSibling;

    A->nextSibling = nullptr;
    B->nextSibling = nullptr;

    return Meld(Meld(A, B), TwoPassMeld(newNode));
}


//Delete min value of the heap and return it
//Return -1 if heap is empty
int PairingHeap::DeleteMin(){
    if(root==nullptr)
        return -1;
    int res=root->value;
    Node* child=root->child;
    delete root;
    root=TwoPassMeld(child);
    return res;
}

//Delete node key from the heap
void PairingHeap::Delete(Node*& key){
    DecreaseKey(key,INT_MIN); //Decrease node key to infinite
    DeleteMin();               //Then deletes it
}

//Cleans the heap
void PairingHeap::clean(Node*& root){
    if(root==nullptr)
        return;
    if(root->child!=nullptr)
        clean(root->child);
    if(root->nextSibling!=nullptr)
        clean(root->nextSibling);
    delete root;
    root=nullptr;
}

#endif // PAIRINGHEAP_H_INCLUDED
