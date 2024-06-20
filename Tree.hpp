#pragma once
#include <stddef.h>
#include <stdexcept>
#include "Node.hpp"

template <typename T, int K = 2>
class Tree
{
private:
    size_t k_ary;
    Node<T> *root;

public:
    Tree() : k_ary(K), root(nullptr) {};

    void add_root(Node<T> &_root)
    {
        this->root != nullptr ? throw std::runtime_error("ERROR: This tree already has a root") : this->root = &_root;
    }

    void add_sub_node(Node<T> &parent, Node<T> &child)
    {
        if (parent.get_num_of_childs() > k_ary)
            throw std::runtime_error("ERROR: Too many children to this node");

        parent.add_child(child);
    }

   
};
