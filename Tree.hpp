/**
 * Name: Uriel Shapiro
 * ID: 9745
 */

#ifndef TREE_HPP
#define TREE_HPP
#include <stddef.h> 
#include <stdexcept>            // To throw exceptions
#include <SFML/Graphics.hpp>    // For visualization
#include <functional>           // For std::function
#include <sstream>              // For std::ostringstream
#include <string>
#include <iomanip>              // For std::fixed, std::setprecision
#include "Node.hpp"
#include "Iterators.hpp"
#include "Complex.hpp"

// #define DEBUG
#define ERROR_MESSEGE "Error: Can pre-order traverse only on 2-ary trees"

using std::to_string, std::ostringstream, std::string, std::vector;

/**
 * @brief A class that represents a k-ary tree of template type of nodes.
 */
template <typename T, int K = BINARY_TREE>
class Tree
{
private:
    size_t k_ary;
    Node<T> *root;
    vector<T> node_values;  // To check if a node is already in the tree, is used to prevent cycles.

public:
    Tree() : k_ary(K), root(nullptr){};
    ~Tree() = default; // Nodes are not dynamically allocated, therefore they will be deleted automatically when exiting the scope

    /**
     * @brief Adds a root to the tree.
     * If the tree already has a root, an exception will be thrown.
     */
    void add_root(Node<T> &_root)
    {
        this->root != nullptr ? throw std::runtime_error("ERROR: This tree already has a root") : this->root = &_root;
        node_values.push_back(_root.get_data());
    }

    /**
     * @brief Adds a child to a parent node.
     * If the parent node already has k children, an exception will be thrown.
     * If the child is already in the tree, an exception will be thrown (No cycles allowed in a tree).
     */
    void add_sub_node(Node<T> &parent, Node<T> &child)
    {
        if (parent.get_num_of_childs() + 1 > this->k_ary) // + 1 for the new child
            throw std::runtime_error("ERROR: Too many children to this node");
#ifdef DEBUG
        std::cout << "Searching for: " << child.get_data() << " in the tree" << std::endl;
#endif

        if (std::find(node_values.begin(), node_values.end(), child.get_data()) != node_values.end())   // Check if the node is already in the tree
            throw std::runtime_error("ERROR: This node is already in the tree - can't have a cycle in the tree");

        // If non of the exceptions were thrown, add the child to the parent
        parent.add_child(child);
        node_values.push_back(child.get_data());
    }

    Node<T> *get_root() const // Is used for tests
    {
        return this->root;
    }

    // ----------------------------------- Iterators -----------------------------------
    // The setting for each iterator is the same, and the iterators handle the input inside them, so no need to check the input here.
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

    // ----------------------------------- For Each Iterators -----------------------------------
    BFSIterator<T, K> begin()
    {
        return begin_bfs_scan();
    }

    BFSIterator<T, K> end()
    {
        return end_bfs_scan();
    }

    // ----------------------------------- Visualization -----------------------------------
    friend std::ostream &operator<<(std::ostream &os, const Tree &tree)
    {
        if (tree.root == nullptr)   // Nothing to print
            return os;

        sf::RenderWindow window(sf::VideoMode(1000, 800), "Tree Visualization");    // Create a window
        sf::Font font;
        if (!font.loadFromFile("arial.ttf"))                                        // Load a font from a file
        {
            std::cerr << "Error loading font\n";
            return os;
        }

        const float node_radius = 35.f;                 // Slightly decreased node radius
        const float vertical_spacing = 80.f;            // Reduced vertical spacing
        const float initial_horizontal_spacing = 200.f; // Reduced initial horizontal spacing

        std::map<Node<T> *, sf::Vector2f> positions;    // This map will store the positions of each node (Node, Position)

        // Recursively position nodes
        std::function<void(Node<T> *, float, float, float)> position_nodes = [&](Node<T> *node, float x, float y, float horizontal_spacing)
        {
            if (node == nullptr)
                return;

            positions[node] = sf::Vector2f(x, y);   // Store the position of the node in the map

            float child_x_offset = x - (node->get_children().size() - 1) * horizontal_spacing / 2.f;    // Calculate the offset for the children

            for (size_t i = 0; i < node->get_children().size(); ++i)
            {
                Node<T> *child = node->get_children()[i];
                if (child != nullptr)
                {
                    // Recursively position the children
                    position_nodes(child, child_x_offset + i * horizontal_spacing, y + vertical_spacing, horizontal_spacing / 2.f); 
                }
            }
        };

        // Start positioning nodes from the root
        position_nodes(tree.root, window.getSize().x / 2.f, node_radius + 50.f, initial_horizontal_spacing);

        // Main window loop
        while (window.isOpen())
        { 
            sf::Event event;
            while (window.pollEvent(event)) // Changes the event status
            {
                if (event.type == sf::Event::Closed)    
                    window.close();
            }

            window.clear(sf::Color::White); // Each iteration, clear the window

            for (const auto &pair : positions)  
            {
                Node<T> *node = pair.first;
                sf::Vector2f position = pair.second;    // Get the position of the node

                sf::CircleShape circle(node_radius);    // Create a circle shape
                circle.setFillColor(sf::Color::Green);  // Set the color of the circle to green
                circle.setPosition(position - sf::Vector2f(node_radius, node_radius));  // Set the position of the circle
                window.draw(circle);                    // Draw the circle on the window

                sf::Text text;
                text.setFont(font);                     // Set the font of the text to write the value of the node
                if constexpr (std::is_same<T, string>::value || std::is_same<T, Complex<T>>::value)
                {
                    text.setString(node->get_data());   // Set the string of the text to the value of the node
                }
                else
                {
                    text.setString(formatValue(node->get_data()));
                }
                text.setCharacterSize(16); // Set the text size
                text.setFillColor(sf::Color::Black);    // Set the color of the text
                sf::FloatRect text_bounds = text.getLocalBounds();  // Get the bounds of the text
                text.setOrigin(text_bounds.left + text_bounds.width / 2.0f, text_bounds.top + text_bounds.height / 2.0f);   // Set the origin of the text to be in the center
                text.setPosition(position); // Set the position of the text to be the same as the node
                window.draw(text);  // Draw the text on the window
            
                for (Node<T> *child : node->get_children())  // Draw lines between the nodes
                {
                    if (child)
                    {
                        sf::Vector2f child_position = positions[child]; // Get the position of the child
                        
                        // Create a line between the nodes
                        sf::Vertex line[] = 
                            {
                                sf::Vertex(position, sf::Color::Black),
                                sf::Vertex(child_position, sf::Color::Black)};
                        window.draw(line, 2, sf::Lines);    // Draw the line on the window
                    }
                }
            }
            window.display();   // Display the window each iteration
        }
        return os;
    }
};
#endif