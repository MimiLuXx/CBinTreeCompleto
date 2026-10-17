// BinaryTree v3 sin recursividad STacks.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <stack>
#include <queue>
using namespace std;

struct Node {
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

    void inorder_stack(Node* n);
    void preorder_stack(Node* n);
    void posorder_stack(Node* n);

    //RECORRIDO POR NIVELS
    void levelorder_queue(Node* n);
    void imprimirPorNiveles(Node* n);
    int contarNodos(Node* n);
    int contarNodosporNivel(Node* n, int k);

    //ejercicios pract
    int height(Node* n);
    void imprimirNivel(Node* n, int k); //usando recursivida
    void imprimirTodoPorNiveles(Node* n);
    int kPosicion(int k);
    int contarEntreNiveles(Node* n, int a, int b);
    int ProfundidadNodo(Node* n, int x);
    int contarEntreNiveles(Node* n, int a, int b, int nivelActual);
    int imprimirAncestros(Node* n, int x);

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
    for (p = &root; *p && (*p)->v != x; p = &((*p)->nodes[x > (*p)->v]));
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
    if ((*p)->nodes[0] != 0 && (*p)->nodes[1] != 0) {
        Node** q = rep(p);
        (*p)->v = (*q)->v;
        p = q;
    }
    Node* temp = *p;
    if ((*p)->nodes[1]) {
        *p = (*p)->nodes[1];
    }
    else {
        *p = (*p)->nodes[0];
    }
    delete temp;
    return 1;
}
Node** CBinTree::rep(Node** p) {
    Node** q;
    if (brep) {
        q = &((*p)->nodes[0]);
        while ((*q)->nodes[1]) {
            q = &((*q)->nodes[1]);
        }
    }
    else {//derecha
        q = &((*p)->nodes[1]);
        while ((*q)->nodes[0]) {
            q = &((*q)->nodes[0]);
        }
    }
    brep = !brep;
    return q;
}

void CBinTree::inorder_stack(Node* n) {
    if (!n) return;
    stack <pair <int, Node*> > s;
    s.push(make_pair(0, n));
    while (!s.empty()) {
        // s.top().first => estado 0,1,2,3
        // s.top().second => puntero al nodo --- nodo actual
        Node* actual = s.top().second;
        switch (s.top().first) {
        case 0:
            s.top().first = 1;
            if (actual->nodes[0]) {
                s.push(make_pair(0, actual->nodes[0]));
            }
            break;

        case 1:
            cout << actual->v << " ";
            s.top().first = 2;
            break;

        case 2:
            s.top().first = 3;
            if (actual->nodes[1]) {
                s.push(make_pair(0, actual->nodes[1]));
            }
            break;

        case 3:
            s.pop();
            break;
        }
    }
}


void CBinTree::preorder_stack(Node* n) {
    if (!n) return;
    stack<pair <int, Node*>> s;
    s.push(make_pair(0, n));
    //first numeros //second node
    while (!s.empty()) {
        Node* actual = s.top().second;
        switch (s.top().first) {
        case 0:
            cout << actual->v << " ";
            s.top().first = 1;
            break;

        case 1:
            s.top().first = 2;
            if (actual->nodes[0]) {
                s.push(make_pair(0, actual->nodes[0]));
            }
            break;

        case 2:
            s.top().first = 3;
            if (actual->nodes[1]) {
                s.push(make_pair(0, actual->nodes[1]));
            }
            break;

        case 3:
            s.pop();
            break;
        }

    }
}


void CBinTree::posorder_stack(Node* n) {
    if (!n) return;
    stack<pair <int, Node*>> s;
    s.push(make_pair(0, n));

    while (!s.empty()) {
        Node* actual = s.top().second;

        switch (s.top().first) {
        case 0:
            s.top().first = 1;
            if (actual->nodes[0]) {
                s.push(make_pair(0, actual->nodes[0]));
            }
            break;

        case 1:
            s.top().first = 2;
            if (actual->nodes[1]) {
                s.push(make_pair(0, actual->nodes[1]));
            }
            break;

        case 2:
            cout << actual->v << " ";
            s.top().first = 3;
            break;

        case 3:
            s.pop();
            break;
        }
    }
}

void CBinTree::levelorder_queue(Node* n) {
    if (!n) return;
    queue<Node*> q;

    q.push(n);
    while (!q.empty()) {
        Node* actual = q.front();
        cout << actual->v << " ";
        q.pop();
        if (actual->nodes[0]) {
            q.push(actual->nodes[0]);
        }
        if (actual->nodes[1]) {
            q.push(actual->nodes[1]);
        }
    }

}

void CBinTree::imprimirPorNiveles(Node* n) {
    if (!n) return;
    queue <Node*> q;
    q.push(n);

    while (!q.empty()) {

        int cantidad = q.size();

        for (int i = 0; i < cantidad; i++) {
            Node* actual = q.front();
            q.pop();

            cout << actual->v << " ";

            if (actual->nodes[0]) {
                q.push(actual->nodes[0]);
            }
            if (actual->nodes[1]) {
                q.push(actual->nodes[1]);
            }
        }
        cout << endl;

    }
}

int CBinTree::contarNodos(Node* n) {
    if (!n) return 0;
    queue <Node*> q;
    int contador = 0;
    q.push(n);


    while (!q.empty()) {
        Node* actual = q.front();
        q.pop();
        cout << actual->v << " ";
        contador++;

        if (actual->nodes[0]) {
            q.push(actual->nodes[0]);
        }
        if (actual->nodes[1]) {
            q.push(actual->nodes[1]);
        }

    }
    return contador;

}



