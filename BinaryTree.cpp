// BinaryTree.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include<iostream>
using namespace std;

struct Node
{
    Node(int v) {
        value = v;
        left = right = 0;
    }
    int value;
    Node* left, * right;
};

class CBinTree
{
public:
    CBinTree();
    ~CBinTree();
    bool find(int x, Node**& p);
    bool ins(int x);
    bool rem(int x);
    Node** rep(Node** p);
    void print();
    void inorder(Node* n);
    void limpiar(Node* n);
private:
    Node* root;
    bool brep;
};

CBinTree::CBinTree()
{
    root = 0;  brep = 0;
}

CBinTree::~CBinTree()
{
    limpiar(root);
}


bool CBinTree::find(int x, Node**& p){
    p = &root;
    while ( *p && (*p)->value != x) {
        if (x > (*p)->value)
            p = &((*p)->right);
        else {
            p = &((*p)->left);
        }
    }
    return *p && (*p)->value == x;

}

bool CBinTree::ins(int x) {
    Node** p;
    if (find(x, p)) return 0;
    *p = new Node(x);
    return 1;

}

bool CBinTree::rem(int x) {
    Node** p;
    if (!find(x, p)) return 0;

    //caso 2
    if ((*p)->right && (*p)->left) {
        Node** q = rep(p);
        (*p)->value = (*q)->value;
        p = q;

    }

    //caso 1
    Node* temp = *p;
    if (temp->right) {
        *p = (*p)->right;
    }
    else {
        *p = (*p)->left;
    }
    delete temp;
    return 1;
}


Node** CBinTree::rep(Node** p) {
    Node** q;
    if (brep) { //primera vuelta brep = 0 -> if (breap) es falsa
        q = &((*p)->left);
        while ((*q)->right!= 0) {
            q = &((*p)->right);
        }
    }
    else {
        q = &((*p)->right);
        while ((*q)->left) {
            q = &((*q)->left);
        }
    }
    brep = !brep;
    return q;
}

void CBinTree::inorder(Node* n) { //procesa nodo antes de ir a la derecha
    if (!n)return;
    inorder(n->left);
    cout << n->value << " ";
    inorder(n->right);
}

void CBinTree::limpiar(Node* n) { //recorre ambos hijos y elimina
    if (!n) return;
    limpiar(n->left);
    limpiar(n->right);
    delete n;
}


void CBinTree::print() {
    inorder(root);
    cout << endl;

}

int main()
{
    CBinTree t;
    t.ins(61);
    t.ins(50); t.ins(80);
    t.ins(33); t.ins(55); t.ins(65); t.ins(90);
    t.ins(66);
    t.print();
    t.rem(33); t.print();
    t.rem(65); t.print();
    t.rem(61); t.print();
    t.rem(50); t.rem(55); t.rem(66); t.rem(90); t.print();
    t.rem(80); t.print();
    t.ins(6); t.print();
}   