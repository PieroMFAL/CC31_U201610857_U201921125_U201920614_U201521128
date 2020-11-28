#ifndef BST_H
#define BST_H

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

#define maximo(a, z) (((a) > (z))? (a) : (z))





template<typename T, typename R = T>
class AVL {

    struct  Nodo {
        T elemt;
        Nodo* derecha;
        Nodo* izquierda;
        int altura;

        Nodo(T elemt, Nodo* derecha = nullptr, Nodo* izquierda = nullptr) :elemt(elemt), derecha(derecha), izquierda(izquierda),altura(0) {}


    };
    using fkey = function<R(T)>;

    using f_pr = function<void(T)>;
    using f_prbool = function<bool(T,R)>;

    using uint = unsigned int;
    Nodo* raiz;
    uint len;
    fkey key;
    int numero = 0;
    int cantidadamostrar;


public:
    AVL(fkey key = [](T a) {return a; }) : raiz(nullptr), len(0), key(key) {}
    ~AVL() {
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

    T find(R attr) {
        auto node = find(raiz, attr);
        return node == nullptr ? nullptr : node->elemt;
    }

    T findmax() {
        if (raiz == nullptr) {
            return nullptr;
        }
        else {
            auto node = findmax(raiz);
            return node->elemt;
        }
    }





    void mostrartodascoincidencias(f_pr f, R num) {
        mostrartodascoincidencias(raiz, f, num);
    }




    void mostrartodascoincidenciascontains(R num,f_pr f,f_prbool f2){
        mostrartodascoincidenciascontains(raiz,num,f,f2);

    }
    int getlen(){
            return len;
        }


private:





    void mostrartodascoincidenciascontains(Nodo* nodo, R palabra,f_pr f,f_prbool f2) {
        if (nodo != nullptr) {
            mostrartodascoincidenciascontains(nodo->izquierda,palabra,f,f2);

            if (f2(nodo->elemt,palabra)){f(nodo->elemt); }
            mostrartodascoincidenciascontains(nodo->derecha,palabra,f,f2);
        }
    }





    void mostrartodascoincidencias(Nodo* nodo, f_pr f, R num) {
        if (nodo != nullptr) {
            mostrartodascoincidencias(nodo->izquierda, f,num);
            if (num == key(nodo->elemt)) f(nodo->elemt);
            mostrartodascoincidencias(nodo->derecha, f,num);
        }
    }


    void mos(Nodo* nodo, f_pr f) {
        numero += 1;
        if(numero<cantidadamostrar+1){ f(nodo->elemt); }
    }




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
            node->altura = maximo(height(node->izquierda), height(node->derecha)) + 1;
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
            if(letra=='p')mostrarultimosx(nodo, f);///usamos mostrar si queremos los n ultimos.
            if(letra=='u')mostrarprimerosx(nodo, f);///usamos  mostrar si queremos los n primeros.
            mostrarnumParametro(nodo->izquierda, f,letra);
        }
    }
    void mostrarenordenconParametro(Nodo* nodo, f_pr f,char letra) {
        mostrarnumParametro(nodo, f,letra);
        numero = 0;
    }



//////////




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


    ////
    Nodo* dummynull = nullptr;
};


#endif // BST_H
