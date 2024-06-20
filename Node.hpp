#pragma once
#include <vector>

template <typename T>
class Node
{
private:
    T data;
    std::vector<Node<T>> children;

public:
    Node(T data) : data(data), children{} {};
    void add_child(Node<T> &child)
    {
        this->children.push_back(child);
    }

    size_t get_num_of_childs()
    {
        return this->children.size();
    }

    T get_value()
    {
        return this->data;
    }
};