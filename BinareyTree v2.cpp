// BinareyTree v2.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
using namespace std;
struct Node
{
    Node(int value) {
        v = value;
        nodes[0] = nodes[1] = 0;
    }
    int v;
    Node* nodes[2];
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
    void preorder(Node* n);
    void postorder(Node* n);
    void reverse(Node* n);

    int contarnodos(Node* n);
    int contarhojas(Node* n);
    int contarDosHijos(Node* n);
    int contarUnHijo(Node* n);
    int contarNodosConvalorPar(Node* n);
    int contarMayores(Node* n, int x);
    int imprimirMenore(Node* n, int x);
    int sumarPares(Node* n);
    int contarEnRango(Node* n, int a, int b);
    int height(Node* n);
    int profundidadNodo(Node* n, int x);
    int contarNodosenNivel(Node* n, int k);



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
}

bool CBinTree::find(int x, Node**& p) {
    for (p = &root; *p && (*p)->v != x; p = &((*p)->nodes[x > (*p)->v])) {};
    return *p && (*p)->v == x;
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
    if ((*p)->nodes[0] && (*p)->nodes[1]) {
        Node** q = rep(p);
        (*p)->v = (*q)->v;
        p = q;
    }
    //caso 1
    Node* temp = *p;
    if ((*p)->nodes[1]) {
        *p = (*p)->nodes[1];
    }
    else
        *p = (*p)->nodes[0];
    delete temp;
    return 1;
}

void CBinTree::inorder(Node* n) {
    if (!n) return;
    inorder(n->nodes[0]);
    cout << n->v << " ";
    inorder(n->nodes[1]);
}

void CBinTree::postorder(Node* n) {
    if (!n) return;
    postorder(n->nodes[0]);
    postorder(n->nodes[1]);
    cout << n->v << " ";
}

void CBinTree::preorder(Node* n) {
    if (!n) return;
    cout << n->v << " ";
    preorder(n->nodes[0]);
    preorder(n->nodes[1]);
}

void CBinTree::reverse(Node* n)
{
    if (!n) return;
    reverse(n->nodes[1]);
    std::cout << n->v << " ";
    reverse(n->nodes[0]);
}

int CBinTree::contarnodos(Node* n) {
    if (!n) return 0;
    int der = contarnodos(n->nodes[1]);
    int iz = contarnodos(n->nodes[0]);
    return der + iz + 1;
}


int CBinTree::contarhojas(Node* n) {
    if (!n) return 0;
    if (n->nodes[0] == nullptr && n->nodes[1] == nullptr)
        return 1;

    int iz = contarhojas(n->nodes[0]);
    int der = contarhojas(n->nodes[1]);

    return iz + der;
}


int CBinTree::contarDosHijos(Node* n) {
    if (!n) return 0;

    int izq = contarDosHijos(n->nodes[0]);
    int der= contarDosHijos(n->nodes[1]);

    if (n->nodes[1] != 0 && n->nodes[0] != 0) {
        return izq + der + 1;
    }

    return izq + der;
}

int CBinTree::contarUnHijo(Node* n) {
    if (!n) return 0;
    int izq = contarUnHijo(n->nodes[0]);
    int der = contarUnHijo(n->nodes[1]);

    if ((n->nodes[0] != nullptr && n->nodes[1] == nullptr) || n->nodes[1] != nullptr && n->nodes[0] == nullptr) {
        return izq + der + 1;
    }
    return izq + der;
}

int CBinTree::contarNodosConvalorPar(Node* n) {
    if (!n) return 0;
    int izq = contarNodosConvalorPar(n->nodes[0]);
    int der = contarNodosConvalorPar(n->nodes[1]);

    if (n->v % 2 == 0) {
        return izq + der + 1;
    }
    return izq + der;
}

int CBinTree::contarMayores(Node* n, int x) {
    if (!n) return 0;
    int izq = contarMayores(n->nodes[0],x); //inorder
    int actual = 0;
    if (n->v > x) {
        cout << n->v << " ";
        actual = 1;
    }
    int der = contarMayores(n->nodes[1],x);

    return izq + der + actual;
}

