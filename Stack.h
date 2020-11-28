#ifndef STACK_H
#define STACK_H
#include <QApplication>
using namespace std;

template <typename T>
class Stack {
    struct Node {
        T e; Node* next;
        Node(T e, Node* next = nullptr) : e(e), next(next) {}
    };

    Node* _top;
    int     len;

public:
    Stack() : _top(nullptr), len(0) {}

    ~Stack() {
        while (_top != nullptr) {
            Node* aux = _top;
            _top = _top->next;
            delete aux;
        }
    }

    int     size() { return len; }
    bool    empty() { return len == 0; }

    void    push(T e) {
        _top = new Node(e, _top);
        ++len;
    }

    void    pop() {
        if (len > 0) {
            Node* aux = _top;
            _top = _top->next;
            delete aux;
            --len;
        }
    }

    T       top() {
        if (len > 0) {
            return _top->e;
        }
        return nullptr;
    }
    T get(int pos){
        if (pos < 0 || pos >= len) return nullptr;
        Node* aux = _top;
        for (int i = 0; i < pos; ++i)
        {
            aux = aux->next;
        }
        return aux->e;
    }
    void  clear(){
        while (len > 0){
            pop();
        }
    }


};
#endif // STACK_H
