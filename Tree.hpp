#pragma once
#include <stddef.h>
#include <stdexcept>
#include "Node.hpp"
#include "Iterators.hpp"

//  #define DEBUG
 #define ERROR_MESSEGE "Error: Can pre-order traverse only on 2-ary trees"

template <typename T, int K = 2>
class Tree
{
private:
    size_t k_ary;
    Node<T> *root;

public:
    Tree() : k_ary(K), root(nullptr){};

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

    PreOrderIterator<T> begin_pre_order()
    {
        if (k_ary == 2)
        {
#ifdef DEBUG
            std::cout << "Creating a new PreOrderIterator with the root" << std::endl;
#endif
            return PreOrderIterator<T>(root);
        }

        throw std::runtime_error(ERROR_MESSEGE);
    }

    PreOrderIterator<T> end_pre_order()
    {
        if (k_ary == 2)
        {
#ifdef DEBUG
            std::cout << "Creating a new PreOrderIterator with nullptr" << std::endl;
#endif
            return PreOrderIterator<T>(nullptr);
        }

        throw std::runtime_error(ERROR_MESSEGE);
    }

    PostOrderIterator<T> begin_post_order()
    {
        if (k_ary == 2)
        {
#ifdef DEBUG
            std::cout << "Creating a new PostOrderIterator with the root" << std::endl;
#endif
            return PostOrderIterator<T>(root);
        }

        throw std::runtime_error(ERROR_MESSEGE);
    }

    PostOrderIterator<T> end_post_order()
    {
        if (k_ary == 2)
        {
#ifdef DEBUG
            std::cout << "Creating a new PostOrderIterator with nullptr" << std::endl;
#endif
            return PostOrderIterator<T>(nullptr);
        }

        throw std::runtime_error(ERROR_MESSEGE);
    }

    BFSIterator<T> begin_bfs_scan()
    {
        return BFSIterator<T>(root);
    }

    BFSIterator<T> end_bfs_scan()
    {
        return BFSIterator<T>(nullptr);
    }
};
