#pragma once
#include <stddef.h>
#include <stdexcept>
#include "Node.hpp"
#include "Iterators.hpp"

// #define DEBUG
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
        if (parent.get_num_of_childs() > this->k_ary)
            throw std::runtime_error("ERROR: Too many children to this node");

        parent.add_child(child);
    }

    PreOrderIterator<T, K> begin_pre_order()
    {
#ifdef DEBUG
        std::cout << "Creating a new PreOrderIterator with the root" << std::endl;
#endif
        return PreOrderIterator<T, K>(root);
    }

    PreOrderIterator<T, K> end_pre_order()
    {
#ifdef DEBUG
        std::cout << "Creating a new PreOrderIterator with nullptr" << std::endl;
#endif
        return PreOrderIterator<T, K>(nullptr);
    }

    PostOrderIterator<T, K> begin_post_order()
    {
#ifdef DEBUG
        std::cout << "Creating a new PostOrderIterator with the root" << std::endl;
#endif
        return PostOrderIterator<T, K>(root);
    }

    PostOrderIterator<T, K> end_post_order()
    {
#ifdef DEBUG
        std::cout << "Creating a new PostOrderIterator with nullptr" << std::endl;
#endif
        return PostOrderIterator<T, K>(nullptr);
    }

    InOrderIterator<T, K> begin_in_order()
    {
        return InOrderIterator<T, K>(root);
    }

    InOrderIterator<T, K> end_in_order()
    {
        return InOrderIterator<T, K>(nullptr);
    }

    BFSIterator<T, K> begin_bfs_scan()
    {
        return BFSIterator<T, K>(root);
    }

    BFSIterator<T, K> end_bfs_scan()
    {
        return BFSIterator<T, K>(nullptr);
    }

    DFSIterator<T, K> begin_dfs_scan()
    {
        return DFSIterator<T, K>(root);
    }

    DFSIterator<T, K> end_dfs_scan()
    {
        return DFSIterator<T, K>(nullptr);
    }

    MinHeap<T> begin_min_heap_scan()
    {
        if(this->k_ary > 2)
            throw std::runtime_error(ERROR_MESSEGE);

        return MinHeap<T>(root);
    }

    MinHeap<T> end_min_heap_scan()
    {
        if(this->k_ary > 2)
            throw std::runtime_error(ERROR_MESSEGE);
            
        return MinHeap<T>(nullptr);
    }
};