int CBinTree::imprimirMenore(Node* n, int x) {
    if (!n) return 0;
    int izq = imprimirMenore(n->nodes[0], x);
    int actual = 0;
    if (n->v < x) {
        cout << n->v << " ";
        actual = 1;
    }
    int der = imprimirMenore(n->nodes[1], x);
    return izq + der + actual;
}

int CBinTree::sumarPares(Node* n) {
    if (!n) return 0;
    int izq = sumarPares(n->nodes[0]);
    int der = sumarPares(n->nodes[1]);
    if (n->v % 2 == 0) {
        return n->v + izq + der;
    }
    return izq + der;
}
int CBinTree::contarEnRango(Node* n, int a, int b) {
    if (!n) return 0;
    int izq = contarEnRango(n->nodes[0],a,b);
    int actual = 0;
    if (n->v >= a && n->v <= b) {
        cout << n->v << " ";
        actual = 1;
    }
    int der = contarEnRango(n->nodes[1],a,b);

    return izq + der + actual;
};

int CBinTree::height(Node* n) { //altura contando nodos. Si fuera aristas cambiar if (!n) return -1;
    if (!n) return 0;
    int izq = height(n->nodes[0]);
    int der = height(n->nodes[1]);

    if (izq < der) {
        return der + 1;
    }
    else {
        return izq + 1;
    }
}

int CBinTree::profundidadNodo(Node* n, int x) {
    if (!n) return -1; //no existe

    if (n->v == x) { //empiezo a contar
        return 0; 
    }
    int resultado;
    if (n->v < x) {
        resultado = profundidadNodo(n->nodes[1], x);
    }
    else {
        resultado = profundidadNodo(n->nodes[0], x);
    }
    if (resultado == -1) //nodo buscado no existe 
        return -1;

    return resultado + 1;
}

int CBinTree::contarNodosenNivel(Node* n, int k) {
    if (!n || k < 0) return 0;
    if (k == 0) { //nivel que busco
        cout << n->v << " ";
        return 1;
    }

    int izq = contarNodosenNivel(n->nodes[0], k-1);
    int der = contarNodosenNivel(n->nodes[1], k-1);

    return izq + der;

}

Node** CBinTree::rep(Node** p) {
    Node** q;
    if (brep) {
        q = &((*p)->nodes[0]);
        while ((*q)->nodes[1])
            q = &((*q)->nodes[1]);
    }
    else {
        q = &((*p)->nodes[1]);
        while ((*q)->nodes[0])
            q = &((*q)->nodes[0]);
    }
    brep = !brep;
    return q;
}

//for(q = &((*p)->nodes[!brep]); (*q)->nodes[brep] !=0; q = &((*q)->nodes[brep]); 
// brep = !brep;
//return 1;



void CBinTree::print() {
    
    cout << "inorder: "; inorder(root); cout << endl;
    cout << "preorder: "; preorder(root); cout << "\n";
    cout << "postorder: "; postorder(root); cout << "\n";
    cout << "reverse: "; reverse(root); cout << "\n";
    cout << "Nodos en total: " << contarnodos(root) << endl;
    cout << "Hojas sin hijos: " << contarhojas(root) << endl;
    cout << "Nodos con dos hijos: " << contarDosHijos(root) << endl;
    cout << "Nodos con un hijo: " << contarUnHijo(root) << endl;
    cout << "Mayores: " << contarMayores(root, 60) << endl;
    cout << "Menores: " << imprimirMenore(root, 60) << endl;
    cout << "Suma Pares: " << sumarPares(root) << endl;
    cout << "Contar en Rango: " << contarEnRango(root,60,90) << endl;
    cout << "Altura: " << height(root) << endl;
    cout << "Profundidad de X: " << profundidadNodo(root, 99) << endl;
    cout << "Contar Nodos en Nivel x: " << contarNodosenNivel(root, 1) << endl;
}

int main()
{
    CBinTree t;
    t.ins(61);
    t.ins(50); t.ins(80);
    t.ins(33); t.ins(55); t.ins(65); t.ins(90);
    t.ins(66);
    t.print();

}