void CBinTree::imprimirNivel(Node* n, int k) { //cuando es void llamar recursiva sin crear int
    if (!n) return;
    if (k == 0) {
        cout << n->v << " ";
        return;
    }
    imprimirNivel(n->nodes[0], k - 1);
    imprimirNivel(n->nodes[1], k - 1);
}

int CBinTree::height(Node* n) {
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

void CBinTree::imprimirTodoPorNiveles(Node* n) {
    if (!n) return;
    for (int i = 0; i < height(n); i++) { //i representa k es decir nivel actual
        imprimirNivel(n, i);
        cout << endl;
    }
}

void inorderVector(Node* n, vector<int>& valores) {
    if (!n) return;
    inorderVector(n->nodes[0], valores);
    valores.push_back(n->v);
    inorderVector(n->nodes[1], valores);
}

int CBinTree::kPosicion(int k) {
    vector<int>valores;
    inorderVector(root, valores);

    if (k < 1 || k > valores.size()) return -1;

    return valores[k - 1];

}


int CBinTree::ProfundidadNodo(Node* n, int x) {
    if (!n) return -1;

    if (n->v == x) {
        return 0;
    }
    int contador;
    if (x < n->v) {
        contador = ProfundidadNodo(n->nodes[0], x);
    }
    else {
        contador = ProfundidadNodo(n->nodes[1], x);
    }

    if (contador == -1) return -1;
    return contador + 1;
}


int CBinTree::contarNodosporNivel(Node* n, int k) {
    if (!n || k < 0) return 0;

    if (k == 0) {
        cout << n->v << " ";
        return 1;
    }
    int izq = contarNodosporNivel(n->nodes[0], k - 1);
    int der = contarNodosporNivel(n->nodes[1], k - 1);
    return izq + der;

}

/*int CBinTree::contarEntreNiveles(Node* n, int a, int b) {
    int contador = 0;

    for (int i = a; i <= b; i++) { //recorre ambos niveles
        contador = contador + contarNodosporNivel(n, i);
    }
    return contador;
}
*/

int CBinTree::contarEntreNiveles(Node* n, int a, int b) {
    if (!n || a < 0 || b < a)return 0;
    queue<Node*>q;
    q.push(n);

    int nivelActual = 0;
    int contador = 0;

    while (!q.empty() && nivelActual <= b) {
        for (int i = 0; i < q.size(); i++) {
            Node* actual = q.front();
            q.pop();

            if (nivelActual >= a && nivelActual <= b) {
                contador++;
            }
            if (actual->nodes[0]) {
                q.push(actual->nodes[0]);
            }
            if (actual->nodes[1]) {
                q.push(actual->nodes[1]);
            }

        }
        nivelActual++;
    }
    return contador;
}


int CBinTree::contarEntreNiveles(Node* n, int a, int b, int nivelActual) {
    if (!n) return 0;
    int actual = 0;
    if (nivelActual >= a && nivelActual <= b) {
        actual = 1;

    }
    int izq = contarEntreNiveles(n->nodes[0], a, b, nivelActual + 1);
    int der = contarEntreNiveles(n->nodes[1], a, b, nivelActual + 1);

    return izq + der + actual;
}

int CBinTree::imprimirAncestros(Node* n, int x) {
    stack<Node*> s;

    Node* actual = n;

    while (actual && actual->v != x) {
        s.push(actual);

        if (actual->v < x) {
            actual = actual->nodes[1];
        }
        else {
            actual = actual->nodes[0];
        }
    }

    if (!actual) return 0;

    vector <int> v;
    while (!s.empty()) {
        Node* temp = s.top();
        v.push_back(temp->v);
        s.pop();
    }
    for (int i = v.size()-1; i >= 0; i--) {
        cout << v[i] << " ";
    }
    return 1;

}


void CBinTree::print()
{
    vector<int> valores;
    cout << "\nCon stack\n";
    cout << "Inorder:   "; inorder_stack(root); cout << "\n";
    cout << "Preorder:  "; preorder_stack(root); cout << "\n";
    cout << "Postorder: "; posorder_stack(root); cout << "\n";

    cout << "\nCon Niveles\n";
    cout << "Por niveles: "; levelorder_queue(root); cout << "\n";
    cout << "Por niveles dejando espacio: "; imprimirPorNiveles(root); cout << "\n";
    cout << "Numero de Nodos: " << contarNodos(root) << endl;

    cout << "Imprimir X nivel: "; imprimirNivel(root, 2); cout << endl;
    cout << "Imprimir por niveles: " << endl; imprimirTodoPorNiveles(root);
    cout << "Altura: " << height(root) << endl;

    cout << "Posicion X:" << kPosicion(6) << endl;

    cout << "Nodos en nivel 1: " << contarNodosporNivel(root, 1) << endl;
    cout << "Nodos en nivel 2: " << contarNodosporNivel(root, 2) << endl;
    cout << "Nodos entre Niveles: " << contarEntreNiveles(root, 1, 2) << endl;

    cout << contarEntreNiveles(root, 1, 2, 0) << endl;

    cout << "Imprimir ancestrros: " << imprimirAncestros(root,66) << endl;
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


