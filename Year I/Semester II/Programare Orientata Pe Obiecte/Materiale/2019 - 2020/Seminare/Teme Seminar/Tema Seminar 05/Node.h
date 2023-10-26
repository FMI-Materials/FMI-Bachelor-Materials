//
// Created by Darius Buhai on 4/30/20.
//

#ifndef SEMINAR5_NODE_H
#define SEMINAR5_NODE_H

#pragma once

template <typename T> class LinkedList;

template <typename T>
class Node
{
    T value;
    Node<T>* next;
public:
    Node(T, Node<T>* = nullptr);
    friend class LinkedList<T>;
};

template <typename T>
Node<T>::Node(T val, Node<T>* ptr): value(val), next(ptr) {}


#endif //SEMINAR5_NODE_H
