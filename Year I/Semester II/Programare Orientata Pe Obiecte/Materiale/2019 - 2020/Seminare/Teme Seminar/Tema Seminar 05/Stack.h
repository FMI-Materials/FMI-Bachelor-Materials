//
// Created by Darius Buhai on 4/30/20.
//

#ifndef SEMINAR5_STACK_H
#define SEMINAR5_STACK_H

#pragma once
#include <iostream>
#include <algorithm>
#include <vector>

template <typename T = int>
class Stack{
    T* mem;
    int top;
    unsigned count;
public:
    Stack(unsigned _d = 10): mem(new T[_d]), count(_d), top(-1){}
    Stack(const Stack & oth);
    ~Stack();
    Stack<T>& operator = (const Stack<T>& ob);
    T Top();
    T Pop();
    std::vector<T> Pop(unsigned nr);

    template <typename D>
    friend std::istream& operator>>(std::istream& in, Stack<D>& s);
    template <typename D>
    friend std::ostream& operator<<(std::ostream& out, const Stack<D>& s);

    void push(T);
};

template <typename T>
T Stack<T>::Top()
{
    if (top == -1)
        throw std::runtime_error("Tried to get top of empty stack");
    return mem[top];
}

template <typename T>
T Stack<T>::Pop()
{
    if (top == -1)
        throw std::runtime_error("Tried to pop an empty stack");
    auto t = mem[top];
    top--;
    return t;
}


template <typename T>
Stack<T>::Stack(const Stack & oth)
{
    top = oth.top;
    count = oth.count;
    mem = new T[count];
    std::copy(oth.mem, oth.mem + top + 1, mem);
}

template <typename T>
void Stack<T>::push(T val){
    if(top==count-1){
        T* aux = new T[count+10];
        count+=10;
        std::copy(mem, mem+count,aux);
        delete []mem;
        mem = aux;
    }
    mem[++top] = val;
}

template <typename T>
Stack<T>::~Stack() {
    delete []mem;
}

template <typename T>
Stack<T>& Stack<T>::operator = (const Stack<T>& ob) {
    if (this = &ob) return *this;
    delete []mem;
    top = ob.top;
    count = ob.top;
    mem = new T[count];
    std::copy(ob.mem, ob.mem + count, mem);
    return *this;
}

/*template <typename T>
std::istream& Stack<T>::operator>>(std::istream& in, Stack<T>& s)
{
    delete []mem;
    int n;
    in >> n;
    top = n-1;
    count = n;
    mem = new T[n];
    for(int i = 0; i < n; ++i){
        T x;
        in >> x;
        mem[i] = x;
    }
    return in;
}*/

template <typename D>
std::ostream& operator<<(std::ostream& out, const Stack<D>& s)
{
    for(int i = 0; i <= s.top; ++i) out << s.mem[i] << " ";
    return out;
}

template<typename T>
std::vector<T> Stack<T>::Pop(unsigned nr)
{
    if(top < nr)
        throw std::runtime_error("Tried to pop too many elements from stack");
    std::vector<T> ret;
    while(nr--)
        ret.push_back(Pop());
    return ret;
}


#endif //SEMINAR5_STACK_H
