#pragma once
#include "Node.hpp"
#include <stack>
#include <queue>

// #define DEBUG

#define LEFT_CHILD 0
#define RIGHT_CHILD 1

using std::stack, std::queue;

template <typename T>
class Iterator
{
protected:
    Node<T> *p_current;

public:
    Iterator(Node<T> *root) : p_current(root) {}
    virtual ~Iterator() = default;
    virtual Iterator<T> *operator++() = 0;
    virtual const T &get_value() const
    {
        if (this->p_current != nullptr)
            return this->p_current->get_data();
        else
            throw std::runtime_error("ERROR in get_value");
    }

    virtual Node<T> *get_current() const
    {
        return this->p_current;
    }

    virtual bool operator!=(const Iterator<T> &other) const
    {
        return this->p_current != other.get_current();
    }
};

template <typename T>
class PreOrderIterator : public Iterator<T>
{
private:
    stack<Node<T> *> pre_order_stack;

public:
    PreOrderIterator(Node<T> *root) : Iterator<T>(root)
    {
        if (root != nullptr)
            pre_order_stack.push(root);
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
            this->p_current = pre_order_stack.top();
        }
        else
        {
#ifdef DEBUG
            std::cout << "Assigning nullptr" << std::endl;
#endif
            this->p_current = nullptr;
        }
#ifdef DEBUG
        std::cout << "Done here" << std::endl;
#endif
        return this;
    }
};

template <typename T>
class PostOrderIterator : public Iterator<T>
{
private:
    stack<Node<T> *> parents_stack;
    queue<Node<T> *> children_queue;

    void addSubTree(Node<T> *sub_root)
    {
        if (sub_root->is_leaf())
            return;

        Node<T> *r_node;
        if (sub_root->get_children().size() > 1)
        {
            r_node = sub_root->get_children()[RIGHT_CHILD];
            parents_stack.push(r_node);
        }

        Node<T> *l_node = sub_root->get_children()[LEFT_CHILD];
        parents_stack.push(l_node);
        if (sub_root->get_children().size() > 1)
            addSubTree(r_node);

        addSubTree(l_node);
    }

public:
    PostOrderIterator(Node<T> *root) : Iterator<T>(root)
    {
        addSubTree(root->get_children()[RIGHT_CHILD]);
        parents_stack.push(root);
        addSubTree(root->get_children()[LEFT_CHILD]);
        
        children_queue.push(parents_stack.top()->get_children()[RIGHT_CHILD]);
        children_queue.push(parents_stack.top()->get_children()[LEFT_CHILD]);
        this->p_current = children_queue.front();
        children_queue.pop();
    }

    PostOrderIterator<T> *operator++()
    {
        if (children_queue.empty() && parents_stack.empty())
        {
            this->p_current = nullptr;
            return this;
        }
        if (!children_queue.empty())
        {
            this->p_current = children_queue.front();
            children_queue.pop();
            return this;
        }
        if (!parents_stack.empty())
        {
            this->p_current = parents_stack.top();
            parents_stack.pop();
            children_queue.push(parents_stack.top()->get_children()[LEFT_CHILD]);
            children_queue.push(parents_stack.top()->get_children()[RIGHT_CHILD]);
        }

        return this;
    }
};

template <typename T>
class BFSIterator : public Iterator<T>
{
private:
    queue<Node<T> *> _queue;

public:
    BFSIterator(Node<T> *root) : Iterator<T>(root)
    {
        if (root != nullptr)
            _queue.push(root);
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
            this->p_current = nullptr;
            return this;
        }

        this->p_current = _queue.front();
        return this;
    }
};
