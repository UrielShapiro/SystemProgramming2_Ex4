#pragma once
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Complex.hpp"

using std::vector;

template <typename T>
class Node
{
private:
    T data;
    vector<Node<T> *> children;

public:
    Node(T data) : data(data), children{} {};
    Node(const Node<T> &other) : data(other.get_data()), children(other.get_children()) {}
    Node(const Complex<T> &other) : data(other), children{} {}

    void add_child(Node<T> &child)
    {
        this->children.push_back(&child);
    }

    size_t get_num_of_childs() const
    {
        return this->children.size();
    }

    const T &get_data() const
    {
        return this->data;
    }

    vector<Node<T> *> get_children() const
    {
        return this->children;
    }

    bool is_leaf() const
    {
        return this->children.empty();
    }

    bool operator<(const Node<T> &other) const
    {
        return this->data() < other.get_data();
    }

    bool operator>(const Node<T> &other) const
    {
        return this->data() > other.get_data();
    }

    bool operator==(const Node<T> &other) const
    {
        return this->data == other.get_data();
    }

};