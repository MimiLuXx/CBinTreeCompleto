#include <iostream>
#include <stack>
#include <queue>//cola
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

    int height(Node* n); // calcular la profundidad de forma recursiva

    /* posibles otros calculos

     - calcular la altura, pero usando un recorrido por profundidad como: inorder, preorder,
     -  calcular la altura, pero usando un recorrido por amplitud como: levels
     -  recorrer solo los nodos del los ultimos niveles
     - etc
     - la sugerencia para estudiar es utilizar este codigo generar mas posibles preguntas, utilizando Gemini, Claude, etc

    */

    void levels(Node* n);
    void inorder_stack(Node* n);
    void preorder_stack(Node* n);
    void posorder_stack(Node* n);
    void reverse_stack(Node* n);
    void inorder(Node* n);
    void preorder(Node* n);
    void posorder(Node* n);
    void reverse(Node* n);
    int height_levels(Node* n);
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

bool CBinTree::find(int x, Node**& p)
{
    for (p = &root; *p && (*p)->v != x;p = &((*p)->nodes[x > (*p)->v]));
    return *p && (*p)->v == x;
}

bool CBinTree::ins(int x)
{
    Node** p;
    if (find(x, p)) return 0;
    *p = new Node(x);
    return 1;
}

bool CBinTree::rem(int x)
{
    Node** p;
    if (!find(x, p)) return 0;

    if ((*p)->nodes[0] && (*p)->nodes[1]) //2
    {
        Node** q = rep(p);
        (*p)->v = (*q)->v;
        p = q;
    }

    Node* t = *p;
    *p = (*p)->nodes[(*p)->nodes[1] != 0];
    delete t;
    return 1;
}

Node** CBinTree::rep(Node** p)
{
    Node** q;
    for (q = &((*p)->nodes[!brep]); (*q)->nodes[brep] != 0;
        q = &((*q)->nodes[brep]));
    brep = !brep;
    return q;
}

void CBinTree::print()
{
    cout << "\nCon stack\n";
    cout << "Inorder:   "; inorder_stack(root); cout << "\n";
    cout << "Preorder:  "; preorder_stack(root); cout << "\n";
    cout << "Postorder: "; posorder_stack(root); cout << "\n";
    cout << "Reverse:   "; reverse_stack(root); cout << "\n";

    cout << "Recursivos\n";
    cout << "Inorder:   "; inorder(root); cout << "\n";
    cout << "Preorder:  "; preorder(root); cout << "\n";
    cout << "Postorder: "; posorder(root); cout << "\n";
    cout << "Reverse:   "; reverse(root); cout << "\n";

    cout << "Altura recursividad:" << " " << height(root) << "\n";
    cout << "Niveles: "; levels(root); cout << "\n";
    cout << "Altura usando amplitud levels: " << height_levels(root) << "\n";
}

int CBinTree::height(Node* n) //altura con recursividad
{
    if (!n) return 0;
    int r = height(n->nodes[1]);
    int l = height(n->nodes[0]);
    
    if (r > l) 
        return r + 1;
    else 
        return l + 1;
    
}


void CBinTree::levels(Node* n) //recorrido imprime nodos por niveles
{
    queue<Node*> q;
    q.push(root);

    if (!n) {
        cout << "Arbol vacio";
    }

    while (!q.empty())
    {
        Node* actual = q.front();
        cout << actual->v << " ";

        if(actual->nodes[0])
            q.push(actual->nodes[0]);
   
        if(actual->nodes[1])
            q.push(actual->nodes[1]);

        q.pop();
        
    }
}
int CBinTree::height_levels(Node* n) { //altura usando amplitud niveles
    int contador = 0;
    if (!n) {
        cout << "Arbol vacio" << contador;
        return 0;
    }

    queue<Node*> q;
    q.push(root);
    while (!q.empty())
    {
        int cantidadnodos = q.size(); // una vez por nivel
        for (int i = 0; i < cantidadnodos; i++) {
            Node* actual = q.front();
            cout << actual->v << " ";
            q.pop();

            if (actual->nodes[0])
                q.push(actual->nodes[0]);

            if (actual->nodes[1])
                q.push(actual->nodes[1]);

        }
        cout << endl;
        contador++;
    }

    return contador;
}



void CBinTree::inorder_stack(Node* n)
{   //ejemplo => std::pair<int, char> p;  p.first = 2;    p.second = 'x';

    stack< pair<int, Node*> > s;

    s.push(make_pair(0, root));

    while (!s.empty())
    {
        Node* actual = s.top().second;
        // s.top().first => estado 0,1,2,3
        // s.top().second => puntero al nodo --- nodo actual
        switch (s.top().first)
        {
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

void CBinTree::preorder_stack(Node* n)
{
    {   //ejemplo => std::pair<int, char> p;  p.first = 2;    p.second = 'x';

        stack< pair<int, Node*> > s;

        s.push(make_pair(0, root));

        while (!s.empty())
        {
            Node* actual = s.top().second;
            // s.top().first => estado 0,1,2,3
            // s.top().second => puntero al nodo --- nodo actual
            switch (s.top().first)
            {
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
}
void CBinTree::posorder_stack(Node* n)
{
    {
           //ejemplo => std::pair<int, char> p;  p.first = 2;    p.second = 'x';

            stack< pair<int, Node*> > s;

            s.push(make_pair(0, root));

            while (!s.empty())
            {
                Node* actual = s.top().second;
                // s.top().first => estado 0,1,2,3
                // s.top().second => puntero al nodo --- nodo actual
                switch (s.top().first)
                {
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
}
void CBinTree::reverse_stack(Node* n)
{
    {
        {   //ejemplo => std::pair<int, char> p;  p.first = 2;    p.second = 'x';

            stack< pair<int, Node*> > s;

            s.push(make_pair(0, root));

            while (!s.empty())
            {
                Node* actual = s.top().second;
                // s.top().first => estado 0,1,2,3
                // s.top().second => puntero al nodo --- nodo actual
                switch (s.top().first)
                {
                case 0:
                    s.top().first = 1;
                    if (actual->nodes[1]) {
                        s.push(make_pair(0, actual->nodes[1]));
                    }
                    break;
                    


                case 1:
                    cout << actual->v << " ";
                    s.top().first = 2;
                    break;

                case 2:
                    s.top().first = 3;
                    if (actual->nodes[0]) {
                        s.push(make_pair(0, actual->nodes[0]));
                    }
                    break;
                    


                case 3:
                    s.pop();
                    break;
                }
            }
        }
    }
}


void CBinTree::inorder(Node* n)
{
    if (!n) return;
    inorder(n->nodes[0]);
    cout << n->v << " ";
    inorder(n->nodes[1]);
}

void CBinTree::preorder(Node* n)
{
    if (!n) return;
    cout << n->v << " ";
    preorder(n->nodes[0]);
    preorder(n->nodes[1]);
}

void CBinTree::posorder(Node* n)
{
    if (!n) return;
    posorder(n->nodes[0]);
    posorder(n->nodes[1]);
    cout << n->v << " ";
}

void CBinTree::reverse(Node* n)
{
    if (!n) return;
    reverse(n->nodes[1]);
    std::cout << n->v << " ";
    reverse(n->nodes[0]);
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