#ifndef AVL2P_H
#define AVL2P_H

#include<mainwindow.h>
#include <ui_mainwindow.h>
#include <functional>
#include <fstream>
#include <string>
#include<iomanip>
#include <sstream>
#include <ctime>
#include <iostream>

#include <QMainWindow>
#include "User.h"
#include "Amigos.h"
#include "Lista.h"
#include "Stack.h"
#include <sstream>
#include <stdlib.h>
#include <QMessageBox>
#include <functional>

using namespace std;
using std::function;

#define max(a, b) (((a) > (b))? (a) : (b))





template<typename T, typename R = T,typename R2=T >
class AVL2P {

    struct  Nodo {
        T elemt;
        Nodo* derecha;
        Nodo* izquierda;
        int altura;

        Nodo(T elemt, Nodo* derecha = nullptr, Nodo* izquierda = nullptr) :elemt(elemt), derecha(derecha), izquierda(izquierda),altura(0) {}


    };
    using fkey = function<R(T)>;
    using Fsecondkey = function<R2(T)>;


    using f_pr = function<void(T)>;
    using uint = unsigned int;
    Nodo* raiz;
    uint len;
    fkey key;
    Fsecondkey key2;
    int numero = 0;
    int cantidadamostrar;


public:
    AVL2P(fkey key = [](T a) {return a; }, Fsecondkey key2 = [](T a) {return a; }) : raiz(nullptr), len(0), key(key),key2(key2) {}
    ~AVL2P() {
        destruir(raiz);
    }
    void addelem(T elemt) { addelem(raiz, elemt); }
    void inorder(f_pr f) { inorder(raiz, f); }


    void mostrarenordenconParametro(f_pr f, int num,char letra) {
        cantidadamostrar = num + 1;
        mostrarenordenconParametro(raiz, f,letra);
    }

    void Remover(R atr) {
            remover2(raiz, atr);
        }
    void Removercon2P(R atr,R2 atr2) {
          remover2_2p(raiz,atr,atr2);
        }
    int getlen(){
        return len;
    }




    T find(R attr) {
        auto node = find(raiz, attr);
        return node == nullptr ? nullptr : node->elem;
    }

    T findmax() {
        if (raiz == nullptr) {
            return nullptr;
        }
        else {
            auto node = findmax(raiz);
            return node->elem;
        }
    }


    void mostrartodascoincidencias(f_pr f, R num) {
        mostrartodascoincidencias(raiz, f, num);
    }








private:



    void mostrartodascoincidencias(Nodo* nodo, f_pr f, R num) {
        if (nodo != nullptr) {
            mostrartodascoincidencias(nodo->izquierda, f,num);
            if (num == key(nodo->elemt)) f(nodo->elemt);
            mostrartodascoincidencias(nodo->derecha, f,num);
        }
    }
    /////
    void mos(Nodo* nodo, f_pr f) {
        numero += 1;
        if(numero<cantidadamostrar+1){ f(nodo->elemt); }
    }

    //////

    void destruir(Nodo* nodo) {
        if (nodo != nullptr) {
            destroy(nodo->derecha);
            destroy(nodo->izquierda);
            delete nodo;
        }
    }




    int height(Nodo* node) {
        return node == nullptr ? -1 : node->altura;
    }


    void addelem(Nodo*& nodo, T elemt) {
        if (nodo == nullptr) {
            nodo = new Nodo(elemt);
            len++;

        }
        else {
            if (key(elemt) < key(nodo->elemt)) {
            addelem(nodo->izquierda, elemt);
            }
            else {
            addelem(nodo->derecha, elemt);
            }
            balance(nodo);
        }

    }


    void   updateHeight(Nodo* node) {
        if (node != nullptr) {
            node->altura = max(height(node->izquierda), height(node->derecha)) + 1;
        }
    }

    void   rotarizq(Nodo*& node) {
        Nodo* aux = node->derecha;
        node->derecha = aux->izquierda;
        updateHeight(node);
        aux->izquierda = node;
        updateHeight(aux);
        node = aux;
    }

    void   rotarder(Nodo*& node) {
        Nodo* aux = node->izquierda;
        node->izquierda = aux->derecha;
        updateHeight(node);
        aux->derecha = node;
        updateHeight(aux);
        node = aux;
    }




