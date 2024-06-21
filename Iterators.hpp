#pragma once
#include "Node.hpp"
#include <stack>
#include <queue>

// #define DEBUG

using std::stack, std::queue;

template <typename T>
class PreOrderIterator
{
private:
    Node<T> *p_current;
    stack<Node<T> *> pre_order_stack;

public:
    PreOrderIterator(Node<T> *root) : p_current(root)
    {
        if (root != nullptr)
            pre_order_stack.push(root);

#ifdef DEBUG
        std::cout << "stack size on constructor: " << pre_order_stack.size() << std::endl;
#endif
    }

    ~PreOrderIterator() = default;

    Node<T> *get_current() const
    {
        return p_current;
    }

    const T &get_value() const
    {
#ifdef DEBUG
        std::cout << "Reached get_value: stack size: " << pre_order_stack.size() << std::endl;
#endif
        if (p_current != nullptr)
            return p_current->get_data();
        else
            throw std::runtime_error("ERROR in get_value");
    }

    PreOrderIterator<T> *operator++()
    {
        if (!pre_order_stack.empty())
        {
#ifdef DEBUG
            std::cout << "Stack is not empty" << std::endl;
            std::cout << "Stack size: " << pre_order_stack.size() << std::endl;

#endif
            Node<T> *current(pre_order_stack.top());
            pre_order_stack.pop();
#ifdef DEBUG
            std::cout << "Popped the stack" << std::endl;
            std::cout << "Stack size: " << pre_order_stack.size() << std::endl;
#endif
            if (!current->is_leaf() && current != nullptr)
            {
#ifdef DEBUG
                std::cout << "Size of children vector: " << current->get_children().size() << std::endl;
                std::cout << "Trying the for loop" << std::endl;
#endif
                size_t i = current->get_num_of_childs();
                for (auto node = current->get_children().rbegin(); node != current->get_children().rend(); ++node)
                {
#ifdef DEBUG
                    std::cout << "Pushing: " << current->get_children().at(i - 1)->get_data() << std::endl;
#endif
                    pre_order_stack.push(current->get_children().at(--i));
                }
            }
        }

        if (!pre_order_stack.empty()) // Checking agin in case the last node did not have childrens.
        {
#ifdef DEBUG
            std::cout << "Assigning the top, which is: " << pre_order_stack.top()->get_data() << std::endl;
#endif
            p_current = pre_order_stack.top();
        }
        else
        {
#ifdef DEBUG
            std::cout << "Assigning nullptr" << std::endl;
#endif
            p_current = nullptr;
        }
#ifdef DEBUG
        std::cout << "Done here" << std::endl;
#endif
        return this;
    }

    bool operator!=(const PreOrderIterator<T> &other) const
    {
#ifdef DEBUG
        std::cout << "Using !=" << std::endl;
#endif
        return this->p_current != other.get_current();
    }
};

template <typename T>
class PostOrderIterator
{
};

template <typename T>
class BFSIterator
{
private:
    queue<Node<T> *> _queue;
    Node<T> *p_current;

public:
    BFSIterator(Node<T> *root) : p_current(root)
    {
        if (root != nullptr)
            _queue.push(root);
    }

    ~BFSIterator() = default;

    Node<T> *get_current() const
    {
        return p_current;
    }

    const T &get_value() const
    {
#ifdef DEBUG
        std::cout << "Reached get_value: stack size: " << _queue.size() << std::endl;
#endif
        if (p_current != nullptr)
            return p_current->get_data();
        else
            throw std::runtime_error("ERROR in get_value");
    }

    BFSIterator<T> *operator++()
    {
        if (!_queue.empty())
        {
            Node<T> *current = _queue.front();

#ifdef DEBUG
            std::cout << "Current: " << current->get_data() << std::endl;
#endif
            _queue.pop();

            if (!current->is_leaf())
            {
                for (Node<T> *node : current->get_children())
                {
#ifdef DEBUG
                    std::cout << "Pushing: " << node->get_data() << std::endl;
#endif
                    _queue.push(node);
                }
            }
        }
        else
        {
            p_current = nullptr;
            return this;
        }

        p_current = _queue.front();
        return this;
    }

    bool operator!=(const BFSIterator<T> &other) const
    {
#ifdef DEBUG
        std::cout << "Using !=" << std::endl;
#endif
        return this->p_current != other.get_current();
    }
};