#include <iostream>

using namespace std;

struct nodo {
    int value;
    nodo *izq;
    nodo *der;
    int altura;
};
struct nodo *raiz, *aux;

int crearNodo() {
    aux = ((struct nodo *) malloc (sizeof(struct nodo)));
    cout<<"Cual es el valor: ";
    cin>>aux->value;
    aux->izq = NULL;
    aux->der = NULL;
    aux->altura = 1;    
}

struct nodo* insertar(struct nodo* nodo) {
    if (nodo == NULL) {
        return aux;
    }

    if (aux->value < nodo->value) {
        nodo->izq = insertar(nodo->izq);
    } else if (aux->value > nodo->value) {
        nodo->der = insertar(nodo->der);
    } else {
        return nodo;
    }

    nodo->altura = 1 + mayor(obtenerAltura(nodo->izq), obtenerAltura(nodo->der));

    int balance = obtenerBalance(nodo);

    if (balance > 1 && aux->value < nodo->izq->value) {
        return rotarDerecha(nodo);
    }

    if (balance < -1 && aux->value > nodo->der->value) {
        return rotarIzquierda(nodo);
    }

    if (balance > 1 && aux->value > nodo->izq->value) {
        nodo->izq = rotarIzquierda(nodo->izq);
        return rotarDerecha(nodo);
    }

    if (balance < -1 && aux->value < nodo->der->value) {
        nodo->der = rotarDerecha(nodo->der);
        return rotarIzquierda(nodo);
    }

    return nodo;
}


int obtenerAltura(struct nodo *n) {
    if (n == NULL) {
        return 0;
    }
    return n->altura;
}

int mayor(int a, int b) {
    return (a > b) ? a : b;
}

struct nodo* rotarDerecha(struct nodo *y) {
    struct nodo *x = y->izq;
    struct nodo *T2 = x->der;

    x->der = y;
    y->izq = T2;

    y->altura = mayor(obtenerAltura(y->izq), obtenerAltura(y->der)) + 1;
    x->altura = mayor(obtenerAltura(x->izq), obtenerAltura(x->der)) + 1;

    return x;
}

struct nodo* rotarIzquierda(struct nodo *x) {
    struct nodo *y = x->der;
    struct nodo *T2 = y->izq;

    y->izq = x;
    x->der = T2;

    x->altura = mayor(obtenerAltura(x->izq), obtenerAltura(x->der)) + 1;
    y->altura = mayor(obtenerAltura(y->izq), obtenerAltura(y->der)) + 1;

    return y;
}

int obtenerBalance(struct nodo *n) {
    if (n == NULL) {
        return 0;
    }
    return obtenerAltura(n->izq) - obtenerAltura(n->der);
}

void preOrden(struct nodo *nodo) {
    if (nodo != NULL) {
        cout<<nodo->value<<" ";
        preOrden(nodo->izq);
        preOrden(nodo->der);
    }
}

int main() {
    raiz = NULL;
    int opc = 0;
    do {
        cout<<"Menu de opciones"<<endl;
        cout<<"1. Registrar un nodo"<<endl;
        cout<<"2. Mostrar Arbol"<<endl;
        cout<<"3. Salir"<<endl;
        cin>>opc;
        switch (opc) {
            case 1:
                crearNodo();
                raiz = insertar(raiz);
                break;
            case 2:
                cout<<"PreOrden: ";
                preOrden(raiz);
                cout<<endl;
                break;
        }
    } while (opc != 3);
    return 0;
}
