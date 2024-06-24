#pragma once
#include "Node.hpp"
#include <stack>
#include <queue>

// #define DEBUG

#define LEFT_CHILD 0
#define RIGHT_CHILD 1

using std::stack, std::queue, std::priority_queue;

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
#ifdef DEBUG
        std::cout << "Using get_value" << std::endl;
#endif
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

    PreOrderIterator<T> *operator++() override
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
                std::cout << "Size of children vector: " << current->get_num_of_childs() << std::endl;
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

    void addSubTree(Node<T> *sub_root)
    {
#ifdef DEBUG
        std::cout << "Adding the subtree of: " << sub_root->get_data() << std::endl;
#endif
        if (sub_root == nullptr || sub_root->is_leaf()) // If is leaf, was already been added on previous iteration
            return;

        Node<T> *r_node = nullptr;
        if (sub_root->get_num_of_childs() > 1)
        {
            r_node = sub_root->get_children()[RIGHT_CHILD];
            this->parents_stack.push(r_node);
        }

        Node<T> *l_node = sub_root->get_children()[LEFT_CHILD]; // Must have a left child because is not a leaf
        this->parents_stack.push(l_node);

        if (r_node != nullptr)
            addSubTree(r_node);

        addSubTree(l_node);
    }

public:
    PostOrderIterator(Node<T> *root) : Iterator<T>(root)
    {
#ifdef DEBUG
        if (root == nullptr)
            std::cout << "Root is nullptr" << std::endl;
#endif
        if (root != nullptr)
        {
            this->parents_stack.push(root); // Root must be printed at the end, therefore is pushed first

            if (root->get_num_of_childs() > 1)
            {
                this->parents_stack.push(root->get_children()[RIGHT_CHILD]);
                addSubTree(root->get_children()[RIGHT_CHILD]);
            }

            if (!root->is_leaf())
            {
                this->parents_stack.push(root->get_children()[LEFT_CHILD]);
                addSubTree(root->get_children()[LEFT_CHILD]);
            }

            this->p_current = this->parents_stack.top(); // Setting the pointer to the top of the stack (which is the leftmost leaf)
            this->parents_stack.pop();
        }
    }

    PostOrderIterator<T> *operator++() override
    {
        if (parents_stack.empty()) // Means that all nodes reached, can finish.
        {
            this->p_current = nullptr;
#ifdef DEBUG
            std::cout << "Parent stack is empty" << std::endl;
#endif
            return this;
        }

        if (!parents_stack.empty())
        {
            this->p_current = parents_stack.top();
            parents_stack.pop();
        }

        return this;
    }
};

template <typename T>
class InOrderIterator : public Iterator<T>
{
private:
    stack<Node<T> *> parents_stack;
    void addSubTree(Node<T> *sub_root)
    {
#ifdef DEBUG
        std::cout << "Adding the subtree of: " << sub_root->get_data() << std::endl;
#endif
        if (sub_root == nullptr || sub_root->is_leaf()) // If is leaf, was already been added on previous iteration
            return;

        Node<T> *r_node = nullptr;
        if (sub_root->get_num_of_childs() > 1)
        {
            r_node = sub_root->get_children()[RIGHT_CHILD];
            this->parents_stack.push(r_node);
        }

        this->parents_stack.push(sub_root);

        Node<T> *l_node = sub_root->get_children()[LEFT_CHILD]; // Must have a left child because is not a leaf
        this->parents_stack.push(l_node);

        if (r_node != nullptr)
            addSubTree(r_node);

        addSubTree(l_node);
    }

public:
    InOrderIterator(Node<T> *root) : Iterator<T>(root)
    {
        if (root != nullptr)
        {
            if (root->get_num_of_childs() > 1)
            {
                addSubTree(root->get_children()[RIGHT_CHILD]);
            }

            this->parents_stack.push(root);

            if (!root->is_leaf())
            {
                addSubTree(root->get_children()[LEFT_CHILD]);
            }

            this->p_current = this->parents_stack.top();
            this->parents_stack.pop();
        }
    }

    InOrderIterator<T> *operator++() override
    {
        if (parents_stack.empty()) // Means that all nodes reached, can finish.
        {
            this->p_current = nullptr;
#ifdef DEBUG
            std::cout << "Parent stack is empty" << std::endl;
#endif
            return this;
        }

        if (!parents_stack.empty())
        {
            this->p_current = parents_stack.top();
            parents_stack.pop();
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

    BFSIterator<T> *operator++() override
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

template <typename T>
class DFSIterator : public Iterator<T>
{
private:
    queue<Node<T> *> parents_stack;

    void addSubTree(Node<T> *sub_root)
    {
#ifdef DEBUG
        std::cout << "Adding the subtree of: " << sub_root->get_data() << std::endl;
#endif

        this->parents_stack.push(sub_root);
        if (sub_root->is_leaf()) // If is leaf, was already been added on previous iteration
        {
            return;
        }

        for (Node<T> *node : sub_root->get_children())
        {
            addSubTree(node);
        }
    }

public:
    DFSIterator(Node<T> *root) : Iterator<T>(root)
    {
        if (root != nullptr)
        {
#ifdef DEBUG
            std::cout << "Creating new DFSIterator" << std::endl;
#endif
            addSubTree(root);
            this->p_current = this->parents_stack.front();
            parents_stack.pop();
        }
    }

    DFSIterator<T> *operator++() override
    {
        if (parents_stack.empty())
        {
            this->p_current = nullptr;
            return this;
        }

        this->p_current = parents_stack.front();
        parents_stack.pop();
        return this;
    }
};

template <typename T>
struct CompareNodes
{
    bool operator()(const Node<T> *node1, const Node<T> *node2)
    {
        return node1->get_data() > node2->get_data();
    }
};

template <typename T>
class MinHeap : public Iterator<T>
{
private:
    Node<T> *min;
    priority_queue<Node<T> *, vector<Node<T> *>, CompareNodes<T>> pq;

    void addSubTree(Node<T> *sub_root)
    {
#ifdef DEBUG
        std::cout << "Adding the subtree of: " << sub_root->get_data() << std::endl;
#endif

        this->pq.push(sub_root);
        if (sub_root->is_leaf()) // If is leaf, was already been added on previous iteration
        {
            return;
        }

        for (Node<T> *node : sub_root->get_children())
        {
            addSubTree(node);
            this->p_current = pq.top();
            pq.pop();
        }
    }

public:
    MinHeap(Node<T> *root) : Iterator<T>(root)
    {
        addSubTree(root);
        this->p_current = pq.top();
        pq.pop();
    }

    MinHeap<T> *operator++() override
    {
        if (pq.empty())
        {
            this->p_current = nullptr;
            return this;
        }

        this->p_current = pq.top();
        pq.pop();
        return this;
    }
};