    void  balance(Nodo*& node) {
        int hizq = height(node->izquierda);
        int hder = height(node->derecha);

        if (hder - hizq < -1) {
            hizq = height(node->izquierda->izquierda);
            hder = height(node->izquierda->derecha);
            if (hder > hizq) {
                rotarizq(node->izquierda);
            }
            rotarder(node);
        }
        else if (hder - hizq > 1) {
            hizq = height(node->derecha->izquierda);
            hder = height(node->derecha->derecha);
            if (hizq > hder) {
                rotarder(node->derecha);
            }
            rotarizq(node);
        }
        else {
            updateHeight(node);
        }
    }


    void inorder(Nodo* nodo, f_pr f) {
        if (nodo != nullptr) {
            inorder(nodo->izquierda, f);
            f(nodo->elemt);
            inorder(nodo->derecha, f);

        }
    }







    void mostrarultimosx(Nodo* nodo, f_pr f) {/////se usa para mostrar los ultimos elementos en orden de forma ascendente
        numero += 1;
        if (numero > len + 1 - cantidadamostrar)f(nodo->elemt);
    }
    void mostrarprimerosx(Nodo* nodo, f_pr f) {/////se usa para mostrar los primeros en el inorden elementos en orden de forma ascendente
        numero += 1;
        if (numero < cantidadamostrar)f(nodo->elemt);
    }
    void mostrarnumParametro(Nodo* nodo, f_pr f,char letra) {
        if (nodo != nullptr) {
            mostrarnumParametro(nodo->derecha, f,letra);
            if(letra=='p')mostrarultimosx(nodo, f);///usamos mostrar2 si queremos los n ultimos.
            if(letra=='u')mostrarprimerosx(nodo, f);
            mostrarnumParametro(nodo->izquierda, f,letra);
        }
    }
    void mostrarenordenconParametro(Nodo* nodo, f_pr f,char letra) {
        mostrarnumParametro(nodo, f,letra);
        numero = 0;
    }






    Nodo*& find(Nodo*& nodo, R Atrib) {
        if (nodo == nullptr) {
            return dummynull;
        }
        else if (Atrib == key(nodo->elemt)) {
            return nodo;
        }
        else if (Atrib < key(nodo->elemt)) {
            return find(nodo->izquierda, Atrib);
        }
        else if (Atrib >= key(nodo->elemt)) {
            return find(nodo->derecha, Atrib);
        }
    }

    Nodo*& findmax(Nodo*& nodo) {
        if (nodo->derecha == nullptr) {
            return nodo;
        }
        else {
            return findmax(nodo->derecha);
        }
    }




    //de un lado
    T remover(Nodo*& node) {
        if (node->derecha == nullptr) {
            Nodo* aux = node;
            node = node->izquierda;
            auto otroelem = aux->elemt;
            delete aux;
            len--;
            return otroelem;
        }
        else {
            auto otroelem = remover(node->derecha);
            balance(node);
            return otroelem;
        }
    }

    //para el otro
    void remover1(Nodo*& node) {
        if (node->izquierda == nullptr) {
            Nodo*& aux = node;
            node = node->derecha;
            delete aux;
            len--;
        }
        else {
            node->elemt = remover(node->izquierda);
        }
    }
    //este busca
    void remover2(Nodo*& node, R elem) {
        if (node != nullptr) {
            if (elem == key(node->elemt)) {
                remover1(node);
            }
            else {
                if (elem < key(node->elemt))
                    remover2(node->izquierda, elem);
                else
                    remover2(node->derecha, elem);
                balance(node);
            }
        }

    }

    void remover2_2p(Nodo*& node, R elem,R2 elem2) {
        if (node != nullptr) {
            if (elem == key(node->elemt)&&elem2==key2(node->elemt)) {
                remover1(node);
            }
            else {
                if (elem < key(node->elemt))
                    remover2_2p(node->izquierda, elem,elem2);
                if(elem==key(node->elemt)){
                    remover2_2p(node->izquierda, elem,elem2);
                }
                if(elem>=key(node->elemt)){
                    remover2_2p(node->derecha, elem,elem2);
                }
                balance(node);
            }
        }

    }




    ////
    Nodo* dummynull = nullptr;

    void mostrartodascoincidencias_dosParam(Nodo* nodo, f_pr f, R num, R2 num2) {
        if (nodo != nullptr) {
            mostrartodascoincidencias(nodo->izquierda, f, num);
            if (num == key(nodo->elemt)||num2==key2(nodo->elemt)) f(nodo->elemt);
            mostrartodascoincidencias(nodo->derecha, f, num);
        }
    }






};


#endif // AVL2P_H
