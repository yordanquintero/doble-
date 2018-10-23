#include <stdlib.h>
#include <stdio.h>

#define ASCENDENTE 1
#define DESCENDENTE 0

class nodo{
public:
    nodo(int v, nodo *sig=NULL, nodo *ant=NULL):
        valor(v), siguiente(sig), anterior(ant){}

private:
    int valor;
    nodo *siguiente;
    nodo *anterior;

    friend class lista;

};

typedef nodo *pnodo;

class lista{
public:
    lista() : plista(NULL){}
    ~lista();

    void insertar(int v);
    void borrar(int v);
    bool listaVacia() {return plista==NULL;}
    void mostrar(int);
    void siguiente();
    void anterior();
    void primero();
    void ultimo();
    bool actual(){return plista!=NULL;}
    int valorActual() {return plista->valor;}

private:
    pnodo plista;
};

lista::~lista(){
    pnodo aux;
    primero();

    while(plista){
        aux=plista;
        plista=plista->siguiente;
        delete aux;
    }
}

void lista::insertar(int v){
    pnodo nuevo;

    primero();

    if(listaVacia()||plista->valor > v){
        nuevo = new nodo(v,plista);
        if(!plista) plista=nuevo;
        else plista->anterior=nuevo;
    }

    else{
        while(plista->siguiente&&plista->siguiente->valor<=v) siguiente();

        nuevo = new nodo(v,plista->siguiente,plista);
        plista->siguiente=nuevo;
        if(nuevo->siguiente) nuevo->siguiente->anterior=nuevo;
    }
}

void lista::borrar(int v){
    pnodo nodo;

    nodo=plista;

    while(nodo&&nodo->valor<v) nodo=nodo->siguiente;
    while(nodo&&nodo->valor>v) nodo=nodo->anterior;

    if(!nodo || nodo->valor !=v) return;

    if(nodo->anterior)
        nodo->anterior->siguiente = nodo->siguiente;
    if(nodo->siguiente)
        nodo->siguiente->anterior = nodo->anterior;
    delete nodo;
}

void lista::mostrar(int orden){
    pnodo nodo;
    if(orden==ASCENDENTE){
        primero();
        nodo=plista;
        while(nodo){
            printf("%d -> ", nodo->valor);
            nodo=nodo->siguiente;
        }
    }
    else{
        ultimo();
        nodo=plista;
        while(nodo){
            printf("%d -> ", nodo->valor);
            nodo=nodo->anterior;
        }
    }
    printf("\n");
}

void lista::siguiente(){
    if(plista) plista = plista->siguiente;
}

void lista::anterior(){
    if(plista) plista = plista->anterior;
}

void lista::primero(){
    while(plista&&plista->anterior) plista=plista->anterior;
}

void lista::ultimo(){
    while(plista&&plista->siguiente) plista=plista->siguiente;
}

int main(){
    lista listaDE;

    listaDE.insertar(20);
    listaDE.insertar(10);
    listaDE.insertar(40);
    listaDE.insertar(30);

    listaDE.mostrar(ASCENDENTE);
    listaDE.mostrar(DESCENDENTE);

    listaDE.primero();
    printf("Primero: %d\n", listaDE.valorActual());

    listaDE.ultimo();
    printf("Ultimo: %d\n", listaDE.valorActual());

    listaDE.borrar(10);
    listaDE.borrar(15);
    listaDE.borrar(45);
    listaDE.borrar(40);

    listaDE.mostrar(ASCENDENTE);
    listaDE.mostrar(DESCENDENTE);

    system("pause");

    return 0;
}

