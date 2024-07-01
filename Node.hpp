/**
 * Name: Uriel Shapiro
 * ID: 9745
 */

#ifndef NODE_HPP
#define NODE_HPP
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Complex.hpp"

using std::vector;

/**
 * @brief A class that represents a node in a k-ary tree.
 */
template <typename T>
class Node
{
private:
    T data; // Data can be any type
    vector<Node<T> *> children; // Each node has a vector of pointers to its children

public:
    Node(T data) : data(data), children{} {};
    Node(const Node<T> &other) : data(other.get_data()), children(other.get_children()) {}

    // This constructor is used to convert a Complex object to a Node object, 
    // because we want the type of object inside the Node to be Complex.
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
        return this->children.empty();  // If the node has no children -> he is leaf
    }

    // If non-comperable type is used, there would be a compilation time error
    bool operator<(const Node<T> &other) const
    {
        return this->get_data() < other.get_data();
    }

    bool operator>(const Node<T> &other) const
    {
        return this->get_data() > other.get_data();
    }

    bool operator==(const Node<T> &other) const
    {
        return this->get_data() == other.get_data();
    }
};
#endif