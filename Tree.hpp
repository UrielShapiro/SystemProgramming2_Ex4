#pragma once
#include <stddef.h>
#include <stdexcept>
#include <SFML/Graphics.hpp>
#include <functional>
#include <sstream>
#include <string>
#include <iomanip>
#include "Node.hpp"
#include "Iterators.hpp"
#include "Complex.hpp"

// #define DEBUG
#define ERROR_MESSEGE "Error: Can pre-order traverse only on 2-ary trees"

using std::to_string, std::ostringstream, std::string;

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
        if (this->k_ary > 2)
            throw std::runtime_error(ERROR_MESSEGE);

        return MinHeap<T>(root);
    }

    MinHeap<T> end_min_heap_scan()
    {
        if (this->k_ary > 2)
            throw std::runtime_error(ERROR_MESSEGE);

        return MinHeap<T>(nullptr);
    }

    friend std::ostream &operator<<(std::ostream &os, const Tree &tree)
    {
        if (tree.root == nullptr)
            return os;

        sf::RenderWindow window(sf::VideoMode(1000, 800), "Tree Visualization");
        sf::Font font;
        if (!font.loadFromFile("arial.ttf"))
        {
            std::cerr << "Error loading font\n";
            return os;
        }

        const float node_radius = 25.f;                 // Slightly decreased node radius
        const float vertical_spacing = 80.f;            // Reduced vertical spacing
        const float initial_horizontal_spacing = 200.f; // Reduced initial horizontal spacing

        std::map<Node<T> *, sf::Vector2f> positions;

        // Recursively position nodes
        std::function<void(Node<T> *, float, float, float)> position_nodes = [&](Node<T> *node, float x, float y, float horizontal_spacing)
        {
            if (node == nullptr)
                return;

            positions[node] = sf::Vector2f(x, y);

            float child_x_offset = x - (node->get_children().size() - 1) * horizontal_spacing / 2.f;

            for (size_t i = 0; i < node->get_children().size(); ++i)
            {
                Node<T> *child = node->get_children()[i];
                if (child != nullptr)
                {
                    position_nodes(child, child_x_offset + i * horizontal_spacing, y + vertical_spacing, horizontal_spacing / 2.f);
                }
            }
        };

        position_nodes(tree.root, window.getSize().x / 2.f, node_radius + 50.f, initial_horizontal_spacing);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear(sf::Color::White);

            for (const auto &pair : positions)
            {
                Node<T> *node = pair.first;
                sf::Vector2f position = pair.second;

                sf::CircleShape circle(node_radius);
                circle.setFillColor(sf::Color::Green);
                circle.setPosition(position - sf::Vector2f(node_radius, node_radius));
                window.draw(circle);

                sf::Text text;
                text.setFont(font);
                if constexpr (std::is_same<T, string>::value)
                {
                    text.setString(node->get_data());
                }
                else if constexpr (std::is_same<T, Complex>::value)
                {
                    ostringstream oss;
                    oss << node->get_data();
                    text.setString(oss.str());
                }
                else
                {

                    std::ostringstream oss;
                    oss << std::fixed << std::setprecision(2) << node->get_data();
                    text.setString(oss.str());
                }
                text.setCharacterSize(16); // Slightly larger text size
                text.setFillColor(sf::Color::Black);
                sf::FloatRect text_bounds = text.getLocalBounds();
                text.setOrigin(text_bounds.left + text_bounds.width / 2.0f, text_bounds.top + text_bounds.height / 2.0f);
                text.setPosition(position);
                window.draw(text);

                for (Node<T> *child : node->get_children())
                {
                    if (child)
                    {
                        sf::Vector2f child_position = positions[child];

                        sf::Vertex line[] =
                            {
                                sf::Vertex(position, sf::Color::Black),
                                sf::Vertex(child_position, sf::Color::Black)};
                        window.draw(line, 2, sf::Lines);
                    }
                }
            }
            window.display();
        }
        return os;
    }
};
