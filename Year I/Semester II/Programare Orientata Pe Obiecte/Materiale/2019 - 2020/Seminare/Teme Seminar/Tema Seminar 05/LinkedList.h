#ifndef SEMINAR5_LINKEDLIST_H
#define SEMINAR5_LINKEDLIST_H

#pragma once
#include <iostream>
#include "Node.h"

template <typename T>
class LinkedList {
    Node<T>* first;
    Node<T>* last;
    unsigned size;

    void Dealocare();
public:
    ~LinkedList();
    LinkedList();
    LinkedList(unsigned, T);
    LinkedList(const LinkedList&);
    void push(T);
    void erase(const T& val);
    bool find(const T& val);
    LinkedList& operator =(const LinkedList&);

    template <typename D>
    friend std::istream& operator>>(std::istream&, LinkedList<D>&);
    template <class D>
    friend std::ostream& operator<<(std::ostream&,const LinkedList<D>&);
    T operator [] (unsigned int poz);

};

template <typename T>
LinkedList<T>::LinkedList(): first(nullptr), last(nullptr), size(0) {}

template <typename T>
LinkedList<T>::~LinkedList()
{
    Dealocare();
}

template <typename T>
void LinkedList<T>::Dealocare()
{
    Node<T>* acum = first;
    while (acum) {
        first = acum->next;
        delete acum;
        acum = first;
    }
    size = 0;
    first = last = nullptr;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& oth)
{
    if (&oth == this)
        return *this;
    Dealocare();
    LinkedList l(oth);
    this->first = l.first;
    this->last = l.last;
    this->size = l.size;
    l.first = l.last = nullptr;
    return *this;
}

template <typename T>
void LinkedList<T>::push(T val) {
    if (first == nullptr) {
        first = new Node<T>(val);
        last = first;
        size = 1;
    } else {
        Node<T>* newNode = new Node<T>(val);
        last->next = newNode;
        last = newNode;
        ++size;
    }
}

template <typename T>
LinkedList<T>::LinkedList(unsigned sz, T val):LinkedList(){
    while (sz--){
        this->push(val);
    }
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& other):LinkedList(){
    for (Node<T>* node = other.first; node; node = node->next){
        this->push(node->val);
    }
}

template <typename T>
void LinkedList<T>::erase(const T& val) {
    Node<T>* pos = first;
    Node<T>* prev = nullptr;
    while (pos and pos->value != val) {
        prev = pos;
        pos = pos->next;
    }

    if (pos == nullptr) return;

    if (prev == nullptr) {
        first = first->next;
        delete pos;
    }
    else {
        prev->next = pos->next;
        delete pos;
        if (prev->next == nullptr) last = prev;
    }

    --size;
}

template <typename T>
bool LinkedList<T>::find(const T& val) {
    for (Node<T>* pos = first; pos; pos = pos->next) {
        if (pos->val == val) return true;
    }
    return false;
}

template <typename T>
std::istream& operator>>(std::istream& in, LinkedList<T>& obj)
{
    obj.Dealocare();
    int n;
    in >> n;
    for (int i = 0; i < n; i++)
    {
        T t;
        in >> t;
        obj.push(t);
    }
    return in;
}

template <class T>
std::ostream& operator<<(std::ostream& out, const LinkedList<T>& obj)
{
    Node<T>* first = obj.first;
    while(first != nullptr)
    {
        out << first->value << " ";
        first = first->next;
    }
    return out;
}

#endif //SEMINAR5_LINKEDLIST_H
