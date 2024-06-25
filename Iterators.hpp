#pragma once
#include "Node.hpp"
#include <stack>
#include <queue>
#include <algorithm>

// #define DEBUG

#define LEFT_CHILD 0
#define RIGHT_CHILD 1
#define BINARY_TREE 2

using std::stack, std::queue, std::priority_queue;

template <typename T, int K = 2>
class Iterator
{
protected:
    Node<T> *p_current;
    bool not_binary;

public:
    Iterator(Node<T> *root) : p_current(root), not_binary(K > 2) {}
    virtual ~Iterator() = default;
    virtual Iterator<T, K> *operator++() = 0;
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

    virtual bool operator!=(const Iterator<T, K> &other) const
    {
        return this->p_current != other.get_current();
    }
};

template <typename T, int K>
class PreOrderIterator : public Iterator<T, K>
{
private:
    stack<Node<T> *> pre_order_stack;
    queue<Node<T> *> dfs_stack;

    void DFSaddSubTree(Node<T> *sub_root)
    {
#ifdef DEBUG
        std::cout << "Adding the subtree of: " << sub_root->get_data() << std::endl;
#endif

        this->dfs_stack.push(sub_root);
        if (sub_root->is_leaf()) // If is leaf, was already been added on previous iteration
        {
            return;
        }

        for (Node<T> *node : sub_root->get_children())
        {
            DFSaddSubTree(node);
        }
    }

public:
    PreOrderIterator(Node<T> *root) : Iterator<T, K>(root)
    {
        if (root != nullptr)
        {
            if (this->not_binary) // Run DFS
            {
                DFSaddSubTree(root);
                this->p_current = this->dfs_stack.front();
                this->dfs_stack.pop();
            }
            else
            {
                pre_order_stack.push(root);
            }
        }
    }

    PreOrderIterator<T, K> *operator++() override
    {
        if (this->not_binary)
        {
            if (this->dfs_stack.empty())
            {
                this->p_current = nullptr;
                return this;
            }

            this->p_current = dfs_stack.front();
            this->dfs_stack.pop();
            return this;
        }
        else
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
    }
};

template <typename T, int K>
class PostOrderIterator : public Iterator<T, K>
{
private:
    stack<Node<T> *> parents_stack;
    queue<Node<T> *> dfs_queue;

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

    void DFSaddSubTree(Node<T> *sub_root)
    {
#ifdef DEBUG
        std::cout << "DFS - Adding the subtree of: " << sub_root->get_data() << std::endl;
#endif

        this->dfs_queue.push(sub_root);
        if (sub_root->is_leaf()) // If is leaf, was already been added on previous iteration
        {
            return;
        }

        for (Node<T> *node : sub_root->get_children())
        {
            DFSaddSubTree(node);
        }
    }

public:
    PostOrderIterator(Node<T> *root) : Iterator<T, K>(root)
    {
#ifdef DEBUG
        if (root == nullptr)
            std::cout << "Root is nullptr" << std::endl;
#endif
        if (root != nullptr)
        {
            if (this->not_binary)
            {
#ifdef DEBUG
                std::cout << "Not binary" << std::endl;
#endif
                DFSaddSubTree(root);
                this->p_current = this->dfs_queue.front();
                this->dfs_queue.pop();
            }
            else
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
    }

    PostOrderIterator<T, K> *operator++() override
    {
        if (this->not_binary)
        {
            if (dfs_queue.empty())
            {
                this->p_current = nullptr;
                return this;
            }

            this->p_current = dfs_queue.front();
            dfs_queue.pop();
            return this;
        }
        else
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
    }
};

template <typename T, int K>
class InOrderIterator : public Iterator<T, K>
{
private:
    stack<Node<T> *> parents_stack;
    queue<Node<T> *> dfs_stack;

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

    void DFSaddSubTree(Node<T> *sub_root)
    {
#ifdef DEBUG
        std::cout << "Adding the subtree of: " << sub_root->get_data() << std::endl;
#endif

        this->dfs_stack.push(sub_root);
        if (sub_root->is_leaf()) // If is leaf, was already been added on previous iteration
        {
            return;
        }

        for (Node<T> *node : sub_root->get_children())
        {
            DFSaddSubTree(node);
        }
    }

public:
    InOrderIterator(Node<T> *root) : Iterator<T, K>(root)
    {
        if (root != nullptr)
        {
            if (this->not_binary)
            {
                DFSaddSubTree(root);
                this->p_current = this->dfs_stack.front();
                this->dfs_stack.pop();
            }
            else
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
    }

    InOrderIterator<T, K> *operator++() override
    {
        if (this->not_binary)
        {
            if (this->dfs_stack.empty())
            {
                this->p_current = nullptr;
                return this;
            }

            this->p_current = dfs_stack.front();
            this->dfs_stack.pop();
            return this;
        }
        else
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
    }
};

template <typename T, int K>
class BFSIterator : public Iterator<T, K>
{
private:
    queue<Node<T> *> _queue;

public:
    BFSIterator(Node<T> *root) : Iterator<T, K>(root)
    {
        if (root != nullptr)
            _queue.push(root);
    }

    BFSIterator<T, K> *operator++() override
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

template <typename T, int K>
class DFSIterator : public Iterator<T, K>
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
    DFSIterator(Node<T> *root) : Iterator<T, K>(root)
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

    DFSIterator<T, K> *operator++() override
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
        return node1->get_data() < node2->get_data();
    }
};

template <typename T>
class MinHeap : public Iterator<T, 2>
{
private:
    vector<Node<T> *> min_heap;

    static bool compare_nodes(const Node<T> *node1, const Node<T> *node2)
    {
        return node1->get_data() > node2->get_data();
    }

    void addSubTree(Node<T> *sub_root)
    {
#ifdef DEBUG
        std::cout << "Adding the subtree of: " << sub_root->get_data() << std::endl;
#endif

        this->min_heap.push_back(sub_root);
        if (sub_root->is_leaf()) // If it is leaf, was already been added in previous iteration
        {
            return;
        }

        for (Node<T> *node : sub_root->get_children())
        {
            addSubTree(node);
        }
    }

public:
    MinHeap(Node<T> *root) : Iterator<T, 2>(root)
    {
        if (root != nullptr)
        {
            addSubTree(root);
            std::make_heap(min_heap.begin(), min_heap.end(), compare_nodes);
            this->p_current = min_heap.front();
            #ifdef DEBUG
            std::cout << "Root:" << this->p_current->get_data() <<std::endl;
            #endif

            std::pop_heap(min_heap.begin(), min_heap.end(), compare_nodes);
            min_heap.pop_back();
        }
    }

    MinHeap<T> *operator++() override
    {
#ifdef DEBUG
        std::cout << "Iterating" << std::endl;
#endif
        if (min_heap.empty())
        {
            this->p_current = nullptr;
            return this;
        }

        this->p_current = min_heap.front();
        std::pop_heap(min_heap.begin(), min_heap.end(), compare_nodes);
        min_heap.pop_back();
#ifdef DEBUG
        std::cout << "Popped " << this->p_current->get_data() << std::endl;
#endif
        return this;
    }
};
