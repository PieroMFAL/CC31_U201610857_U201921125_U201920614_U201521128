#ifndef LISTA_H
#define LISTA_H
#include <QApplication>
#include <functional>
using namespace std;

template <typename T>
class Lista{
private:
    struct Nodo
    {
        T elem;
        Nodo* next;
        Nodo(T elem, Nodo* next = nullptr) :elem(elem), next(next){}
    };

    Nodo* head;
    int len;

public:
    Lista() :head(nullptr), len(0){}
    ~Lista(){
        while (head != nullptr)
        {
            Nodo* aux = head;
            head = head->next;
            delete aux;
        }
    }
    int size() { return len; }
    bool empty() { return len == 0; }
    void addPos(T elem, int pos){
        function<void(T )> addfirst=[&](T elem){
            head = new Nodo(elem,head);
            ++len;
        };
        if (pos<0 || pos>len) return;
        if (pos == 0)
        {
            addfirst(elem);
        }
        else
        {
            Nodo* aux = head;
            for (int i = 0; i < pos-1; i++)
            {
                aux = aux->next;
            }
            aux->next = new Nodo(elem, aux->next);
            ++len;
        }

    }
    void addLast(T elem){

        addPos(elem, len);
    }
    void removePos(int pos){
       function< void()> removeFirst=[&](){
            if (len > 0)
            {
                Nodo* aux = head;
                head = head->next;
                delete aux;
                --len;
            }

        };
        if (pos < 0 || pos >= len) return;
        if (pos == 0)
        {
            removeFirst();
        }
        else
        {
            Nodo* aux = head;
            for (int i = 0; i < pos-1; i++)
            {
                aux = aux->next;
            }
            Nodo* aux2 = aux->next;
            aux->next = aux2->next;
            delete aux2;//aux
            //delete aux;
            --len;
        }
    }
    T get(int pos){
        if (pos < 0 || pos >= len) return nullptr;
        Nodo* aux = head;
        for (int i = 0; i < pos; ++i)
        {
            aux = aux->next;
        }
        return aux->elem;
    }

};

#endif // LISTA_H
